/*
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * Copyright (c) 1999-2008 Apple Inc.  All Rights Reserved.
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 *
 */
/*
    File:       QTSSPrefs.cpp

    Contains:   Implements class defined in QTSSPrefs.h.

    Change History (most recent first):
    
*/

#include "QTSServerPrefs.h"
#include "MyAssert.h"
#include "OSMemory.h"
#include "QTSSDataConverter.h"
#include "defaultPaths.h"
#include "QTSSRollingLog.h"
 
#ifndef __Win32__
#include <signal.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <errno.h>
#endif

QTSServerPrefs::PrefInfo QTSServerPrefs::sPrefInfo[] =
{
    { kDontAllowMultipleValues, "0",        NULL                    },  //connection_timeout
    { kDontAllowMultipleValues, "easycms.easydarwin.org",  NULL     },  //cms_addr
	{ kDontAllowMultipleValues,	"10000",		NULL				},	//cms_port
    { kDontAllowMultipleValues, "10000",     NULL                   },  //maximum_connections
    { kDontAllowMultipleValues, "102400",   NULL                    },  //maximum_bandwidth
	{ kDontAllowMultipleValues,	"000000000000", NULL				},	//serial_number
    { kAllowMultipleValues,     "0",        NULL                    },  //bind_ip_addr
    { kDontAllowMultipleValues, "false",    NULL                    },  //break_on_assert
    { kDontAllowMultipleValues, "true",     NULL                    },  //auto_restart
    { kDontAllowMultipleValues, "1",        NULL                    },  //total_bytes_update
    { kDontAllowMultipleValues, "60",       NULL                    },  //average_bandwidth_update
    { kDontAllowMultipleValues, "80",		NULL                    },  //local_camera_port
	{ kDontAllowMultipleValues,	DEFAULTPATHS_SSM_DIR,	NULL		},	//module_folder
    { kDontAllowMultipleValues, "Error",    NULL                    },  //error_logfile_name
	{ kDontAllowMultipleValues,	DEFAULTPATHS_LOG_DIR,	NULL		},	//error_logfile_dir
    { kDontAllowMultipleValues, "7",        NULL                    },  //error_logfile_interval
    { kDontAllowMultipleValues, "256000",   NULL                    },  //error_logfile_size
    { kDontAllowMultipleValues, "2",        NULL                    },  //error_logfile_verbosity
    { kDontAllowMultipleValues, "true",     NULL                    },  //screen_logging
    { kDontAllowMultipleValues, "true",     NULL                    },  //error_logging

    { kDontAllowMultipleValues, "8192",     NULL                    },  //min_tcp_buffer_size
	{ kDontAllowMultipleValues,	"200000",	NULL					},	//max_tcp_buffer_size
    { kDontAllowMultipleValues, ".5",       NULL                    },  //tcp_seconds_to_buffer
    { kDontAllowMultipleValues, "127.0.0.1", NULL					},  //local_camera_addr
#ifndef __Win32__
    { kDontAllowMultipleValues, "admin",     NULL                    },  //run_user_name
    { kDontAllowMultipleValues, "admin",     NULL                    },  //run_password
#else
    { kDontAllowMultipleValues, "",         NULL                    },  //run_user_name
    { kDontAllowMultipleValues, "",         NULL                    },  //run_group_name
#endif

    { kAllowMultipleValues,     "554",      NULL					},  //rtsp_ports

	{ kDontAllowMultipleValues, "0",        NULL                    },  //run_num_threads
    { kDontAllowMultipleValues, DEFAULTPATHS_PID_DIR PLATFORM_SERVER_BIN_NAME ".pid",	NULL	},	//pid_file
    { kDontAllowMultipleValues, "false",    NULL                    },   //force_logs_close_on_write
    { kDontAllowMultipleValues, "false",    NULL                    },   //disable_thinning
	{ kDontAllowMultipleValues, "0",        NULL                     }, //default_stream_quality
    { kDontAllowMultipleValues, "true",     NULL                     }, //enable_allow_guest_default
    { kDontAllowMultipleValues, "1",        NULL                     }  //run_num_rtsp_threads
   
};



QTSSAttrInfoDict::AttrInfo  QTSServerPrefs::sAttributes[] =
{   /*fields:   fAttrName, fFuncPtr, fAttrDataType, fAttrPermission */
    /* 0 */ { "connection_timeout",                     NULL,                   qtssAttrDataTypeUInt32,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 1 */ { "cms_addr",								NULL,                   qtssAttrDataTypeCharArray,  qtssAttrModeRead | qtssAttrModeWrite },
    /* 2 */ { "cms_port",								NULL,                   qtssAttrDataTypeUInt32,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 3 */ { "maximum_connections",                    NULL,                   qtssAttrDataTypeSInt32,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 4 */ { "maximum_bandwidth",                      NULL,                   qtssAttrDataTypeSInt32,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 5 */ { "serial_number",                           NULL,                   qtssAttrDataTypeCharArray,  qtssAttrModeRead | qtssAttrModeWrite },
    /* 6 */ { "bind_ip_addr",                           NULL,                   qtssAttrDataTypeCharArray,  qtssAttrModeRead | qtssAttrModeWrite },
    /* 7 */ { "break_on_assert",                        NULL,                   qtssAttrDataTypeBool16,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 8 */ { "auto_restart",                           NULL,                   qtssAttrDataTypeBool16,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 9 */ { "total_bytes_update",                     NULL,                   qtssAttrDataTypeUInt32,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 10 */ { "average_bandwidth_update",              NULL,                   qtssAttrDataTypeUInt32,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 11 */ { "local_camera_port",						NULL,                   qtssAttrDataTypeUInt16,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 12 */ { "module_folder",                         NULL,                   qtssAttrDataTypeCharArray,  qtssAttrModeRead | qtssAttrModeWrite },
    /* 13 */ { "error_logfile_name",                    NULL,                   qtssAttrDataTypeCharArray,  qtssAttrModeRead | qtssAttrModeWrite },
    /* 14 */ { "error_logfile_dir",                     NULL,                   qtssAttrDataTypeCharArray,  qtssAttrModeRead | qtssAttrModeWrite },
    /* 15 */ { "error_logfile_interval",                NULL,                   qtssAttrDataTypeUInt32,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 16 */ { "error_logfile_size",                    NULL,                   qtssAttrDataTypeUInt32,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 17 */ { "error_logfile_verbosity",               NULL,                   qtssAttrDataTypeUInt32,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 18 */ { "screen_logging",                        NULL,                   qtssAttrDataTypeBool16,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 19 */ { "error_logging",                         NULL,                   qtssAttrDataTypeBool16,     qtssAttrModeRead | qtssAttrModeWrite },

	/* 20 */ { "min_tcp_buffer_size",                   NULL,                   qtssAttrDataTypeUInt32,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 21 */ { "max_tcp_buffer_size",                   NULL,                   qtssAttrDataTypeUInt32,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 22 */ { "tcp_seconds_to_buffer",                 NULL,                   qtssAttrDataTypeFloat32,    qtssAttrModeRead | qtssAttrModeWrite },
    /* 23 */ { "local_camera_addr",						NULL,                   qtssAttrDataTypeCharArray,  qtssAttrModeRead | qtssAttrModeWrite },
    /* 24 */ { "run_user_name",                         NULL,                   qtssAttrDataTypeCharArray,  qtssAttrModeRead | qtssAttrModeWrite },
    /* 25 */ { "run_password",							NULL,                   qtssAttrDataTypeCharArray,  qtssAttrModeRead | qtssAttrModeWrite },
    /* 26 */ { "rtsp_port",                             NULL,                   qtssAttrDataTypeUInt16,     qtssAttrModeRead | qtssAttrModeWrite },

	/* 27 */ { "run_num_threads",                       NULL,                   qtssAttrDataTypeUInt32,     qtssAttrModeRead | qtssAttrModeWrite },
	/* 28 */ { "pid_file",								NULL,					qtssAttrDataTypeCharArray,	qtssAttrModeRead | qtssAttrModeWrite },
    /* 29 */ { "force_logs_close_on_write",             NULL,                   qtssAttrDataTypeBool16,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 30 */ { "disable_thinning",                      NULL,                   qtssAttrDataTypeBool16,     qtssAttrModeRead | qtssAttrModeWrite },
	/* 31 */ { "default_stream_quality",                NULL,                   qtssAttrDataTypeUInt16,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 32 */ { "enable_allow_guest_default",			NULL,                   qtssAttrDataTypeBool16,     qtssAttrModeRead | qtssAttrModeWrite },
    /* 33 */ { "run_num_rtsp_threads",					NULL,                   qtssAttrDataTypeUInt32,     qtssAttrModeRead | qtssAttrModeWrite }
};


QTSServerPrefs::QTSServerPrefs(XMLPrefsParser* inPrefsSource, Bool16 inWriteMissingPrefs)
:   QTSSPrefs(inPrefsSource, NULL, QTSSDictionaryMap::GetMap(QTSSDictionaryMap::kPrefsDictIndex), false),
    fConnectionTimeoutInSecs(0),
    fRTSPTimeoutString(fRTSPTimeoutBuf, 0),

    fCMSPort(0),
    fMaximumConnections(0),
    fMaxBandwidthInKBits(0),
    fBreakOnAssert(false),
    fAutoRestart(false),
    fTBUpdateTimeInSecs(0),
    fABUpdateTimeInSecs(0),
    fLocalCameraPort(80),
    fErrorRollIntervalInDays(0),
    fErrorLogBytes(0),
    fErrorLogVerbosity(0),
    fScreenLoggingEnabled(true),
    fErrorLogEnabled(false),
    fMinTCPBufferSizeInBytes(0),
    fMaxTCPBufferSizeInBytes(0),
    fTCPSecondsToBuffer(0),

    fAuthScheme(qtssAuthDigest),
    fNumThreads(0),
    fNumRTSPThreads(0),

    fCloseLogsOnWrite(false),
    fDisableThinning(false),
	//
	fDefaultStreamQuality(0),
	fAllowGuestAuthorizeDefault(true)
{
    SetupAttributes();
    RereadServerPreferences(inWriteMissingPrefs);
}

void QTSServerPrefs::Initialize()
{
    for (UInt32 x = 0; x < qtssPrefsNumParams; x++)
        QTSSDictionaryMap::GetMap(QTSSDictionaryMap::kPrefsDictIndex)->
            SetAttribute(x, sAttributes[x].fAttrName, sAttributes[x].fFuncPtr,
                            sAttributes[x].fAttrDataType, sAttributes[x].fAttrPermission);
}


void QTSServerPrefs::SetupAttributes()
{
    this->SetVal(qtssPrefsConnectionTimeout,&fConnectionTimeoutInSecs,        sizeof(fConnectionTimeoutInSecs));

	this->SetVal(qtssPrefsCMSIPAddr,		&fCMSIPAddr,				sizeof(fCMSIPAddr));
    this->SetVal(qtssPrefsCMSPort,			&fCMSPort,					sizeof(fCMSPort));
    this->SetVal(qtssPrefsMaximumConnections,&fMaximumConnections,      sizeof(fMaximumConnections));
    this->SetVal(qtssPrefsMaximumBandwidth, &fMaxBandwidthInKBits,      sizeof(fMaxBandwidthInKBits));
    this->SetVal(qtssPrefsBreakOnAssert,    &fBreakOnAssert,            sizeof(fBreakOnAssert));
    this->SetVal(qtssPrefsAutoRestart,      &fAutoRestart,              sizeof(fAutoRestart));
    this->SetVal(qtssPrefsTotalBytesUpdate, &fTBUpdateTimeInSecs,       sizeof(fTBUpdateTimeInSecs));
    this->SetVal(qtssPrefsAvgBandwidthUpdate,&fABUpdateTimeInSecs,      sizeof(fABUpdateTimeInSecs));
    this->SetVal(qtssPrefsLocalCameraPort, &fLocalCameraPort,   sizeof(fLocalCameraPort));

    this->SetVal(qtssPrefsErrorRollInterval, &fErrorRollIntervalInDays, sizeof(fErrorRollIntervalInDays));
    this->SetVal(qtssPrefsMaxErrorLogSize,  &fErrorLogBytes,            sizeof(fErrorLogBytes));
    this->SetVal(qtssPrefsErrorLogVerbosity, &fErrorLogVerbosity,       sizeof(fErrorLogVerbosity));
    this->SetVal(qtssPrefsScreenLogging,    &fScreenLoggingEnabled,     sizeof(fScreenLoggingEnabled));
    this->SetVal(qtssPrefsErrorLogEnabled,  &fErrorLogEnabled,          sizeof(fErrorLogEnabled));

    this->SetVal(qtssPrefsMinTCPBufferSizeInBytes,  &fMinTCPBufferSizeInBytes,  sizeof(fMinTCPBufferSizeInBytes));
    this->SetVal(qtssPrefsMaxTCPBufferSizeInBytes,  &fMaxTCPBufferSizeInBytes,  sizeof(fMaxTCPBufferSizeInBytes));
    this->SetVal(qtssPrefsTCPSecondsToBuffer,   &fTCPSecondsToBuffer,           sizeof(fTCPSecondsToBuffer));

    this->SetVal(qtssPrefsRunNumThreads,                &fNumThreads,                   sizeof(fNumThreads));

    this->SetVal(qtssPrefsCloseLogsOnWrite,             &fCloseLogsOnWrite,             sizeof(fCloseLogsOnWrite));
    this->SetVal(qtssPrefsDisableThinning,              &fDisableThinning,              sizeof(fDisableThinning));

	this->SetVal(qtssPrefsDefaultStreamQuality,			&fDefaultStreamQuality,                 sizeof(fDefaultStreamQuality)); //default_stream_quality
	this->SetVal(qtssPrefsEnableAllowGuestDefault,      &fAllowGuestAuthorizeDefault,   sizeof(fAllowGuestAuthorizeDefault)); //enable_allow_guest_authorize_default
    this->SetVal(qtssPrefsNumRTSPThreads,               &fNumRTSPThreads,               sizeof(fNumRTSPThreads));
}

void QTSServerPrefs::RereadServerPreferences(Bool16 inWriteMissingPrefs)
{
    OSMutexLocker locker(&fPrefsMutex);
    QTSSDictionaryMap* theMap = QTSSDictionaryMap::GetMap(QTSSDictionaryMap::kPrefsDictIndex);
    
    for (UInt32 x = 0; x < theMap->GetNumAttrs(); x++)
    {
        //
        // Look for a pref in the file that matches each pref in the dictionary
        char* thePrefTypeStr = NULL;
        char* thePrefName = NULL;
        
        ContainerRef server = fPrefsSource->GetRefForServer();
        ContainerRef pref = fPrefsSource->GetPrefRefByName( server, theMap->GetAttrName(x) );
        char* thePrefValue = NULL;
        if (pref != NULL)
            thePrefValue = fPrefsSource->GetPrefValueByRef( pref, 0, &thePrefName,
                                                                    (char**)&thePrefTypeStr);
        
        if ((thePrefValue == NULL) && (x < qtssPrefsNumParams)) // Only generate errors for server prefs
        {
            //
            // There is no pref, use the default and log an error
            if (::strlen(sPrefInfo[x].fDefaultValue) > 0)
            {
                //
                // Only log this as an error if there is a default (an empty string
                // doesn't count). If there is no default, we will constantly print
                // out an error message...
                QTSSModuleUtils::LogError(  QTSSModuleUtils::GetMisingPrefLogVerbosity(),
                                            qtssServerPrefMissing,
                                            0,
                                            sAttributes[x].fAttrName,
                                            sPrefInfo[x].fDefaultValue);
            }
            
            this->SetPrefValue(x, 0, sPrefInfo[x].fDefaultValue, sAttributes[x].fAttrDataType);
            if (sPrefInfo[x].fAdditionalDefVals != NULL)
            {
                //
                // Add additional default values if they exist
                for (UInt32 y = 0; sPrefInfo[x].fAdditionalDefVals[y] != NULL; y++)
                    this->SetPrefValue(x, y+1, sPrefInfo[x].fAdditionalDefVals[y], sAttributes[x].fAttrDataType);
            }
            
            if (inWriteMissingPrefs)
            {
                //
                // Add this value into the file, cuz we need it.
                pref = fPrefsSource->AddPref( server, sAttributes[x].fAttrName, QTSSDataConverter::TypeToTypeString(sAttributes[x].fAttrDataType));
                fPrefsSource->AddPrefValue(pref, sPrefInfo[x].fDefaultValue);
                
                if (sPrefInfo[x].fAdditionalDefVals != NULL)
                {
                    for (UInt32 a = 0; sPrefInfo[x].fAdditionalDefVals[a] != NULL; a++)
                        fPrefsSource->AddPrefValue(pref, sPrefInfo[x].fAdditionalDefVals[a]);
                }
            }
            continue;
        }
        
        QTSS_AttrDataType theType = QTSSDataConverter::TypeStringToType(thePrefTypeStr);
        
        if ((x < qtssPrefsNumParams) && (theType != sAttributes[x].fAttrDataType)) // Only generate errors for server prefs
        {
            //
            // The pref in the file has the wrong type, use the default and log an error
            
            if (::strlen(sPrefInfo[x].fDefaultValue) > 0)
            {
                //
                // Only log this as an error if there is a default (an empty string
                // doesn't count). If there is no default, we will constantly print
                // out an error message...
                QTSSModuleUtils::LogError(  qtssWarningVerbosity,
                                            qtssServerPrefWrongType,
                                            0,
                                            sAttributes[x].fAttrName,
                                            sPrefInfo[x].fDefaultValue);
            }
            
            this->SetPrefValue(x, 0, sPrefInfo[x].fDefaultValue, sAttributes[x].fAttrDataType);
            if (sPrefInfo[x].fAdditionalDefVals != NULL)
            {
                //
                // Add additional default values if they exist
                for (UInt32 z = 0; sPrefInfo[x].fAdditionalDefVals[z] != NULL; z++)
                    this->SetPrefValue(x, z+1, sPrefInfo[x].fAdditionalDefVals[z], sAttributes[x].fAttrDataType);
            }

            if (inWriteMissingPrefs)
            {
                //
                // Remove it out of the file and add in the default.
                fPrefsSource->RemovePref(pref);
                pref = fPrefsSource->AddPref( server, sAttributes[x].fAttrName, QTSSDataConverter::TypeToTypeString(sAttributes[x].fAttrDataType));
                fPrefsSource->AddPrefValue(pref, sPrefInfo[x].fDefaultValue);
                if (sPrefInfo[x].fAdditionalDefVals != NULL)
                {
                    for (UInt32 b = 0; sPrefInfo[x].fAdditionalDefVals[b] != NULL; b++)
                        fPrefsSource->AddPrefValue(pref, sPrefInfo[x].fAdditionalDefVals[b]);
                }
            }
            continue;
        }
        
        UInt32 theNumValues = 0;
        if ((x < qtssPrefsNumParams) && (!sPrefInfo[x].fAllowMultipleValues))
            theNumValues = 1;
            
        this->SetPrefValuesFromFileWithRef(pref, x, theNumValues);
    }
    
    QTSSRollingLog::SetCloseOnWrite(fCloseLogsOnWrite);
    //
    // In case we made any changes, write out the prefs file
    (void)fPrefsSource->WritePrefsFile();
}

char* QTSServerPrefs::GetStringPref(QTSS_AttributeID inAttrID)
{
    StrPtrLen theBuffer;
    (void)this->GetValue(inAttrID, 0, NULL, &theBuffer.Len);
    theBuffer.Ptr = NEW char[theBuffer.Len + 1];
    theBuffer.Ptr[0] = '\0';
    
    if (theBuffer.Len > 0)
    {
        QTSS_Error theErr = this->GetValue(inAttrID, 0, theBuffer.Ptr, &theBuffer.Len);
        if (theErr == QTSS_NoErr)
            theBuffer.Ptr[theBuffer.Len] = 0;
    }
    return theBuffer.Ptr;
}

void QTSServerPrefs::SetCloseLogsOnWrite(Bool16 closeLogsOnWrite) 
{
    QTSSRollingLog::SetCloseOnWrite(closeLogsOnWrite);
    fCloseLogsOnWrite = closeLogsOnWrite; 
}

Bool16 QTSServerPrefs::GetCMSIP(char* outCMSIP)
{
	if(outCMSIP == NULL)
		return false;

#ifndef _WIN32
    typedef struct hostent HOSTENT;
    signal(SIGPIPE, SIG_IGN);
#endif
	HOSTENT *host_entry = ::gethostbyname(this->GetStringPref(qtssPrefsCMSIPAddr));
    char ip[20] = {0};
    if (host_entry == NULL)
    {
        switch (h_errno)
        {
        case HOST_NOT_FOUND:
            fputs("The host was not found.\n", stderr);
            break;
        case NO_ADDRESS:
            fputs("The name is valid but it has no address.\n", stderr);
            break;
        case NO_RECOVERY:
            fputs("A non-recoverable name server error occurred.\n", stderr);
            break;
        case TRY_AGAIN:
            fputs("The name server is temporarily unavailable.", stderr);
            break;
        }
        return false;
    }
    else
    {
        sprintf(outCMSIP, "%s", inet_ntoa(*((struct in_addr *) host_entry->h_addr_list[0])));
    }

	return true;
}


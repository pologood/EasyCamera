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
    Contains:   Object store for RTSP server preferences.
    
    
    
*/

#ifndef __QTSSERVERPREFS_H__
#define __QTSSERVERPREFS_H__

#include "StrPtrLen.h"
#include "QTSSPrefs.h"
#include "XMLPrefsParser.h"

class QTSServerPrefs : public QTSSPrefs
{
    public:

        // INITIALIZE
        //
        // This function sets up the dictionary map. Must be called before instantiating
        // the first RTSPPrefs object.
    
        static void Initialize();

        QTSServerPrefs(XMLPrefsParser* inPrefsSource, Bool16 inWriteMissingPrefs);
        virtual ~QTSServerPrefs() {}
        
        //This is callable at any time, and is thread safe wrt to the accessors.
        //Pass in true if you want this function to update the prefs file if
        //any defaults need to be used. False otherwise
        void RereadServerPreferences(Bool16 inWriteMissingPrefs);
        
        //Individual accessor methods for preferences.
        
        //Amount of idle time after which respective protocol sessions are timed out
        //(stored in seconds)
        
        //This is the value we advertise to clients (lower than the real one)
        UInt32  GetConnectionTimeoutSecs()  { return fConnectionTimeoutInSecs; }
        UInt32  GetCMSPort()   { return fCMSPort; }
        StrPtrLen*  GetRTSPTimeoutAsString() { return &fRTSPTimeoutString; }

        //-1 means unlimited
        SInt32  GetMaxConnections()         { return fMaximumConnections; }
        SInt32  GetMaxKBitsBandwidth()      { return fMaxBandwidthInKBits; }
        
        // for tcp buffer size scaling
        UInt32  GetMinTCPBufferSizeInBytes()            { return fMinTCPBufferSizeInBytes; }
        UInt32  GetMaxTCPBufferSizeInBytes()            { return fMaxTCPBufferSizeInBytes; }
        Float32 GetTCPSecondsToBuffer()                 { return fTCPSecondsToBuffer; }
        
        //for joining HTTP sessions from behind a round-robin DNS
        Bool16  GetDoReportHTTPConnectionAddress()      { return fDoReportHTTPConnectionAddress;  }
        
        //for debugging, mainly
        Bool16      ShouldServerBreakOnAssert()         { return fBreakOnAssert; }
        Bool16      IsAutoRestartEnabled()              { return fAutoRestart; }

        UInt32      GetTotalBytesUpdateTimeInSecs()     { return fTBUpdateTimeInSecs; }
        UInt32      GetAvgBandwidthUpdateTimeInSecs()   { return fABUpdateTimeInSecs; }
        UInt32      GetLocalCameraPort()         { return fLocalCameraPort; }
        
        // For the compiled-in error logging module
        
        Bool16  IsErrorLogEnabled()             { return fErrorLogEnabled; }
        Bool16  IsScreenLoggingEnabled()        { return fScreenLoggingEnabled; }

        UInt32  GetMaxErrorLogBytes()           { return fErrorLogBytes; }
        UInt32  GetErrorRollIntervalInDays()    { return fErrorRollIntervalInDays; }
        UInt32  GetErrorLogVerbosity()          { return fErrorLogVerbosity; }
        void    SetErrorLogVerbosity(UInt32 verbosity)        { fErrorLogVerbosity = verbosity; }
        
        //
        // For UDP retransmits
        Bool16  GetRTSPDebugPrintfs()           { return fEnableRTSPDebugPrintfs; }
        Bool16  GetRTSPServerInfoEnabled()      { return fEnableRTSPServerInfo; }
        
        Float32    GetOverbufferRate()                { return fOverbufferRate; }
           
        //
        // force logs to close after each write (true or false)
        Bool16  GetCloseLogsOnWrite()           { return fCloseLogsOnWrite; }
        void    SetCloseLogsOnWrite(Bool16 closeLogsOnWrite);
                
        // String preferences. Note that the pointers returned here is allocated
        // memory that you must delete!
        
        char*   GetErrorLogDir()
            { return this->GetStringPref(qtssPrefsErrorLogDir); }
        char*   GetErrorLogName()
            { return this->GetStringPref(qtssPrefsErrorLogName); }

        char*   GetModuleDirectory()
            { return this->GetStringPref(qtssPrefsModuleFolder); }
            
        char*   GetLocalCameraAddress()
            { return this->GetStringPref(qtssPrefsLocalCameraAddress); }

        char*   GetRunUserName()
            { return this->GetStringPref(qtssPrefsRunUserName); }
        char*   GetRunPassword()
            { return this->GetStringPref(qtssPrefsRunPassword); }

        char*   GetPidFilePath()
            { return this->GetStringPref(qtssPrefsPidFile); }

        char*   GetStatsMonitorFileName()
            { return this->GetStringPref(qtssPrefsMonitorStatsFileName); }

        Bool16 ServerStatFileEnabled()      { return fEnableMonitorStatsFile; }
        UInt32 GetStatFileIntervalSec()     { return fStatsFileIntervalSeconds; }
        QTSS_AuthScheme GetAuthScheme()     { return fAuthScheme; }

                
        UInt32  GetNumThreads()                   { return fNumThreads; } //short tasks threads
        UInt32  GetNumBlockingThreads()           { return fNumRTSPThreads; } //return the number of threads that long tasks will be scheduled on -- RTSP processing for example.
        
        Bool16  GetDisableThinning()              { return fDisableThinning; }
        
        UInt16  GetDefaultStreamQuality()         { return fDefaultStreamQuality; }            
       
        Bool16 GetAllowGuestDefault()             { return fAllowGuestAuthorizeDefault; }  

		Bool16 GetCMSIP(char* outCMSIP);/*						  { return this->GetStringPref(qtssPrefsCMSIPAddr); }*/

		char* GetDeviceSerialNumber()			  { return this->GetStringPref(qtssPrefsSerialNumber); }
        
    private:

        UInt32      fConnectionTimeoutInSecs;
        char        fRTSPTimeoutBuf[20];
        StrPtrLen   fRTSPTimeoutString;

		char		fCMSIPAddr[20];
        UInt32      fCMSPort;
        
        SInt32  fMaximumConnections;
        SInt32  fMaxBandwidthInKBits;
        
        Bool16  fBreakOnAssert;
        Bool16  fAutoRestart;
        UInt32  fTBUpdateTimeInSecs;
        UInt32  fABUpdateTimeInSecs;
        UInt32  fLocalCameraPort;
        
        UInt32  fErrorRollIntervalInDays;
        UInt32  fErrorLogBytes;
        UInt32  fErrorLogVerbosity;
        Bool16  fScreenLoggingEnabled;
        Bool16  fErrorLogEnabled;  

        UInt32  fMinTCPBufferSizeInBytes;
        UInt32  fMaxTCPBufferSizeInBytes;
        Float32 fTCPSecondsToBuffer;

        Bool16  fDoReportHTTPConnectionAddress;

        QTSS_AuthScheme fAuthScheme;
        Bool16  fEnableRTSPErrMsg;
        Bool16  fEnableRTSPDebugPrintfs;
        Bool16  fEnableRTSPServerInfo;
        UInt32  fNumThreads;
        UInt32  fNumRTSPThreads;
        
        Bool16  fEnableMonitorStatsFile;
        UInt32  fStatsFileIntervalSeconds;
    
        Float32    fOverbufferRate;
        
        Bool16  fCloseLogsOnWrite;
        
        Bool16 fDisableThinning;
        
        UInt16 fDefaultStreamQuality;
        Bool16 fAllowGuestAuthorizeDefault;


        enum
        {
            kAllowMultipleValues = 1,
            kDontAllowMultipleValues = 0
        };
        
        struct PrefInfo
        {
            UInt32  fAllowMultipleValues;
            char*   fDefaultValue;
            char**  fAdditionalDefVals; // For prefs with multiple default values
        };
            
        void SetupAttributes();
        //
        // Returns the string preference with the specified ID. If there
        // was any problem, this will return an empty string.
        char* GetStringPref(QTSS_AttributeID inAttrID);
        
        static QTSSAttrInfoDict::AttrInfo   sAttributes[];
        static PrefInfo sPrefInfo[];
        
        // Prefs that have multiple default values (rtsp_ports) have
        // to be dealt with specially
        static char*    sAdditionalDefaultPorts[];       
};
#endif //__QTSSPREFS_H__

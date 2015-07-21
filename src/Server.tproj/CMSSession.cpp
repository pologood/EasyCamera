/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
/*
    File:       CMSSession.cpp

    Contains:   Implementation of class defined in RTCPTask.h
*/

#include "CMSSession.h"
#include "QTSServerInterface.h"

SInt64 CMSSession::Run()
{
	qtss_printf("CMSSession::Run() \n");
    return 5*1000;
}

/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
#include "EasyMediaSink.h"
#include "QTSServerInterface.h"
#include "QTSServer.h"

EasyMediaSink::EasyMediaSink()
:	Task(),
	fMutex()
{
	this->Signal(Task::kStartEvent);
}

EasyMediaSink::~EasyMediaSink(void)
{
	qtss_printf("~EasyMediaSink\n");
}

SInt64 EasyMediaSink::Run()
{
	QTSS_Error nRet = QTSS_NoErr;

	qtss_printf("EasyMediaSink::Run() \n");
	return 2*60*1000;
}
	

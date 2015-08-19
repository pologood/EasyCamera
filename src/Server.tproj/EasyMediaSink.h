/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
#ifndef _EASY_MEDIA_SINK_H_
#define _EASY_MEDIA_SINK_H_

#include "Task.h"
#include "QTSS.h"

class EasyMediaSink : public Task
{
public:
	EasyMediaSink();
	~EasyMediaSink(void);

	OSMutex*	GetMutex()      { return &fMutex; }
	
private:

	OSMutex fMutex;

	SInt64 Run();
};

#endif //_EASY_MEDIA_SINK_H_

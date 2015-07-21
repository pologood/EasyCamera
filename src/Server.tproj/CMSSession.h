/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
/*
    File:       CMSSession.h

    Contains:   

*/

#ifndef __CMS_SESSION_H__
#define __CMS_SESSION_H__

#include "Task.h"

class CMSSession : public Task
{
    public:
        //This task handles all incoming RTCP data. It just polls, so make sure
        //to start the polling process by signalling a start event.
        CMSSession() : Task() {this->SetTaskName("CMSSession"); this->Signal(Task::kStartEvent); }
        virtual ~CMSSession() {}
    
    private:
        virtual SInt64 Run();
};

#endif //__CMS_SESSION_H__

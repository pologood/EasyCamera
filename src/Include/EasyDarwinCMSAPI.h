/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
#ifndef _EasyDarwin_CMS_INTERFACE_H
#define _EasyDarwin_CMS_INTERFACE_H
#include "libClientCommondef.h"

#if (defined(_WIN32))
#ifndef _DLL_
#define EASYDARWIN_CMS_API
#else
#ifdef EASYDARWIN_CMS_API_EXPORTS
#define EASYDARWIN_CMS_API __declspec(dllexport) 
#else  
#define EASYDARWIN_CMS_API __declspec(dllimport)
#endif
#endif
#elif defined(__linux__)
#define EASYDARWIN_CMS_API
#endif

namespace EasyDarwin { namespace libEasyCMS
{

class EASYDARWIN_CMS_API EasyDarwinCMSAPI
{
public:
	EasyDarwinCMSAPI();
	~EasyDarwinCMSAPI(void);

private:
	void *m_callCenter;

public:
	//µÇÂ¼
	Easy_Error  Login(const char *szHost, int nPort, const char *szAccess, const char *szPassword);
};

}
}
#endif

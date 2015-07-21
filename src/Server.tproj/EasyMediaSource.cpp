/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
#include "EasyMediaSource.h"
#include "QTSServerInterface.h"
#include "QTSServer.h"

static unsigned int sLastVPTS = 0;
static unsigned int sLastAPTS = 0;

//摄像机音视频数据回调
HI_S32 NETSDK_APICALL OnStreamCallback(	HI_U32 u32Handle,		/* 句柄 */
										HI_U32 u32DataType,     /* 数据类型，视频或音频数据或音视频复合数据 */
										HI_U8*  pu8Buffer,      /* 数据包含帧头 */
										HI_U32 u32Length,		/* 数据长度 */
										HI_VOID* pUserData		/* 用户数据*/
									)						
{
	HI_S_AVFrame* pstruAV = HI_NULL;
	HI_S_SysHeader* pstruSys = HI_NULL;
	EasyMediaSource* pThis = (EasyMediaSource*)pUserData;

	if (u32DataType == HI_NET_DEV_AV_DATA)
	{
		pstruAV = (HI_S_AVFrame*)pu8Buffer;

		if (pstruAV->u32AVFrameFlag == HI_NET_DEV_VIDEO_FRAME_FLAG)
		{
			//qtss_printf("   PTS:%d increase:%d --\n",pstruAV->u32AVFramePTS, pstruAV->u32AVFramePTS - sLastVPTS);
			
			////qtss_printf("u32Length %u PTS: %u Len: %u \n", u32Length, pstruAV->u32AVFramePTS,pstruAV->u32AVFrameLen);
			//视频帧处理
			//fwrite(pu8Buffer+sizeof(HI_S_AVFrame),1,pstruAV->u32AVFrameLen,pThis->_f_264);
			//推送给MediaSink进行队列/缓冲/发送

			//强制要求第一帧为I关键帧
			if(pThis->m_bForceIFrame)
			{
				if(pstruAV->u32VFrameType == HI_NET_DEV_VIDEO_FRAME_I)
					pThis->m_bForceIFrame = false;
				else
					return HI_SUCCESS;
			}

			unsigned int vInter = pstruAV->u32AVFramePTS - sLastVPTS;

			sLastVPTS = pstruAV->u32AVFramePTS;
			//pThis->GetMediaSink()->PushPacket((char*)pu8Buffer, u32Length);
		}
		else if (pstruAV->u32AVFrameFlag == HI_NET_DEV_AUDIO_FRAME_FLAG)
		{
			//pThis->GetMediaSink()->PushPacket((char*)pu8Buffer, u32Length);
		}
	}	

	return HI_SUCCESS;
}

	
HI_S32 NETSDK_APICALL OnEventCallback(	HI_U32 u32Handle,	/* 句柄 */
										HI_U32 u32Event,	/* 事件 */
										HI_VOID* pUserData  /* 用户数据*/
                                )
{
	//if(HI_NET_DEV_NORMAL_DISCONNECTED == u32Event)
	//	pSamnetlibDlg->AlartData();
	//qtss_printf("Event Callback\n");
	return HI_SUCCESS;
}

HI_S32 NETSDK_APICALL OnDataCallback(	HI_U32 u32Handle,		/* 句柄 */
										HI_U32 u32DataType,		/* 数据类型*/
										HI_U8*  pu8Buffer,      /* 数据 */
										HI_U32 u32Length,		/* 数据长度 */
										HI_VOID* pUserData		/* 用户数据*/
                                )
{
	//CSamnetlibDlg *pSamnetlibDlg = (CSamnetlibDlg*)pUserData;
	//qtss_printf("Data Callback\n");
	//pSamnetlibDlg->AlartData();
	return HI_SUCCESS;
}


EasyMediaSource::EasyMediaSource()
:	Task(),
	m_u32Handle(0),
	fCameraLogin(false),//是否已登录标识
	m_bStreamFlag(false),//是否正在流媒体标识
	m_bForceIFrame(true)
{
	//SDK初始化，全局调用一次
	HI_NET_DEV_Init();
	this->Signal(Task::kStartEvent);
}

EasyMediaSource::~EasyMediaSource(void)
{
	qtss_printf("~EasyMediaSource\n");
	
	//先停止Stream，内部有是否在Stream的判断
	NetDevStopStream();

	if(fCameraLogin)
		HI_NET_DEV_Logout(m_u32Handle);

	//SDK释放，全局调用一次
	HI_NET_DEV_DeInit();
}

bool EasyMediaSource::CameraLogin()
{
	//如果已登录，返回true
	if(fCameraLogin) return true;
	//登录到摄像机
	HI_S32 s32Ret = HI_SUCCESS;
	s32Ret = HI_NET_DEV_Login(	&m_u32Handle,"admin","admin","192.168.66.119",80);

	if (s32Ret != HI_SUCCESS)
	{
		qtss_printf("HI_NET_DEV_Login Fail\n");
		m_u32Handle = 0;
		return false;
	}
	else
	{
		HI_NET_DEV_SetReconnect(m_u32Handle, 5000);
		fCameraLogin = true;
	}

	return true;
}

QTSS_Error EasyMediaSource::NetDevStartStream()
{
	//如果未登录,返回失败
	if(!CameraLogin()) return QTSS_RequestFailed;
	
	//已经在流传输中，返回Easy_AttrNameExists
	if(m_bStreamFlag) return QTSS_AttrNameExists;

	OSMutexLocker locker(this->GetMutex());

	QTSS_Error theErr = QTSS_NoErr;
	HI_S32 s32Ret = HI_SUCCESS;
	HI_S_STREAM_INFO struStreamInfo;

	HI_NET_DEV_SetEventCallBack(m_u32Handle, (HI_ON_EVENT_CALLBACK)OnEventCallback, this);
	HI_NET_DEV_SetStreamCallBack(m_u32Handle, (HI_ON_STREAM_CALLBACK)OnStreamCallback, this);
	HI_NET_DEV_SetDataCallBack(m_u32Handle, (HI_ON_DATA_CALLBACK)OnDataCallback, this);

	struStreamInfo.u32Channel = HI_NET_DEV_CHANNEL_1;
	struStreamInfo.blFlag = HI_FALSE;
	struStreamInfo.u32Mode = HI_NET_DEV_STREAM_MODE_TCP;
	struStreamInfo.u8Type = HI_NET_DEV_STREAM_ALL;
	s32Ret = HI_NET_DEV_StartStream(m_u32Handle, &struStreamInfo);
	if (s32Ret != HI_SUCCESS)
	{
		qtss_printf("HI_NET_DEV_StartStream Fail\n");
		return QTSS_RequestFailed;
	}

	m_bStreamFlag = true;
	m_bForceIFrame = true;
	qtss_printf("HI_NET_DEV_StartStream SUCCESS\n");

	return QTSS_NoErr;
}

void EasyMediaSource::NetDevStopStream()
{
	if( m_bStreamFlag )
	{
		qtss_printf("HI_NET_DEV_StopStream\n");
		HI_NET_DEV_StopStream(m_u32Handle);
		m_bStreamFlag = false;
		//m_bForceIFrame = false;
	}
}

void EasyMediaSource::handleClosure(void* clientData) 
{
	if(clientData != NULL)
	{
		EasyMediaSource* source = (EasyMediaSource*)clientData;
		source->handleClosure();
	}
}

void EasyMediaSource::handleClosure() 
{
	if (fOnCloseFunc != NULL) 
	{
		(*fOnCloseFunc)(fOnCloseClientData);
	}
}

void EasyMediaSource::stopGettingFrames() 
{
	OSMutexLocker locker(this->GetMutex());
	fOnCloseFunc = NULL;
	doStopGettingFrames();
}

void EasyMediaSource::doStopGettingFrames() 
{
	qtss_printf("doStopGettingFrames()\n");
	NetDevStopStream();
}

bool EasyMediaSource::GetSnapData(unsigned char* pBuf, UInt32 uBufLen, int* uSnapLen)
{
	//如果摄像机未登录，返回false
	if(!CameraLogin()) return false;

	//调用SDK获取数据
	HI_S32 s32Ret = HI_FAILURE; 
	s32Ret = HI_NET_DEV_SnapJpeg(m_u32Handle, (HI_U8*)pBuf, uBufLen, uSnapLen);
	if(s32Ret == HI_SUCCESS)
	{
		return true;
	}

	return false;
}

SInt64 EasyMediaSource::Run()
{
	printf("EasyMediaSource::Run Test\n");

	QTSS_Error nRet = QTSS_NoErr;

	do{
		//向设备获取快照数据
		unsigned char *sData = (unsigned char*)malloc(EASY_SNAP_BUFFER_SIZE);
		int snapBufLen = 0;

		//如果获取到摄像机快照数据，Base64编码/发送
		if(!GetSnapData(sData, EASY_SNAP_BUFFER_SIZE, &snapBufLen))
		{
			//未获取到数据
			qtss_printf("EasyDeviceCenter::UpdateDeviceSnap => Get Snap Data Fail \n");
			nRet = QTSS_ValueNotFound;
			break;
		}

		QTSServer* svr = (QTSServer*)QTSServerInterface::GetServer();
		svr->GetCMSApi()->UpdateSnap((const char*)sData, snapBufLen);

		free((void*)sData);
		sData = NULL;

	}while(0);

	return 10*1000;
}
	

/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
#ifndef __EasyPusher_H__
#define __EasyPusher_H__

#ifdef _WIN32
#define EasyPusher_API  __declspec(dllexport)
#define Easy_APICALL  __stdcall
#else
#define EasyPusher_API
#define Easy_APICALL 
#endif

#define Easy_Pusher_Handle void*

typedef unsigned char           Pusher_U8;
typedef unsigned char           Pusher_UCHAR;
typedef unsigned short          Pusher_U16;
typedef unsigned int            Pusher_U32;

enum
{
    Pusher_NoErr						= 0,
    Pusher_RequestFailed				= -1,
    Pusher_Unimplemented				= -2,
    Pusher_RequestArrived				= -3,
    Pusher_OutOfState					= -4,
    Pusher_NotAModule					= -5,
    Pusher_WrongVersion					= -6,
    Pusher_IllegalService				= -7,
    Pusher_BadIndex						= -8,
    Pusher_ValueNotFound				= -9,
    Pusher_BadArgument					= -10,
    Pusher_ReadOnly						= -11,
	Pusher_NotPreemptiveSafe			= -12,
    Pusher_NotEnoughSpace				= -13,
    Pusher_WouldBlock					= -14,
    Pusher_NotConnected					= -15,
    Pusher_FileNotFound					= -16,
    Pusher_NoMoreData					= -17,
    Pusher_AttrDoesntExist				= -18,
    Pusher_AttrNameExists				= -19,
    Pusher_InstanceAttrsNotAllowed		= -20,
	Pusher_InvalidSocket				= -21,
	Pusher_MallocError					= -22,
	Pusher_ConnectError					= -23,
	Pusher_SendError					= -24
};
typedef int Pusher_Error;

/* 音视频编码 */
#define EASY_SDK_VIDEO_CODEC_H264	0x01000001		/* H264 */
#define EASY_SDK_AUDIO_CODEC_AAC	0x01000011		/* AAC */
#define EASY_SDK_AUDIO_CODEC_G711	0x01000012		/* G711 */
#define EASY_SDK_AUDIO_CODEC_G726	0x01000013		/* G726 */

/* 音视频帧标识 */
#define EASY_SDK_VIDEO_FRAME_FLAG	0x02000001	/* 视频帧标志 */
#define EASY_SDK_AUDIO_FRAME_FLAG	0x02000002	/* 音频帧标志 */

/* 视频关键字标识 */
#define EASY_SDK_VIDEO_FRAME_I		0x03000001	/* 关键帧 */
#define EASY_SDK_VIDEO_FRAME_P		0x03000002	/* 非关键帧 */

typedef struct __EASY_AV_Frame
{
    Pusher_U32    u32AVFrameFlag;		/* 帧标志  视频 or 音频 */
    Pusher_U32    u32AVFrameLen;		/* 帧的长度 */
    Pusher_U32    u32VFrameType;		/* 视频的类型，I帧或P帧 */
    Pusher_U8     *pBuffer;				/* 数据 */
}EASY_AV_Frame;

typedef struct __EASY_MEDIA_INFO_T
{
	Pusher_U32 u32VideoCodec;			/* 视频编码类型 */
	Pusher_U32 u32VideoFps;				/* 视频帧率 */
	
	Pusher_U32 u32AudioCodec;			/* 音频编码类型 */
	Pusher_U32 u32AudioSamplerate;		/* 音频采样率 */
	Pusher_U32 u32AudioChannel;			/* 音频通道数 */
}EASY_MEDIA_INFO_T;

/* 推送事件类型定义 */
typedef enum __EASY_PUSH_STATE_T
{
    EASY_PUSH_STATE_CONNECTING   =   1,     /* 连接中 */
    EASY_PUSH_STATE_CONNECTED,              /* 连接成功 */
    EASY_PUSH_STATE_CONNECT_FAILED,         /* 连接失败 */
    EASY_PUSH_STATE_CONNECT_ABORT,          /* 连接异常中断 */
    EASY_PUSH_STATE_PUSHING,                /* 推流中 */
    EASY_PUSH_STATE_DISCONNECTED,           /* 断开连接 */
    EASY_PUSH_STATE_ERROR
}EASY_PUSH_STATE_T;

/* 推送回调函数定义 _userptr表示用户自定义数据 */
typedef int (*EasyPusher_Callback)(int _id, EASY_PUSH_STATE_T _state, EASY_AV_Frame *_frame, void *_userptr);

#ifdef __cplusplus
extern "C"
{
#endif

	/* 创建推送句柄  返回为句柄值 */
	EasyPusher_API Easy_Pusher_Handle Easy_APICALL EasyPusher_Create();
	
	/* 释放推送句柄 */
	EasyPusher_API Pusher_U32 Easy_APICALL EasyPusher_Release(Easy_Pusher_Handle handle);

    /* 设置流传输事件回调 userptr传输自定义对象指针*/
    EasyPusher_API Pusher_U32 Easy_APICALL EasyPusher_SetEventCallback(Easy_Pusher_Handle handle,  EasyPusher_Callback callback, int id, void *userptr);

	/* 开始流传输 serverAddr:流媒体服务器地址、port:流媒体端口、streamName:流名称<xxx.sdp>、username/password:推送携带的用户名密码、pstruStreamInfo:推送的媒体定义、bufferKSize:以k为单位的缓冲区大小<512~2048之间,默认512> */
	EasyPusher_API Pusher_U32 Easy_APICALL EasyPusher_StartStream(Easy_Pusher_Handle handle, char* serverAddr, Pusher_U16 port, char* streamName, char *username, char *password, EASY_MEDIA_INFO_T*  pstruStreamInfo, Pusher_U32 bufferKSize);

	/* 停止流传输 */
	EasyPusher_API Pusher_U32 Easy_APICALL EasyPusher_StopStream(Easy_Pusher_Handle handle);

	/* 推流 frame:具体推送的流媒体帧 */
	EasyPusher_API Pusher_U32 Easy_APICALL EasyPusher_PushFrame(Easy_Pusher_Handle handle, EASY_AV_Frame* frame );

#ifdef __cplusplus
}
#endif


#endif

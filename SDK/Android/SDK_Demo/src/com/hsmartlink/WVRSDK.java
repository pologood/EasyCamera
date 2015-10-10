package com.hsmartlink;

public class WVRSDK
{
	static
	{
		System.loadLibrary("PPPP_API");
		System.loadLibrary("StreamPlayLib");
		System.loadLibrary("NasClientNetLib");
		System.loadLibrary("jni_nas");
	}

	// 初始化库
	public native static int InitLib();

	// 释放库资源
	public native static int UnInitLib();

	// 检测网络
	public native static int NetworkDetect();

	// 设置参数事件回调
	public native static int SetCallBack(Object UserContext);

	/*
	 * Function: 创建通讯实例, strDid、trHost不能同时为空 strUsername 登录用户名 strPwd 登录密码
	 * strHost 设备IP nPort 端口 strDid 设备ID NetType 连接方式 0/1:Tcp/p2p
	 * 
	 * @RETURN >=0成功，负数为错误类型
	 */
	public native static int CreateInstance(String strUsername, String strPwd,
			String strHost, int nPort, String StrDid, int NetType);

	/*
	 * Function: 释放通讯实例 userid CreateInstance的返回值
	 */
	public native static int DestroyInstance(int userid);

	// 启动通讯实例
	public native static int Start(int userid);

	// 停止通讯实例工作
	public native static int Stop(int userid);

	// 获取设备参数
	public native static int GetParam(int userid, int nType);

	// 设置设备参数
	public native static int SetParam(int userid, int nType, String param);
	/**
	 * 
	 * @param userid
	 * @param channel
	 * @param cmd 
	 * @return
	 */
	public native static int PtzControl(int userid, int channel, int cmd);

	/*
	 * Function: 请求视频流 userid CreateInstance返回值 streamid 80/81/82 主/子/次码流
	 * channel 通道号
	 * 
	 * @RETURN 0失败，>0请求成功
	 */
	public native static int StartStream(int userid, int streamid, int channel);

	// 关闭视频流
	public native static int StopStream(int userid, int channel);
	
	public native static int SetLiveRender(int userid, Object render);
	// 搜索设备初始化
	public native static int SearchDeviceInit();

	// 搜索设备资源释放
	public native static int SearchDeviceUninit();

	// 设置搜索数据回调对象
	public native static int SetSearchCallBack(Object UserContext);

	// 搜索设备
	public native static int SearchDevice();

	/*
	 * 打开监听 audioid=1 channel 通道号
	 */
	public native static int StartAudio(int userid, int audioid, int channel);

	// 关闭监听
	public native static int StopAudio(int userid, int channel);
}

package hsl.p2pipcam.manager;

import com.hsmartlink.WVRSDK;

public class WvrDeviceSDK 
{
	/**
	 * 初始化
	 * @param serv
	 * @return
	 */
	public static int initializeWvr(String serv)
	{
		return WVRSDK.InitLib();
	}
	
	public static int unInitLibWvr()
	{
		return WVRSDK.UnInitLib();
	}
	
	public static int NetworkDetect()
	{
		return WVRSDK.NetworkDetect();
	}
	/**
	 * 设置回调对象
	 * @param object
	 */
	public static void setWvrCallback(Object object)
	{
		WVRSDK.SetCallBack(object);
	}
	
	/**
	 * 创建设备
	 * @param strUsername
	 * @param strPwd
	 * @param strHost
	 * @param nPort
	 * @param StrDid
	 * @param NetType 0=TCP ,1=P2P
	 * @return userid
	 */
	public static long createWvrDevice(String strUsername, String strPwd,String strHost, int nPort, String StrDid, int NetType)
	{
		return WVRSDK.CreateInstance(strUsername, strPwd, strHost, nPort, StrDid, NetType);
	}
	
	/**
	 * 销毁设备
	 * @param UserID
	 * @return
	 */
	public static int destoryWvrDevice(long UserID)
	{
		return WVRSDK.DestroyInstance((int)UserID);
	}
	
	/**
	 * 设备开启
	 * @param userID
	 * @return
	 */
	public static int openWvrDevice(long userID)
	{
		return WVRSDK.Start((int)userID);
	}
	
	public static void setWvrRender(long userid, Object render)
	{
		WVRSDK.SetLiveRender((int)userid, render);
	}
	/**
	 * 设备关闭
	 * @param userID
	 * @return
	 */
	public static int closeWvrDevice(long userID)
	{
		return WVRSDK.Stop((int)userID);
	}
	
	public static int startPlayStream(long userid, int streamid, int channel)
	{
		return WVRSDK.StartStream((int)userid, streamid, channel);
	}
	
	public static int stopPlayStream(long userid, int channel)
	{
		return WVRSDK.StopStream((int)userid, channel);
	}
	
	public static int startPlayAudio(long userid, int audioid, int channel)
	{
		return WVRSDK.StartAudio((int)userid, audioid, channel);
	}
	
	public static int stopPlayAudio(long userid,int channel)
	{
		return WVRSDK.StopAudio((int)userid, channel);
	}
	
	/**
	 * 获取设备参数
	 * @param userID
	 * @param nType
	 * @return
	 */
	public static int getWvrDeviceParam(long userID,int nType)
	{
		return WVRSDK.GetParam((int)userID, nType);
	}
	
	/**
	 * 设置设备参数
	 * @param userID
	 * @param nType
	 * @param param
	 * @return
	 */
	public static int setWvrDeviceParam(long userID,int nType,String param)
	{
		return WVRSDK.SetParam((int)userID, nType, param);
	}
	
	public static void ptzControlWvrDevice(int userid, int channel, int cmd)
	{
		WVRSDK.PtzControl(userid, channel, cmd);
	}
}

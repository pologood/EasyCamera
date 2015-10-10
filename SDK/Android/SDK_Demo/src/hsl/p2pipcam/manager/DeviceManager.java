/**
 * 
 */
package hsl.p2pipcam.manager;

import hsl.p2pipcam.manager.listener.DeviceStatusListener;
import hsl.p2pipcam.manager.listener.PlayListener;
import hsl.p2pipcam.manager.listener.RecorderListener;
import android.content.Context;

/**
 * 设备管理器
 * @author wang.jingui
 *
 */
public class DeviceManager 
{
	//监听回调接口
	private DeviceStatusListener deviceStatusListener;
	private PlayListener playListener;
	private RecorderListener recorderListener;
	//设备列表
	//上下文
	private Context context;
	private WvrDeviceManager wvrDeviceManager;
	private static DeviceManager instance;
	public static DeviceManager getDeviceManager(Context context)
	{
		if(instance == null)
			instance = new DeviceManager(context);
		return instance;
	}
	
	public DeviceManager(Context context)
	{
		this.context = context;
		wvrDeviceManager = new WvrDeviceManager(this);
	}

	public void initialize()
	{
		
		DeviceSDK.initialize("");
		DeviceSDK.setCallback(this);
		DeviceSDK.networkDetect();
		
		WvrDeviceSDK.initializeWvr("");
		WvrDeviceSDK.setWvrCallback(wvrDeviceManager);
		WvrDeviceSDK.NetworkDetect();
		
	}
	
	public void unInitSearchDevice()
	{
		DeviceSDK.unInitSearchDevice();
	}


	public void setDeviceStatusListener(DeviceStatusListener deviceStatusListener) {
		this.deviceStatusListener = deviceStatusListener;
		wvrDeviceManager.setDeviceStatusListener(deviceStatusListener);
	}

	public void setPlayListener(PlayListener playListener) {
		this.playListener = playListener;
	}


	public void setRecorderListener(RecorderListener recorderListener) {
		this.recorderListener = recorderListener;
	}

	//-------------------------------------------------------------------------
	//---------------------------以下是JNI层回调的接口-------------------------------
	//-------------------------------------------------------------------------
	
	public void CallBack_SnapShot(long UserID, byte[] buff, int len)
	{}
	
	
	public void CallBack_GetParam(long UserID, long nType, String param) 
	{}
	

	public void CallBack_SetParam(long UserID, long nType, int nResult) 
	{
		
	}
	public void CallBack_Event(long UserID, long nType) 
	{
		int status = new Long(nType).intValue();
		if(deviceStatusListener != null)
			deviceStatusListener.receiveDeviceStatus(UserID,status);
	}
	
	public void VideoData(long UserID, byte[] VideoBuf, int h264Data, int nLen, int Width, int Height, int time) 
	{
		
	}
	
	public void callBackAudioData(long nUserID, byte[] pcm, int size)
	{
		if(playListener != null)
			playListener.callBackAudioData(nUserID, pcm, size);
		if(recorderListener != null)
			recorderListener.callBackAudioData(nUserID, pcm, size);
	}
	
	public void CallBack_RecordFileList(long UserID, int filecount, String fname, String strDate, int size)
	{}
	
	public void CallBack_P2PMode(long UserID, int nType)
	{
	}

	public void CallBack_RecordPlayPos(long userid, int pos)
	{}

	public void CallBack_VideoData(long nUserID, byte[] data, int type, int size) {}
	
	public void CallBack_AlarmMessage(long UserID, int nType) 
	{}
	
	
	public void showNotification(String message, Device device,int nType)
	{}
}

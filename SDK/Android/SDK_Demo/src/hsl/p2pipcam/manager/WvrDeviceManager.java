package hsl.p2pipcam.manager;

import hsl.p2pipcam.manager.listener.DeviceStatusListener;

public class WvrDeviceManager 
{
	private DeviceStatusListener deviceStatusListener;
	
	
	private DeviceManager deviceManager;
	
	
	public WvrDeviceManager(DeviceManager deviceManager) {
		this.deviceManager = deviceManager;
	}

	public void setDeviceStatusListener(DeviceStatusListener deviceStatusListener) {
		this.deviceStatusListener = deviceStatusListener;
	}


	

	public void CallBack_GetParam(int UserID, int nType, String json) 
	{}
	public void CallBack_SetParam(int UserID, int nType, int nResult) {}
	
	/**
	 * 100在线
	 * 
	 * @param UserID
	 * @param nType
	 */
	public void CallBack_Event(int UserID, int status) 
	{}
	public void CallBack_P2PMode(int UserID, int nType) 
	{
		
	}
	public void CallBack_AlarmMessage(int UserID, int nType) {

	}
	public void CallBack_SearchDevice(String param){}

}

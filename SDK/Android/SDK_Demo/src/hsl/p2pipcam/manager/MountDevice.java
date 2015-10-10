package hsl.p2pipcam.manager;

import hsl.p2pipcam.bean.DeviceModel;

public class MountDevice 
{
	private static final int P2P = 1;
	private DeviceModel deviceModel;
	private long userid;
	private String name;
	private int channel;
	
	/**
	 * 创建wvr挂载设备
	 * @return
	 */
	public long createWvrMountDevice()
	{
		long userid = -1;
		userid = WvrDeviceSDK.createWvrDevice(deviceModel.getUsername(), deviceModel.getPassword(), deviceModel.getDevIP(), deviceModel.getPort(), deviceModel.getDevID(), P2P);
		if(userid >= 0 )
		{
			int start = WvrDeviceSDK.openWvrDevice(userid);
			if(start>0)
				this.userid = userid;
		}
		return userid;
	}
	
	/**
	 * 销毁wvr挂载设备
	 * @param userid
	 */
	public void destoryWvrMountDevice()
	{
		WvrDeviceSDK.closeWvrDevice(userid);
		WvrDeviceSDK.destoryWvrDevice(userid);
	}
	
	public void setWvrRender(Object render)
	{
		WvrDeviceSDK.setWvrRender(userid, render);
	}
	
	/**
	 * 开启wvr视频流
	 * @param streamid
	 * @param channel
	 */
	public void startPlayWvrStream(int streamid)
	{
		WvrDeviceSDK.startPlayStream(userid, streamid, channel);
	}
	
	/**
	 * 结束wvr视频流
	 * @param channel
	 */
	public void stopPlayWvrStream()
	{
		WvrDeviceSDK.stopPlayStream(userid, channel);
	}
	
	/**
	 * 打开wvr监听 audioid=1 channel 通道号
	 * @param channel
	 */
	public void startPlayWvrAudio()
	{
		WvrDeviceSDK.startPlayAudio(userid, 1, channel);
	}
	
	/**
	 * 关闭wvr监听
	 * @param channel
	 */
	public void stopPlayWvrAudio()
	{
		WvrDeviceSDK.stopPlayAudio(userid, channel);
	}
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public int getChannel() {
		return channel;
	}
	public void setChannel(int channel) {
		this.channel = channel;
	}
	public long getUserid() {
		return userid;
	}
	public void setUserid(long userid) {
		this.userid = userid;
	}
	public void setDeviceModel(DeviceModel deviceModel) {
		this.deviceModel = deviceModel;
	}
	
	
	
}

/**
 * 
 */
package hsl.p2pipcam.manager;

import hsl.p2pipcam.bean.ContantsModel;
import hsl.p2pipcam.bean.DeviceModel;
import hsl.p2pipcam.component.MyRender;
import hsl.p2pipcam.util.AudioPlayer;
import hsl.p2pipcam.util.CustomAudioRecorder;
import hsl.p2pipcam.util.CustomAudioRecorder.AudioRecordResult;
import hsl.p2pipcam.util.CustomBuffer;
import hsl.p2pipcam.util.CustomBufferData;

import java.util.Calendar;

import org.json.JSONException;
import org.json.JSONObject;

import android.graphics.Bitmap;

/**
 * @author wang.jingui
 *
 */
public class Device implements AudioRecordResult
{
	private static final int P2P = 1;
	private DeviceModel deviceModel;
	private int status = -1;
	private long userid;
	private Bitmap bitmap;
	private String systemUser="";
	private String systemPasswd="";
	private int streamType = 10;
	
	private boolean isPlaying = false;
	private int zoneArming = 0;
	

	private AudioPlayer audioPlayer;
	private CustomBuffer AudioBuffer ;
	private CustomAudioRecorder customAudioRecorder;
	
	public Device() {
		AudioBuffer = new CustomBuffer();
		audioPlayer = new AudioPlayer(AudioBuffer);
	}
	public void createDevice()
	{
		if(deviceModel.getDeviceType() == ContantsModel.DeviceType.SWITCH || deviceModel.getDeviceType() == ContantsModel.DeviceType.CLOUD_BOX)
		{
			
			long userid = WvrDeviceSDK.createWvrDevice(deviceModel.getUsername(), deviceModel.getPassword(), deviceModel.getDevIP(), deviceModel.getPort(), deviceModel.getDevID(), P2P);
			if(userid >= 0 )
			{
				int start = WvrDeviceSDK.openWvrDevice(userid);
				if(start>0)
				{
					this.userid = userid;
				}
			}
		}
		else
		{
			long userid = DeviceSDK.createDevice(deviceModel.getUsername(), deviceModel.getPassword(), deviceModel.getDevIP(), deviceModel.getPort(), deviceModel.getDevID(), P2P);
			if(userid > 0 )
			{
				int start = DeviceSDK.openDevice(userid);
				if(start>0)
				{
					this.userid = userid;
				}
			}
		}
	}
	public void reOpenDevice()
	{
		try
		{
			if(deviceModel.getDeviceType() == ContantsModel.DeviceType.SWITCH || deviceModel.getDeviceType() == ContantsModel.DeviceType.CLOUD_BOX)
			{
				WvrDeviceSDK.closeWvrDevice(userid);
				Thread.sleep(50);
				WvrDeviceSDK.openWvrDevice(userid);
			}
			else
			{
				DeviceSDK.closeDevice(userid);
				Thread.sleep(50);
				DeviceSDK.openDevice(userid);
				Thread.sleep(50);
			}
			
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	public void destoryDevice()
	{
		if(deviceModel.getDeviceType() == ContantsModel.DeviceType.SWITCH || deviceModel.getDeviceType() == ContantsModel.DeviceType.CLOUD_BOX)
		{
			WvrDeviceSDK.closeWvrDevice(userid);
			WvrDeviceSDK.destoryWvrDevice(userid);
		}
		else
		{
			DeviceSDK.closeDevice(userid);
			DeviceSDK.destoryDevice(userid);
		}
	}
	

	public void startPlayStream(int resolution)
	{
		DeviceSDK.startPlayStream(userid, streamType, resolution);
	}

	public void stopPlayStream()
	{
		DeviceSDK.stopPlayStream(userid);
	}

	public void setRender(MyRender render)
	{
		DeviceSDK.setRender(userid, render);
	}
	
	public void startPlayAudio()
	{
		AudioBuffer.ClearAll();
		audioPlayer.AudioPlayStart();
		DeviceSDK.startPlayAudio(userid,1);
	}

	public void stopPlayAudio()
	{
		DeviceSDK.stopPlayAudio(userid);
		AudioBuffer.ClearAll();
		audioPlayer.AudioPlayStop();
	}

	public void addAudioData(CustomBufferData dataModel)
	{
		if(audioPlayer.isAudioPlaying())
			AudioBuffer.addData(dataModel);
	}
	
	public void initRecorder()
	{
		customAudioRecorder = new CustomAudioRecorder(this);
	}

	public void startTalk()
	{
		DeviceSDK.startTalk(userid);
		customAudioRecorder.StartRecord();
	}

	public void stopTalk()
	{
		DeviceSDK.stopTalk(userid);
		customAudioRecorder.StopRecord();
	}
	
	public void releaseRecord()
	{
		customAudioRecorder.releaseRecord();
	}

	public void sendTalkData(byte[] data, int size)
	{
		DeviceSDK.SendTalkData(userid, data, size);
	}
	
	public void setCameraParam(int param,int value)
	{
		try 
		{
			JSONObject obj = new JSONObject();
			obj.put("param", param);
			obj.put("value", value);
			DeviceSDK.setDeviceParam(userid, ContantsModel.Param.SET_CAMERA_PARAMS, obj.toString());
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	//---------------------------------EDN-------------------------------------------------//

	@Override
	public void AudioRecordData(byte[] data, int len) {
		sendTalkData(data, len);
	}

	public DeviceModel getDeviceModel() {
		return deviceModel;
	}

	public void setDeviceModel(DeviceModel deviceModel) {
		this.deviceModel = deviceModel;
	}

	public int getStatus() {
		return status;
	}

	public void setStatus(int status) {
		this.status = status;
	}

	public Bitmap getBitmap() {
		return bitmap;
	}

	public void setBitmap(Bitmap bitmap) {
		this.bitmap = bitmap;
	}

	public long getUserid() {
		return userid;
	}

	public String getSystemUser() {
		return systemUser;
	}

	public void setSystemUser(String systemUser) {
		this.systemUser = systemUser;
	}

	public String getSystemPasswd() {
		return systemPasswd;
	}

	public void setSystemPasswd(String systemPasswd) {
		this.systemPasswd = systemPasswd;
	}

	public boolean isPlaying() {
		return isPlaying;
	}

	public void setPlaying(boolean isPlaying) {
		this.isPlaying = isPlaying;
	}

	public int getZoneArming() {
		return zoneArming;
	}

	public void setZoneArming(int zoneArming) {
		this.zoneArming = zoneArming;
	}
	
}

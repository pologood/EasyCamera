package hsl.p2pipcam.manager.listener;

import hsl.p2pipcam.manager.Device;

import java.util.List;

import android.graphics.Bitmap;

public interface DeviceStatusListener {
	public void receiveDeviceStatus(long userid,int status);
	public void receiveDeviceImage(long userid,Bitmap bitmap);
	public void loadListData(List<Device> data);
	public void receiveDeviceZoneArming(long userid,int zone_arming);
}

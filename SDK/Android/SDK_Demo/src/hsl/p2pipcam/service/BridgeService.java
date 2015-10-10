/**
 * 
 */
package hsl.p2pipcam.service;


import hsl.p2pipcam.manager.DeviceManager;

import java.text.SimpleDateFormat;
import java.util.Date;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import android.widget.RemoteViews;

import com.test.R;

/**
 *@author wang.jingui
 */
public class BridgeService extends Service
{
	private DeviceManager deviceManager;
	private NotificationManager mCustomMgr;
	@Override
	public IBinder onBind(Intent arg0)
	{
		return null;
	}

	@Override
	public void onCreate()
	{
		super.onCreate();
		initDeviceManager();
	}
	
	private void initDeviceManager()
	{
		deviceManager = DeviceManager.getDeviceManager(this.getApplicationContext());
		new Thread(){
			@Override
			public void run() {
				deviceManager.initialize();
			}
		}.start();
	}

	@Override
	public void onDestroy() {
		mCustomMgr.cancel(1514);
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) 
	{
		return super.onStartCommand(intent, flags, startId);
	}
	
	
}

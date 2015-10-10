package hsl.p2pipcam.activity;

import hsl.p2pipcam.bean.ContantsModel;
import hsl.p2pipcam.component.MyRender;
import hsl.p2pipcam.component.MyRender.RenderListener;
import hsl.p2pipcam.manager.Device;
import hsl.p2pipcam.manager.DeviceManager;
import hsl.p2pipcam.manager.listener.PlayListener;
import hsl.p2pipcam.util.CustomBufferData;
import hsl.p2pipcam.util.CustomBufferHead;
import android.opengl.GLSurfaceView;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.LinearLayout;

import com.test.R;

public class DevicePlayActivity extends BaseActivity implements PlayListener,RenderListener{
	private GLSurfaceView glSurfaceView;
	private MyRender myRender;
	private LinearLayout progressLayout;
	private Button audioItem;
	private Button recordItem;
	
	private DeviceManager deviceManager;
	private Device device;
	//开启监听
	private boolean isAudio = true;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.play_screen);
		deviceManager = DeviceManager.getDeviceManager(getApplicationContext());
		deviceManager.setPlayListener(this);
		device = TestActivity.device;
		device.initRecorder();
		initView();
		new LoadTask().execute();
		
	}
	
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		device.stopPlayAudio();
		device.stopPlayStream();
		device.releaseRecord();
	}
	private void initView()
	{
		glSurfaceView = (GLSurfaceView)findViewById(R.id.glsurfaceview);
		myRender = new MyRender(glSurfaceView);
		myRender.setListener(this);
		glSurfaceView.setRenderer(myRender);
		progressLayout = (LinearLayout)findViewById(R.id.progressLayout);
		
		audioItem = (Button)findViewById(R.id.audio_item);
		recordItem = (Button)findViewById(R.id.record_item);
		
		audioItem.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				openAudio();
			}
		});
		recordItem.setOnTouchListener(new OnTouchListener() {
			
			@Override
			public boolean onTouch(View arg0, MotionEvent event) {
				if (event.getAction() == MotionEvent.ACTION_DOWN)
				{
					device.stopPlayAudio();
					device.startTalk();
					device.stopTalk();
					device.startTalk();
					showToast("对讲中...");
				} 
				else if (event.getAction() == MotionEvent.ACTION_UP) 
				{
					
					device.stopTalk();
					if(!isAudio)
						device.startPlayAudio();
				}
				return false;
			}
		});
		
	}
	
	/**
	 * 开启监听
	 */
	private void openAudio()
	{
		if(isAudio)
		{
			isAudio = false;
			device.startPlayAudio();
			audioItem.setText("关闭监听");
		}
		else
		{
			isAudio = true;
			device.stopPlayAudio();
			audioItem.setText("开启监听");
		}
	}
	private Handler frushHandler = new Handler()
	{
		@Override
		public void handleMessage(Message msg) {
			super.handleMessage(msg);
			progressLayout.setVisibility(View.GONE);
		}
	};
	@Override
	public void cameraGetParamsResult(long userid, String cameraParams) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void callBackAudioData(long userID, byte[] pcm, int size) {
		if(userID == device.getUserid())
		{
			CustomBufferHead head = new CustomBufferHead();
			CustomBufferData data = new CustomBufferData();
			head.length = size;
			head.startcode = 0xff00ff;
			data.head = head;
			data.data = pcm;
			device.addAudioData(data);
		}
		
	}
	@Override
	public void callBackVideoData(long userID, byte[] data, int type, int size) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void smartAlarmCodeGetParamsResult(long userid, String params) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void smartAlarmNotify(long userid, String message) {
		// TODO Auto-generated method stub
		
	}
	
	private class LoadTask extends AsyncTask<Void, Void, Void>
	{

		@Override
		protected Void doInBackground(Void... arg0) {
			device.setRender(myRender);
			device.startPlayStream(ContantsModel.MidResolution);
			device.setCameraParam(13, 1024);
			device.setCameraParam(6, 15);
			return null;
		}
		
	}

	@Override
	public void initComplete(int size, int width, int height) {
		// TODO Auto-generated method stub
		frushHandler.sendEmptyMessage(0);
	}

	@Override
	public void takePicture(byte[] imageBuffer, int width, int height) {
		// TODO Auto-generated method stub
		
	} 
}

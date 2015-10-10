/**
 * 
 */
package hsl.p2pipcam.util;

import hsl.p2pipcam.manager.Device;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;

/**
 * 录音
 * @author wang.jingui
 *
 */
public class AudioRecorder {
	
	private AudioRecord audioRecord = null;
	private int bufferLen = 0;
	private byte[] buffer = null;
	private boolean isRecording = false;
	private RecordThread recordThread;
	private Device device;
	
	public AudioRecorder(Device device) {
		super();
		this.device = device;
		initRecorder();
	}

	public void startRecorder()
	{
		isRecording = true;
		recordThread = new RecordThread();
		recordThread.start();
	}
	
	public void stopRecorder()
	{
		isRecording = false;
		audioRecord.stop();
		//audioRecord.release();
		recordThread = null;
	}
	
	public boolean initRecorder()
	{
		bufferLen = AudioRecord.getMinBufferSize(8000,AudioFormat.CHANNEL_CONFIGURATION_MONO,AudioFormat.ENCODING_PCM_16BIT);
		audioRecord = new AudioRecord(MediaRecorder.AudioSource.MIC, 8000,AudioFormat.CHANNEL_CONFIGURATION_MONO,AudioFormat.ENCODING_PCM_16BIT, bufferLen);
		if (audioRecord == null) {
			return false;
		}
		buffer = new byte[bufferLen];
		return true;
	}
	
	public class RecordThread extends Thread 
	{
		@Override
		public void run() 
		{
			audioRecord.startRecording();
			while (isRecording) 
			{
				int nRet = audioRecord.read(buffer, 0, bufferLen);
				if (nRet > 0) {
					device.sendTalkData(buffer, bufferLen);
				}
			}
		}
	}
	
}

package hsl.p2pipcam.activity;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.app.ProgressDialog;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.TextView;
import android.widget.Toast;

import com.test.R;


public class BaseActivity extends Activity
{
	protected TextView backItem;
	protected TextView titleItem;
	protected TextView functionItem;
	
	protected ProgressDialog progressDialog;
	public static List<Activity> activitys = new ArrayList<Activity>();
	
	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		activitys.add(this);
	}
	
	@Override
	protected void onDestroy() {
		super.onDestroy();
		activitys.remove(this);
	}

	
	/**
     * 返回按钮事件 默认情况下是返回前一个Activity
     */
    protected void back() {
    	finish();
    }
    
    /**
     * 右上角功能按钮事件
     */
    protected void function()
    {}
	
	/**
	 * 设置back文本
	 * @param text
	 */
	protected void setBackText(String text)
	{
		backItem.setText(text);
	}
	
	/**
	 * 设置标题
	 * @param title
	 */
	protected void setTitleText(String text)
	{
		titleItem.setText(text);
	}
	
	/**
	 * 设置功能文本
	 * @param text
	 */
	protected void setfunctionText(String text)
	{
		functionItem.setText(text);
	}
	
	
	protected void hideFunction()
	{
		functionItem.setVisibility(View.GONE);
	}
	
	protected void showProgressDialog(String msg)
	{
		progressDialog = null;
		progressDialog = ProgressDialog.show(this, "", msg, true, true);
	}
	protected void hideProgressDialog()
	{
		if(progressDialog != null && progressDialog.isShowing())
		{
			progressDialog.dismiss();
			progressDialog = null;
		}
	}
	
	protected void showToast(String msg)
	{
		Toast.makeText(this, msg, Toast.LENGTH_SHORT).show();
	}
}

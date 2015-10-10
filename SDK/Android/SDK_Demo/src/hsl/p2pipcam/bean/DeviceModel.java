package hsl.p2pipcam.bean;

import android.text.TextUtils;

public class DeviceModel 
{
	private String devMac="";
	private String devName="";
	private String devID="";
	private String devIP="";
	private int port;
	private int deviceType;
	private String username="";
	private String password="";
	
	public String getDevMac() {
		return devMac;
	}
	public void setDevMac(String devMac) {
		if(TextUtils.isEmpty(devMac))
			this.devMac = "";
		else
			this.devMac = devMac;
	}
	public String getDevName() {
		return devName;
	}
	public void setDevName(String devName) {
		if(TextUtils.isEmpty(devName))
			devName = "";
		this.devName = devName;
	}
	public String getDevID() {
		return devID;
	}
	public void setDevID(String devID) {
		this.devID = devID;
	}
	public String getDevIP() {
		return devIP;
	}
	public void setDevIP(String devIP) {
		if(TextUtils.isEmpty(devIP))
			this.devIP="";
		else
			this.devIP = devIP;
	}
	public int getPort() {
		return port;
	}
	public void setPort(int port) {
		this.port = port;
	}
	
	public int getDeviceType() {
		return deviceType;
	}
	public void setDeviceType(int deviceType) {
		this.deviceType = deviceType;
	}
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		if(TextUtils.isEmpty(username))
			username = "";
		this.username = username;
	}
	public String getPassword() {
		
		return password;
	}
	public void setPassword(String password) {
		if(TextUtils.isEmpty(password))
			password = "";
		this.password = password;
	}
	
}

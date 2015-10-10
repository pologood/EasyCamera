package hsl.p2pipcam.bean;

/**
 * 常量模型
 * @author wang.jingui
 *
 */
public class ContantsModel
{
	
	//public static final String SERVER = "EFGBFFBJKDJIGEJIENGKFIEHHBMAHONDGJFPBACDBKJCLOLFCEAOCFOBHDLPJEKCAKMMLMCHOLMHACDDJJNIIJAD"; 
	public static final String SERVER = "EBGJEBBBKAJIGEJIEPGIFKEFHAMOHANNGHFBBNCEBKJCLKLIDEACCKOOGILNJHLLAMMALEDAODMMAOCCJONDJJ";
	//高清
	public static final int HighResolution =0;
	//标清
	public static final int MidResolution =1;
	//普通
	public static final int LowResolution =2;
	
	public static final int WvrHighResolution = 80;
	public static final int WvrMidResolution = 81;
	public static final int WvrLowResolution = 82;
	
	public final class DeviceType
	{
		//摄像机
		public static final int CAMERA = 0;
		//云盒子
		public static final int CLOUD_BOX = 1;
		//开关
		public static final int SWITCH = 2;
		//智能报警摄像机
		public static final int SMART_CAMERA = 3;
		//可视门铃
		public static final int DOORBELL = 4;
	}
	/**
	 *本地消息类型 
	 */
	public final class MsgType
	{
		public static final int IMAGE = 1;
		public static final int VIDEO = 2;
		public static final int ALARM = 3;
	}
	
	public final class Alarm
	{
		public static final int GPIO_ALARM = 0x21;
		public static final int MOTION_ALARM = 0x20;
		public static final int AUDIO_ALARM = 0x24;
		public static final int IR_ALARM =0x25;
		public static final int DOOR_ALARM =0x26;
		public static final int SMOKE_ALARM =0x27;
		public static final int BELLITF_ALARM =0x28;
		
		//智能报警使用
		//遥控1-4
		public static final int NET_EVENT_ALARM_REMOTE_CONTROL1 = 0x40;
		public static final int NET_EVENT_ALARM_REMOTE_CONTROL2 = 0x41;
		public static final int NET_EVENT_ALARM_REMOTE_CONTROL3 = 0x42;
		public static final int NET_EVENT_ALARM_REMOTE_CONTROL4 = 0x43;
		// 门铃1-4
		public static final int NET_EVENT_ALARM_DOORBELL1 = 0x44;
		public static final int NET_EVENT_ALARM_DOORBELL2 = 0x45;
		public static final int NET_EVENT_ALARM_DOORBELL3 = 0x46;
		public static final int NET_EVENT_ALARM_DOORBELL4 = 0x47;
		
		// 大厅 1-4
		public static final int NET_EVENT_ALARM_HALL1 = 0x48;
		public static final int NET_EVENT_ALARM_HALL2 = 0x49;
		public static final int NET_EVENT_ALARM_HALL3 = 0x4A;
		public static final int NET_EVENT_ALARM_HALL4 = 0x4B;
		
		// 窗户1-4
		public static final int NET_EVENT_ALARM_WINDOW1 = 0x4C;
		public static final int NET_EVENT_ALARM_WINDOW2 = 0x4D;
		public static final int NET_EVENT_ALARM_WINDOW3 = 0x4E;
		public static final int NET_EVENT_ALARM_WINDOW4 = 0x4F;
		
		// 阳台1-4
		public static final int NET_EVENT_ALARM_VERANDA1 = 0x50;
		public static final int NET_EVENT_ALARM_VERANDA2 = 0x51;
		public static final int NET_EVENT_ALARM_VERANDA3 = 0x52;
		public static final int NET_EVENT_ALARM_VERANDA4 = 0x53;
		
		// 卧室1-4
		public static final int NET_EVENT_ALARM_BEDROOM1 = 0x54;
		public static final int NET_EVENT_ALARM_BEDROOM2 = 0x55;
		public static final int NET_EVENT_ALARM_BEDROOM3 = 0x56;
		public static final int NET_EVENT_ALARM_BEDROOM4 = 0x57;
		
		// 庭院1-4
		public static final int NET_EVENT_ALARM_YARD1 = 0x58;
		public static final int NET_EVENT_ALARM_YARD2 = 0x59;
		public static final int NET_EVENT_ALARM_YARD3 = 0x5A;
		public static final int NET_EVENT_ALARM_YARD4 = 0x5B;
		
		// 其他1-4
		public static final int NET_EVENT_ALARM_OTHER1 = 0x5C;
		public static final int NET_EVENT_ALARM_OTHER2 = 0x5D;
		public static final int NET_EVENT_ALARM_OTHER3 = 0x5E;
		public static final int NET_EVENT_ALARM_OTHER4 = 0x5F;
	}
	
	/**
	 * 设备状态
	 */
	public final class DeviceStatus
	{
		public static final int PPPP_STATUS_UNKNOWN = 0xffffffff;
		public static final int PPPP_STATUS_CONNECTING = 0;//连接中
		public static final int PPPP_STATUS_ON_LINE = 100; //在线
		public static final int PPPP_STATUS_CONNECT_ERRER = 101;//连接错误
		public static final int PPPP_STATUS_USER_ERR = 1;//用户名或者密码错误
		public static final int PPPP_STATUS_DISCONNECT = 11;//断开
		public static final int PPPP_STATUS_CHECK_ACCOUNT = 12;//检测账号
		public static final int PPPP_STATUS_CONNECT_TIMEOUT = 10;//连接超时
		public static final int PPPP_STATUS_NOT_ON_LINE = 9;//不在线 
		public static final int PPPP_STATUS_INVALID_ID = 5;//无效ID
	}
	
	public final class Cmd
	{
		//上下循环
		public static final int CMD_PTZ_UP_DOWN = 26;
		public static final int CMD_PTZ_UP_DOWN_STOP = 27;
		//左右循环
		public static final int CMD_PTZ_LEFT_RIGHT = 28;
		public static final int CMD_PTZ_LEFT_RIGHT_STOP = 29;
		// ptz control command ---------------------------------
		public static final int CMD_PTZ_UP = 0;
		public static final int CMD_PTZ_UP_STOP = 1;
		public static final int CMD_PTZ_DOWN = 2;
		public static final int CMD_PTZ_DOWN_STOP = 3;
		public static final int CMD_PTZ_LEFT = 4;
		public static final int CMD_PTZ_LEFT_STOP = 5;
		public static final int CMD_PTZ_RIGHT = 6;
		public static final int CMD_PTZ_RIGHT_STOP = 7;
	}
	
	/**
	 * 参数类型
	 */
	public final class Param
	{
		public static final int SET_PARAM_NETWORK = 0x2000;
		public static final int GET_PARAM_NETWORK = 0x2001;
		
		public static final int SET_PARAM_USERINFO = 0x2002;
		public static final int GET_PARAM_USERINFO = 0x2003;
		//恢复出厂设置
		public static final int SET_PARAM_REBOOT=0x2710;         
		
		public static final int SET_PARAM_DDNS = 0x2004;
		public static final int GET_PARAM_DDNS = 0x2005;
		
		public static final int SET_PARAM_FTP = 0x2006;
		public static final int GET_PARAM_FTP = 0x2007;
		
		public static final int SET_PARAM_MAIL = 0x2008;
		public static final int GET_PARAM_MAIL = 0x2009;
		
		public static final int SET_PARAM_PTZ = 0x2010;
		public static final int GET_PARAM_PTZ = 0x2011;
		
		public static final int SET_PARAM_WIFI = 0x2012;
		public static final int GET_PARAM_WIFI = 0x2013;
		public static final int GET_PARAM_WIFI_LIST = 0x2014;
		
		public static final int SET_PARAM_DATETIME = 0x2015;
		public static final int GET_PARAM_DATETIME = 0x2016;
		
		public static final int SET_PARAM_ALARM = 0x2017;
		public static final int GET_PARAM_ALARM = 0x2018;
		
		public static final int GET_PARAM_RECORDPATH = 0x2019;
		public static final int SET_PARAM_RECORDPATH = 0x2020;
		public static final int GET_PARAM_RECORDSCH = 0x2021;
		public static final int SET_PARAM_RECORDSCH = 0x2022;
		
		public static final int GET_PARAM_SDFORMAT = 0x2023;
		public static final int SET_PARAM_SDFORMAT = 0x2024;

		public static final int GET_CAMERA_PARAMS = 0x2025; // fixfix 2013-05-11
		public static final int SET_CAMERA_PARAMS = 0x2026; // fixfix 2013-05-11

		public static final int REBOOT_EDV = 0x2700;
		public static final int GET_PARAM_STATUS = 0x2701;
		public static final int SET_PARAM_ALIAS = 0x2702;

		public static final int GET_PARAM_APWIFI = 0x2703; // add 2013-11-8
		public static final int SET_PARAM_APWIFI = 0x2704; // add 2013-11-8

		public static final int GET_LOGIN_PARAM = 0x2705; // fix 2013-12-4

		public static final int SEARCH_RECORD_FILE = 0x2706;
		
		public static final int GET_PARAM_ONLINE_USER = 0x270D;//获取在线人数
		//抓拍
		public static final int GET_PARAM_SNAPSHOT = 0x270E;
		
		//门铃开关指令
		public static final int DOOR_BELL_CONTROL = 0x2716;
		
		public static final int GET_PARAM_ALARM_CAM_LIST = 0x2713;//获取报警设备对码列表
		public static final int SET_PARAM_ALARM_CAM_PRESET_CTRL = 0x2714;//设置报警对应的预位置
		public static final int SET_PARAM_ALARM_CAM_CODE = 0x2715;//报警对码
		
	}
	
	public final class WvrParam
	{
		public static final int SET_PARAM_WIFI = 0x2005;
		public static final int SET_SMART_PLUG_RELAY = 0x2011;//设置定时任务
		public static final int SET_SMART_PLUG_TASK = 0x2012;//设置定时任务
		
		public static final int NAS_GET_PARAM_WIFI  = 0x210E; //获取wifi参数
		public static final int GET_PARAM_WIFI_LIST = 0x210F;
		public static final int GET_SMART_PLUG_RELAY = 0x2115;//获取开关状态
		public static final int GET_SMART_PLUG_TASK_SCHUDULE = 0x2116;//获取任务列表
		public static final int NAS_GET_PARAM_PLUG_MODE = 0x2119; // 设备当前模式
		public static final int NAS_GET_PARAM_MOUNT_CAMERA = 0x2102;//获取wvr挂载设备
		public static final int NAS_SET_PARAM_CAMERA_CONTROL = 0x2018;//1/2/8/9 =亮度/对比度/饱和度/色度 （）int channel int param int value
	}
}

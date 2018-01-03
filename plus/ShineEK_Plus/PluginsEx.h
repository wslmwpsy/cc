#pragma once

#include <vector>
//广西视翰结构体定义
typedef struct stToolDataRecord
{
	int DataType;				
	TCHAR FileName[MAX_PATH];
	int DataSize;	
	LPVOID pData;
	LPVOID Result;	
}TOOL_DATA_RECORD, *LPTOOL_DATA_RECORD;

enum TDataType{
	PLUGINS_UPDATE_IMAGE,
	PLUGINS_MEDIA_CONTROL,
	PLUGINS_NEED_NOTIFY
};

enum TPluginsNotifyType
{
	MAIN_SHOW_NOTIFY,
	MAIN_PLAY_NOTIFY,
	PLAYER_NOTIFY,
	DATA_NOTIFY
};

enum TControlMediaType
{
	ControlMedia_OpenFile = 0,
	ControlMedia_Previous,
	ControlMedia_Next,
	ControlMedia_Stop,
	ControlMedia_Pause,
	ControlMedia_Resume,
	ControlMedia_Seek,
	ControlMedia_SetVolume,
	ControlMedia_SetMute
};

//播放状态的变化
enum TPlayState
{
	PlayState_Stopped = 0, 
	PlayState_Paused, 
	PlayState_Running, 
	PlayState_Complete, 
	PlayState_Closed, 
	PlayState_Mute, 
	Playstate_MuteCancel, 
	PlayState_Error, 
	PlayState_OpenFileSuccessed, 
	PlayState_OpeningFileError
};

//PLUGINS_UPDATE_IMAGE - 主程序通知控件
typedef struct stStatusImageRecord
{
	TCHAR Name[MAX_PATH];
	TCHAR ImageFileName[MAX_PATH];
}STATUS_IMAGE_RECORD, *LPSTATUS_IMAGE_RECORD;

//PLUGINS_NEED_NOTIFY - 主程序通知控件
typedef struct stTPlayerNotifyData
{
	bool Add;
	LPVOID ToolHandle;
}TPLAYER_NOTIFY_DATA, *LPTPLAYER_NOTIFY_DATA;

//PLUGINS_MEDIA_CONTROL - 主程序通知控件
typedef struct stTControlMediaData
{
	TControlMediaType ControlMediaType;
	UINT UserID;
	LPVOID pData;
}TCONTROL_MEDIA_DATA, *LPtCONTROL_MEDIA_DATA;

//插件通知主程序
typedef struct stTPluginsNotifyData
{
	TPluginsNotifyType PluginsNotifytype;
	LPVOID pData;
}TPLUGINS_NOTIFY_DATA, *LPTPLUGINS_NOTIFY_DATA;

//控制TopPlayer结构体
typedef struct stTPlayerMessage
{
	int MSG;
	UINT wParam;
	LPVOID lParam;
}TPLAYER_MESSAGE, *LPTPLAYER_MESSAGE;

typedef struct stTDLNAUrlData{
	TCHAR szUrl[2048];					//文件地址
	TCHAR szTitle[1024];				//歌曲名称
	TCHAR szDevfriendlyName[256*4];		//设备名称
	TCHAR szUPnpArtist[256*4];			//艺术家
	TCHAR szUPnpAlbum[256*4];			//唱片集
	TCHAR szUPnpSchool[256*4];			//流派
	TCHAR szUPnpAlbumArtURL[256*4];		//状态图片
}TDLNA_URL_DATA, *LPTDLNA_URL_DATA;

typedef UINT (*Cdecl)(LPTOOL_DATA_RECORD lpTdr);
typedef int (*init)(Cdecl lpTdr);
typedef void (*ShowConfig)();
typedef bool (*OnClick)(bool bflag);

class DllCalling
{
public:
	DllCalling(TCHAR *pPath);
	~DllCalling();
public:
	//释放资源
	void Dispose(bool disposing); 
	//获取Dll的导出函数
	LPVOID Invoke(LPCSTR MethodName); 
	//返回路径
	TCHAR *GetDllPath() {return m_szPath; }
	//接收和设置通知的类型
	TPluginsNotifyType GetTPluginsNotifyType(){ return m_NotifyType; }
	void SetTPluginsNotifyType(TPluginsNotifyType type) { m_NotifyType = type; }
	//接收消息的句柄
	HANDLE GetNotifyHandle() {return m_NotifyHandle; }
	void SetNotifyHandle(HANDLE handle) { m_NotifyHandle = handle; }
	//是否接收通知
	bool GetNeedNotify() {return m_NeedNotify; }
	void SetNeedNotify(bool NeedNotify){ m_NeedNotify = NeedNotify; }
private:
	TCHAR m_szPath[MAX_PATH];
	bool m_bDisposed;					//是否释放资源
	HINSTANCE m_hDll;					//动态库本身模块的句柄
	TPluginsNotifyType m_NotifyType;
	HANDLE m_NotifyHandle;
	bool m_NeedNotify;
};

typedef std::vector<DllCalling*> DLLCALLING_VEC;

class PluginsEx
{
public:
	PluginsEx();
	~PluginsEx();
public:
	//返回初始化
	int inital(TCHAR *FileName);
	//获取配置
	void ShowConfigEx(TCHAR *FileName);
	//点击
	bool OnClickEx(TCHAR *FileName, bool bflag);
	//更新Topplayer控件的通知类型和句柄
	void UpdateToolsNotifyType(TCHAR *FileName, TPluginsNotifyType Notifytype, HANDLE NotifyHandle);
	//控制Topplayer
	void NotifyToolPlugins(TPluginsNotifyType MainNotify, TPLAYER_MESSAGE NotifyMsg);
	//注册Call_Back函数
	void RegisterCdeclCallback(Cdecl callback)
	{
		m_cdecl_callback = callback;
	}
private:
	//返回对象本身
	DllCalling *GetCalling(TCHAR *filename);
private:
	DLLCALLING_VEC m_DllCalling_vec;
	Cdecl m_cdecl_callback;
};
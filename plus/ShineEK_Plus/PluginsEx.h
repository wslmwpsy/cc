#pragma once

#include <vector>
//�����Ӻ��ṹ�嶨��
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

//����״̬�ı仯
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

//PLUGINS_UPDATE_IMAGE - ������֪ͨ�ؼ�
typedef struct stStatusImageRecord
{
	TCHAR Name[MAX_PATH];
	TCHAR ImageFileName[MAX_PATH];
}STATUS_IMAGE_RECORD, *LPSTATUS_IMAGE_RECORD;

//PLUGINS_NEED_NOTIFY - ������֪ͨ�ؼ�
typedef struct stTPlayerNotifyData
{
	bool Add;
	LPVOID ToolHandle;
}TPLAYER_NOTIFY_DATA, *LPTPLAYER_NOTIFY_DATA;

//PLUGINS_MEDIA_CONTROL - ������֪ͨ�ؼ�
typedef struct stTControlMediaData
{
	TControlMediaType ControlMediaType;
	UINT UserID;
	LPVOID pData;
}TCONTROL_MEDIA_DATA, *LPtCONTROL_MEDIA_DATA;

//���֪ͨ������
typedef struct stTPluginsNotifyData
{
	TPluginsNotifyType PluginsNotifytype;
	LPVOID pData;
}TPLUGINS_NOTIFY_DATA, *LPTPLUGINS_NOTIFY_DATA;

//����TopPlayer�ṹ��
typedef struct stTPlayerMessage
{
	int MSG;
	UINT wParam;
	LPVOID lParam;
}TPLAYER_MESSAGE, *LPTPLAYER_MESSAGE;

typedef struct stTDLNAUrlData{
	TCHAR szUrl[2048];					//�ļ���ַ
	TCHAR szTitle[1024];				//��������
	TCHAR szDevfriendlyName[256*4];		//�豸����
	TCHAR szUPnpArtist[256*4];			//������
	TCHAR szUPnpAlbum[256*4];			//��Ƭ��
	TCHAR szUPnpSchool[256*4];			//����
	TCHAR szUPnpAlbumArtURL[256*4];		//״̬ͼƬ
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
	//�ͷ���Դ
	void Dispose(bool disposing); 
	//��ȡDll�ĵ�������
	LPVOID Invoke(LPCSTR MethodName); 
	//����·��
	TCHAR *GetDllPath() {return m_szPath; }
	//���պ�����֪ͨ������
	TPluginsNotifyType GetTPluginsNotifyType(){ return m_NotifyType; }
	void SetTPluginsNotifyType(TPluginsNotifyType type) { m_NotifyType = type; }
	//������Ϣ�ľ��
	HANDLE GetNotifyHandle() {return m_NotifyHandle; }
	void SetNotifyHandle(HANDLE handle) { m_NotifyHandle = handle; }
	//�Ƿ����֪ͨ
	bool GetNeedNotify() {return m_NeedNotify; }
	void SetNeedNotify(bool NeedNotify){ m_NeedNotify = NeedNotify; }
private:
	TCHAR m_szPath[MAX_PATH];
	bool m_bDisposed;					//�Ƿ��ͷ���Դ
	HINSTANCE m_hDll;					//��̬�Ȿ��ģ��ľ��
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
	//���س�ʼ��
	int inital(TCHAR *FileName);
	//��ȡ����
	void ShowConfigEx(TCHAR *FileName);
	//���
	bool OnClickEx(TCHAR *FileName, bool bflag);
	//����Topplayer�ؼ���֪ͨ���ͺ;��
	void UpdateToolsNotifyType(TCHAR *FileName, TPluginsNotifyType Notifytype, HANDLE NotifyHandle);
	//����Topplayer
	void NotifyToolPlugins(TPluginsNotifyType MainNotify, TPLAYER_MESSAGE NotifyMsg);
	//ע��Call_Back����
	void RegisterCdeclCallback(Cdecl callback)
	{
		m_cdecl_callback = callback;
	}
private:
	//���ض�����
	DllCalling *GetCalling(TCHAR *filename);
private:
	DLLCALLING_VEC m_DllCalling_vec;
	Cdecl m_cdecl_callback;
};
#include "stdafx.h"
#include "PluginsEx.h"

PluginsEx::PluginsEx()
{
	m_DllCalling_vec.clear();
}

PluginsEx::~PluginsEx()
{
	if (m_DllCalling_vec.size() > 0)
	{
		DLLCALLING_VEC::iterator it = m_DllCalling_vec.begin();
		while(it != m_DllCalling_vec.end())
		{
			delete *it;
			it++;
		}
	}
}

int PluginsEx::inital(TCHAR *FileName)
{
	if (PathFileExists(FileName))
	{
		DllCalling *dc = GetCalling(FileName);
		if (dc == NULL)
		{
			return 0;
		}
		init i = (init)dc->Invoke("init");
		return i(m_cdecl_callback);
	}else{
		return 0;
	}
}

void PluginsEx::ShowConfigEx(TCHAR *FileName)
{
	if (!PathFileExists(FileName))
	{
		return;
	}
	DllCalling *dc = GetCalling(FileName);
	if (dc != NULL)
	{
		ShowConfig sc = (ShowConfig)dc->Invoke("ShowConfig");
		sc();
	}
}

bool PluginsEx::OnClickEx(TCHAR *FileName, bool bflag)
{
	DllCalling *dc = GetCalling(FileName);
	if (dc != NULL)
	{
		OnClick oc = (OnClick)dc->Invoke("OnClick");
		return oc(bflag);
	}
	return false;
}

DllCalling *PluginsEx::GetCalling(TCHAR *filename)
{
	DllCalling *dc = NULL;
	if (PathFileExists(filename)) //文件存在
	{
		DLLCALLING_VEC::iterator it = m_DllCalling_vec.begin();
		bool bflag = true;
		while(it != m_DllCalling_vec.end())
		{
			dc = *it;
			if (_tcscmp(dc->GetDllPath(), filename) == 0)
			{
				bflag = false;
				break;
			}
			it++;
		}
		if (bflag) //文件不存在
		{
			dc = new DllCalling(filename);
			m_DllCalling_vec.push_back(dc);
		}
		return dc;
	}else{
		return NULL;
	}
}

void PluginsEx::UpdateToolsNotifyType(TCHAR *FileName, TPluginsNotifyType Notifytype, HANDLE NotifyHandle)
{
	DllCalling *calling = GetCalling(FileName);
	if (calling != NULL)
	{
		calling->SetNotifyHandle(NotifyHandle);
		calling->SetTPluginsNotifyType(Notifytype);
	}
}

void PluginsEx::NotifyToolPlugins(TPluginsNotifyType MainNotify, TPLAYER_MESSAGE NotifyMsg)
{
	DLLCALLING_VEC::iterator it = m_DllCalling_vec.begin();
	while(it != m_DllCalling_vec.end())
	{
		if((*it)->GetTPluginsNotifyType() == MainNotify && (*it)->GetNotifyHandle() != NULL)
		{
			PostMessage((HWND)(*it)->GetNotifyHandle(), NotifyMsg.MSG, NotifyMsg.wParam, (int)NotifyMsg.lParam);
		}
		it++;
	}
}
/********************************************************************************/

DllCalling::DllCalling(TCHAR *pPath)
{
	_tcscpy(m_szPath, pPath);
	m_hDll = LoadLibrary(m_szPath);
	m_bDisposed = false;
}

DllCalling::~DllCalling()
{
	if (!m_bDisposed)
	{
		FreeLibrary(m_hDll);
	}
	m_bDisposed = true;
}

void DllCalling::Dispose(bool disposing) //释放资源
{
	if (!m_bDisposed)
	{
		FreeLibrary(m_hDll);
		m_hDll = NULL;
	}

	m_bDisposed = true;
}

LPVOID DllCalling::Invoke(LPCSTR MethodName) //获取Dll的导出函数
{
	LPVOID method = (LPVOID)GetProcAddress(m_hDll, MethodName);
	return method;
}
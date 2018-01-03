// Register.cpp
//

#include "StdAfx.h"
#include "Register.h"

//////////////////////////////////////////////////////////////////////////
//
// 注册OCX控件
int register_ocx(TCHAR* ocx_file_name, bool copy_to_system_directory)
{
	try
	{
		TCHAR szFilename[256];
		const TCHAR *split_symbol=NULL;

		memset(szFilename,0x0,sizeof(szFilename));
		if (copy_to_system_directory)
		{
			TCHAR szDestFilename[256];
			GetSystemDirectory(szDestFilename, sizeof(szDestFilename));
			_tcscat(szDestFilename, L"\\");
			_tcscat(szDestFilename, ocx_file_name);

			GetModuleFileName(NULL, szFilename, sizeof(szFilename));
			_tcscpy(_tcsrchr(szFilename, '\\')+1, ocx_file_name);

			CopyFile(szFilename, szDestFilename, TRUE);
			_tcscpy(szFilename, szDestFilename);
		}
		else
		{
			_tcscpy(szFilename, ocx_file_name);
		}

		// 载入ocx
		HMODULE hLibModule = LoadLibrary(szFilename);
		if (hLibModule == 0)
		{
			//注册控件失败（找不到ocx文件）
			return -1;
		}

		// 获取注册过程入口
		typedef int (WINAPI *LibProc)();

		split_symbol = _tcsrchr(szFilename,'\\');
		if (split_symbol&&(0==_tcscmp(split_symbol+1,L"DSPushSource.ax")))
		{
			return -1;
		}

		LibProc RegisterProc = GetProcAddress(hLibModule, "DllRegisterServer");
		if (RegisterProc == 0)
		{
			//注册控件失败（ocx文件不合法）
			FreeLibrary(hLibModule);
			return -1;
		}

		// 注册控件
		int ret = (*RegisterProc)();
		if (ret < 0)
		{
			//注册控件失败（返回：%d）
			FreeLibrary(hLibModule);
			return ret;
		}
		//注册成功
		// 释放ocx
		FreeLibrary(hLibModule);

		return ret;
	}
	catch (...)
	{
		
	}
	return -1;
}

//////////////////////////////////////////////////////////////////////////
//
// 注销OCX控件
//
int unregister_ocx(TCHAR* ocx_file_name)
{
	// 载入ocx
	HMODULE hLibModule = LoadLibrary(ocx_file_name);
	if (hLibModule == 0)
	{
    	//"注销控件失败（找不到ocx文件）
		return -1;
	}
	
	// 获取注销过程入口
	typedef int (WINAPI *LibProc)();
	LibProc UnregisterProc = GetProcAddress(hLibModule, "DllUnregisterServer");
	if (UnregisterProc == 0)
	{
		//"注销控件失败（ocx文件不合法）
		FreeLibrary(hLibModule);
		return -1;
	}
	
	// 注销控件
	int ret = (*UnregisterProc)();
	if (ret < 0)
	{
		//"注销控件失败（返回：%d）
		FreeLibrary(hLibModule);
		return ret;
	}
	
	// 释放ocx
	FreeLibrary(hLibModule);
	
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// 
// 注册字体（将字体文件拷贝到系统字体目录）

void register_font(TCHAR* dir)
{
	try
	{
		// 将字体文件拷贝到系统字体目录
		CFileFind file_find;
		TCHAR src_dir[256];
		TCHAR dest_dir[256];
		BOOL result=false;
		CString file_name;
		CString src_path;
		TCHAR dest_path[256];

		memset(src_dir,0x0,sizeof(src_dir));
		memset(dest_dir,0x0,sizeof(dest_dir));

		swprintf(src_dir,L"%s\\*.TTF",dir);
		GetSystemDirectory(dest_dir, sizeof(dest_dir));
		_tcscpy(_tcsrchr(dest_dir, '\\')+1, L"Fonts");

		result = file_find.FindFile(src_dir);
		while (result)
		{
			result = file_find.FindNextFile();
			if (file_find.IsDots() || file_find.IsDirectory() || file_find.IsCompressed())
			{
				continue;
			}
			src_path = file_find.GetFilePath();
			file_name = file_find.GetFileName();
			memset(dest_path,0x0,sizeof(dest_path));
			swprintf(dest_path,L"%s\\%s",dest_dir,file_name.GetBuffer(0));
			//拷贝字体到 /windows/fonts 目录下
			CopyFile(src_path, dest_path, TRUE);
		}
		file_find.Close();

		return;
	}
	catch (...)
	{
		
	}
	return;
}

bool register_ax_control(const TCHAR *ax_directory)
{
	try
	{
		CFileFind file_find;
		TCHAR path[256];
		CString ax_path;
		BOOL result=FALSE;


		memset(path,0x0,sizeof(path));

		if (NULL==ax_directory)
		{
			return false;
		}

		swprintf(path,L"%s\\*.ax",ax_directory);

		result = file_find.FindFile(path);
		while (result)
		{
			result = file_find.FindNextFile();
			if (file_find.IsDots() || file_find.IsDirectory() || file_find.IsCompressed())
			{
				continue;
			}
			ax_path = file_find.GetFilePath();
			//注册ax控件
			register_ocx(ax_path.GetBuffer(0),false);
		}
		file_find.Close();

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}
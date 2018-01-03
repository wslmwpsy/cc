// SkinsManager.cpp: implementation of the SkinsManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "file.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


file::file()
{
	file_handle = NULL;
}

file::~file()
{
}

bool file::open_file(const TCHAR* file_path,DWORD dwCreationDisposition)
{
	if (FILE_READ==dwCreationDisposition)
	{
		//¶Á
		file_handle = CreateFile(file_path,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_DELETE,NULL,OPEN_EXISTING,0,NULL);
	}
	else if (FILE_WRITE==dwCreationDisposition)
	{
		//Ð´
		file_handle = CreateFile(file_path,GENERIC_WRITE,FILE_SHARE_DELETE,NULL,CREATE_ALWAYS,0,NULL);
	}
	else if (FILE_APPEND==dwCreationDisposition)
	{
		//ÔÚÄ©Î²×·¼Ó
		file_handle = CreateFile(file_path,GENERIC_WRITE,FILE_SHARE_DELETE,NULL,OPEN_ALWAYS,0,NULL);
		if (INVALID_HANDLE_VALUE!=file_handle)
		{
			DWORD result = seek_file(0,FILE_END);
			if (INVALID_SET_FILE_POINTER==result)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	else
	{
		return false;
	}
	
	return (INVALID_HANDLE_VALUE!=file_handle);
}

bool file::close_file()
{
	return (TRUE==CloseHandle(file_handle));
}

DWORD file::get_file_size()
{
	return GetFileSize(file_handle,NULL);
}

DWORD file::get_file_size(const TCHAR* file_path)
{
	bool result = open_file(file_path,FILE_READ);
	if(!result) return 0;
	DWORD fs = get_file_size();
	close_file();
	return fs;
}

DWORD file::seek_file(DWORD offset,DWORD method)
{
	return SetFilePointer(file_handle,offset,NULL,method);
}

DWORD file::get_file_pointer()
{
	return SetFilePointer(file_handle,0,NULL,FILE_CURRENT);
}

bool file::read_file(LPVOID buffer,DWORD buf_size,DWORD* read_bytes)
{
	DWORD rd;
	BOOL ret = ReadFile(file_handle,buffer,buf_size,&rd,NULL);
	if(read_bytes) *read_bytes = rd;
	return (TRUE==ret);
}
bool file::write_file(LPVOID buffer,DWORD buf_size,DWORD* write_bytes)
{
	DWORD wd;
	BOOL ret = WriteFile(file_handle,buffer,buf_size,&wd,NULL);
	if(write_bytes) *write_bytes = wd;
	return (TRUE==ret);
}

bool file::file_exist(const TCHAR *file_path)
{
	bool result=false;

	result = open_file(file_path,FILE_READ);
	if (!result)
	{
		return false;
	}
	result = close_file();

	return true;
}
// SkinsManager.h: interface for the SkinsManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKREADER_H__D6DDA561_7CE2_49DF_A2E7_74606EE0ED44__INCLUDED_)
#define AFX_PACKREADER_H__D6DDA561_7CE2_49DF_A2E7_74606EE0ED44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//�ļ�����
enum FILE_ATTRIBUTE
{
	FILE_ATTRIBUTE_NVALID,     //δ֪����Ч
	FILE_ATTRIBUTE_DIR,        //Ŀ¼
	FILE_ATTRIBUTE_FILE,       //��ͨ�ļ�
};

enum FILE_OPEN_FLAG
{
	FILE_READ,   //�ļ���
	FILE_WRITE,  //�ļ�д
	FILE_APPEND, //�ļ�ĩβ׷��
};


class file
{
public:
	file();
	~file();
	bool	open_file(const TCHAR* file_path,DWORD dwCreationDisposition);
	bool	close_file();
	DWORD	get_file_size();
	DWORD	get_file_size(const TCHAR* file_path);
	DWORD	seek_file(DWORD offset,DWORD method);
	DWORD	get_file_pointer();
	bool	read_file(LPVOID buffer,DWORD buf_size,DWORD* read_bytes = NULL);
	bool    write_file(LPVOID buffer,DWORD buf_size,DWORD* write_bytes);
	bool    file_exist(const TCHAR *file_path);
	
private:
	HANDLE file_handle;
};

#endif // !defined(AFX_PACKREADER_H__D6DDA561_7CE2_49DF_A2E7_74606EE0ED44__INCLUDED_)

#include "StdAfx.h"
#include ".\decrypt_singer_picture.h"
#include "picture_key.h"
#include "..\common\StringCodeConversion.h"
#include "../message.h"

#include <shlwapi.h>

#pragma warning(disable: 4267)

decrypt_picture::decrypt_picture(void)
{
}

decrypt_picture::~decrypt_picture(void)
{
}

bool decrypt_picture::decrypt_singer_picture(TCHAR *singer_name,TCHAR *singer_sex,int file_number,TCHAR *src_picture_path,TCHAR *out_file_path)
{
	try
	{
		TCHAR one_singer_name[256];
		TCHAR *split_symbol=NULL;
		TCHAR src_path[256];
		TCHAR decrypt_path[256];
		bool result=false;

		memset(one_singer_name,0x0,sizeof(one_singer_name));
		memset(src_path,0x0,sizeof(src_path));
		memset(decrypt_path,0x0,sizeof(decrypt_path));

		if ((NULL==singer_name)||(NULL==singer_sex)||(src_picture_path==NULL)||(NULL==out_file_path))
		{
			return false;
		}

		//只取第一个歌星名字
		split_symbol = _tcschr(singer_name,'/');
		if (split_symbol)
		{
			//取第一个歌星的姓名
			_tcsncpy(one_singer_name,singer_name,split_symbol-singer_name);
		}
		else
		{
			_tcscpy(one_singer_name,singer_name);
		}
		//得到歌星图片路径
		swprintf(src_path,L"%s\\%s.jpg",src_picture_path,one_singer_name);
		if (PathFileExists(src_path))
		{
			//解密歌星图片
			result = decrypt_picture_file(src_path,decrypt_path,file_number);
			if (!result)
			{
				return false;
			}
		}
		else if (0==_tcscmp(singer_sex,L"2"))
		{
			//默认女图片
			swprintf(decrypt_path,L"%s\\woman.jpg",src_picture_path);
		}
		else if (0==_tcscmp(singer_sex,L"1"))
		{
			//默认男图片
			swprintf(decrypt_path,L"%s\\man.jpg",src_picture_path);
		}
		else if (0==_tcscmp(singer_sex,L"3"))
		{
			//默认对唱图片
			swprintf(decrypt_path,L"%s\\pair.jpg",src_picture_path);
		}
		//返回解密的图片路径
		_tcscpy(out_file_path,decrypt_path);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool decrypt_picture::decrypt_song_picture(TCHAR *song_id,int file_number,TCHAR *src_picture_path,TCHAR *out_file_path)
{
	try
	{
		if ((NULL==song_id)||(NULL==src_picture_path)||(NULL==out_file_path))
		{
			return false;
		}

		TCHAR image_path[256];
		TCHAR decrypt_path[256];
		bool result=false;

		memset(decrypt_path,0x0,sizeof(decrypt_path));

		for (int i=1;i<=6;i++)
		{
            memset(image_path,0x0,sizeof(image_path));

			//得到歌曲图片路径
			swprintf(image_path,L"%s\\JDJPKC%d\\%s.jpg",src_picture_path,i,song_id);
			if (PathFileExists(image_path))
			{
				//解密歌星图片
				result = decrypt_picture_file(image_path,decrypt_path,file_number);
				if (result)
				{
					_tcscpy(out_file_path,decrypt_path);
					return true;
				}
				return false;
			}
		}
		
		return false;
	}
	catch (...)
	{
		
	}
	return false;
}

bool decrypt_picture::decrypt_picture_file(TCHAR *in_file_path,TCHAR *out_file_path,int file_number)
{
	try
	{
		TCHAR temp_path[256];
		string_conversion string_conv;
		TCHAR out_path[256];
		int result=0;

        memset(temp_path,0x0,sizeof(temp_path));
		memset(out_path,0x0,sizeof(out_path));

		::GetTempPath(sizeof(temp_path)/sizeof(TCHAR),temp_path);
		swprintf(out_path,L"%s0011E51%03d",temp_path,file_number);

		//解密
		result = decrypt_file(in_file_path,out_path);
		switch(result)
		{
		case 0: //没有加密
			{
				memset(out_file_path,0x0,sizeof(out_file_path));
				_tcscpy(out_file_path,in_file_path);
			}
			break;
		case 1: //加密成功
			{
				memset(out_file_path,0x0,sizeof(out_file_path));
				_tcscpy(out_file_path,out_path);
			}
			break;
		default:
			return false;
		}
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

int decrypt_picture::decrypt_file(TCHAR *in_file_path,TCHAR *out_file_path)
{
	try
	{
		FILE *fp=NULL;
		size_t nFileSize=0;
		unsigned char *pDataBuffer=NULL;
		const TCHAR *in_file_name=NULL;
		int nFileNameSize=0;
		unsigned char szFileHead[FILE_HEAD_LENGTH] = {0x14,0x18,0x53,0x98,0x7f,0x6e,0x8c,0x9c,0x69,0x02,0x0f,0x5d,0xb0,0xcb,0x17,0x4b};
		unsigned char szReadFileHead[FILE_HEAD_LENGTH];
		int file_size=0;

		memset(szReadFileHead,0x0,sizeof(szReadFileHead));

		if ((NULL==in_file_path)||(NULL==out_file_path))
		{
			return -1;
		}

		in_file_name = _tcsrchr(in_file_path,'\\')+1;
		//修改密钥
		nFileNameSize = _tcslen(in_file_name);
		szFileHead[14] = nFileNameSize;

		//open src file
		fp = _wfopen(in_file_path,L"rb");
		if (NULL==fp)
		{
			return -1;
		}
		fseek(fp,0,SEEK_END);
		file_size = ftell(fp);
		if (file_size<1024)
		{
			return -1;
		}
		fseek(fp,0,SEEK_SET);
		//read head
		fread(szReadFileHead,0x1,sizeof(szReadFileHead),fp);
		if ((szReadFileHead[3]!=szFileHead[3])||(szReadFileHead[6]!=szFileHead[6])||(szReadFileHead[10]!=szFileHead[10])||(szReadFileHead[14]!=szFileHead[14]))
		{
			if (fp)
			{
				fclose(fp);
				fp=NULL;
			}
			return 0;
		}

		fseek(fp,0,SEEK_END);
		nFileSize = ftell(fp)-sizeof(szReadFileHead);
		pDataBuffer = new unsigned char[nFileSize+1];
		if (NULL==pDataBuffer)
		{
			fclose(fp);
			fp=NULL;
			return -1;
		}
		memset(pDataBuffer,0x0,nFileSize+1);
		fseek(fp,sizeof(szReadFileHead),SEEK_SET);
		fread(pDataBuffer,0x1,nFileSize,fp);
		if (fp)
		{
			fclose(fp);
			fp=NULL;
		}
		//decrypt data
		decrypt(pDataBuffer,nFileSize,szReadFileHead,DECRYPT);
		//save encrypt data
		fp = _wfopen(out_file_path,L"wb");
		if (NULL==fp)
		{
			if (pDataBuffer)
			{
				delete []pDataBuffer;
				pDataBuffer = NULL;
			}

			return -1;
		}
		fwrite(pDataBuffer,0x1,nFileSize,fp);
		if (fp)
		{
			fclose(fp);
			fp=NULL;
		}
		if (pDataBuffer)
		{
			delete []pDataBuffer;
			pDataBuffer = NULL;
		}

		return 1;
	}
	catch (...)
	{
		
	}
	return -1;
}

bool decrypt_picture::decrypt(unsigned char *data,long data_len,unsigned char *file_head,enum  OPERATE Type)
{
	try
	{
		unsigned char head[FILE_HEAD_LENGTH];
		int key_index=0;
		unsigned char key[KEY_LENGHT];
		int switch_suffix1=0;
		int switch_suffix2=0;
		unsigned char switch_key=0;

		memset(head,0x0,sizeof(head));
		memset(key,0x0,sizeof(key));

		memcpy(head,file_head,FILE_HEAD_LENGTH);


		//密钥索引
		key_index = (head[5]+head[12])%16;
		//得到使用的密钥
		memcpy(key,shine_key+key_index*KEY_LENGHT,KEY_LENGHT);

		//交换密钥位
		switch_suffix1 = head[1];
		switch_suffix2 = head[7];
		switch_key = key[switch_suffix1];
		key[switch_suffix1] = key[switch_suffix2];
		key[switch_suffix2] = switch_key;

		switch_suffix1 = head[2];
		switch_suffix2 = head[13];
		switch_key = key[switch_suffix1];
		key[switch_suffix1] = key[switch_suffix2];
		key[switch_suffix2] = switch_key;

		switch_suffix1 = head[4];
		switch_suffix2 = head[8];
		switch_key = key[switch_suffix1];
		key[switch_suffix1] = key[switch_suffix2];
		key[switch_suffix2] = switch_key;

		if (ENCRYPT==Type)
		{
			//加密
			for (int i=0;i<data_len;i++)
			{
				for (int j=0;j<KEY_LENGHT;j++)
				{
					if (data[i]==key[j])
					{
						data[i] = j;
						break;
					}
				}
			}
		}
		else if (DECRYPT==Type)
		{
			int suffix=0;
			//解密
			for (int i=0;i<data_len;i++)
			{
				suffix = data[i];
				data[i] = key[suffix];
			}
		}
		return true;
	}
	catch (...)
	{

	}
	return false;
}
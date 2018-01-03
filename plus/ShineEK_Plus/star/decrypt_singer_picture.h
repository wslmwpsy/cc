#pragma once

//文件头
#define FILE_HEAD_LENGTH   16
//密钥长度
#define KEY_LENGHT         256

class decrypt_picture
{
public:
	decrypt_picture(void);
	~decrypt_picture(void);


	/*
	功能：解密歌星图片
	参数：
	    singer_name：歌星名字
		singer_sex：歌星性别
		file_number：文件编号
		src_picture_path：歌星图片存放路径
		out_file_path：解密的文件路径
	返回值：
	    true：成功
		false：失败
	*/
	bool decrypt_singer_picture(TCHAR *singer_name,TCHAR *singer_sex,int file_number,TCHAR *src_picture_path,TCHAR *out_file_path);

	/*
	功能：解密歌曲图片路径
	参数：
	   song_id：歌曲编号
	   file_number：文件编号
	   src_picture_path：歌曲图片存放路径
	   out_file_path：解密的文件路径
   返回值：
       true：成功
	   false：失败
	*/
	bool decrypt_song_picture(TCHAR *song_id,int file_number,TCHAR *src_picture_path,TCHAR *out_file_path);
	
	/*
	功能：解密图片和文件
	参数：
		in_file_path：原文件路径
		out_file_path：解密的文件路径
		file_number：文件编号
	返回值：
		0：源文件没有加密 -1：解密出错 1：解密成功
	*/
	bool decrypt_picture_file(TCHAR *in_file_path,TCHAR *out_file_path,int file_number);

	/*
	功能：解密图片和文件
	参数：
	     in_file_path：原文件路径
		 out_file_path：解密的文件路径
	返回值：
	    0：源文件没有加密 -1：解密出错 1：解密成功
	*/
	int decrypt_file(TCHAR *in_file_path,TCHAR *out_file_path);
	//解密数据
	bool decrypt(unsigned char *data,long data_len,unsigned char *file_head,enum  OPERATE Type);
};

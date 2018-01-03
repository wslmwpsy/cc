#include "stdafx.h"
#include "http.h"
#include "..\common\StringCodeConversion.h"
#include "../common/init_socket.h"
#include "../file/config_file.h"
#include "lame.h"
#include "../file/log.h"

/*结尾边界符号*/
#define POST_FILE_END	"\r\n--AaB03x--\r\n\r\n"

CHttp_old::CHttp_old(void)
{
	initialize();
}

void CHttp_old::initialize(void)
{
	config_file_manager config_file;
	std::wstring server_ip;
	string_conversion string_conv;

	m_login_type = 0;
	memset(m_pc_share_user_info,0x0,sizeof(m_pc_share_user_info));

	for (int i=0;i<TAPE_SONG_MAX_COUNT;i++)
	{
		memset(&m_share_url[i],0x0,sizeof(m_share_url[i]));
	}
	memset(m_server_ip,0x0,sizeof(m_server_ip));
	server_ip = config_file.read_string(L"recorder",L"outlets_server",L"");
	if (!server_ip.empty())
	{
		string_conv.widechar_to_utf8(server_ip.c_str(),m_server_ip,sizeof(m_server_ip));
	}
	m_server_port = 14777;  //默认端口
}

bool CHttp_old::get_url_from_server(TCHAR *song_number,TCHAR *web_url)
{
	try
	{
		SOCKET send_socket;
		char buff[1024];
		TCHAR Url[256];
		string_conversion string_conv;

		if (0==strcmp(m_server_ip,"")||(NULL==song_number)||(NULL==web_url))
		{
			return false;
		}
		// 创建套节字
		send_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(send_socket == INVALID_SOCKET)
		{
			return false;
		}
		//off TIME_WAIT
		struct linger zeroLinger;	
		zeroLinger.l_onoff = 1;	
		zeroLinger.l_linger = 5;

		setsockopt(send_socket,SOL_SOCKET,SO_LINGER,(const char *)&zeroLinger	,sizeof(zeroLinger));

		int m_nSendTimeout = 2000;
		//set send timeout
		setsockopt(send_socket,SOL_SOCKET,SO_SNDTIMEO,(const char *)&m_nSendTimeout,sizeof(m_nSendTimeout));
		setsockopt(send_socket,SOL_SOCKET,SO_RCVTIMEO,(const char *)&m_nSendTimeout,sizeof(m_nSendTimeout));

		// 也可以在这里调用bind函数绑定一个本地地址
		// 否则系统将会自动安排

		// 填写远程地址信息
		sockaddr_in servAddr; 
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = htons(m_server_port);
		// 注意，这里要填写服务器程序（TCPServer程序）所在机器的IP地址
		// 如果你的计算机没有联网，直接使用127.0.0.1即可
		servAddr.sin_addr.S_un.S_addr = inet_addr(m_server_ip);

		if(::connect(send_socket, (sockaddr*)&servAddr, sizeof(servAddr)) == -1)
		{
			closesocket(send_socket);
			return false;
		}
		memset(buff,0x0,sizeof(buff));
		//组织文件头
		set_get_head(buff);
		int len= strlen(buff);
		len = ::send(send_socket,buff,len,0);
		//接收
		memset(buff,0x0,sizeof(buff));
		recv(send_socket,buff,1024,0);

		//关闭socket
		closesocket(send_socket);
		//解析出url
		char *split_symbol = strstr(buff,"\r\n\r\n");
		if (split_symbol)
		{
			split_symbol += 4;
			char *end_symbol = strstr(split_symbol,"\r\n");
			if (end_symbol)
			{
				end_symbol[0]='\0';
			}
			string_conv.utf8_to_widechar(split_symbol,Url,sizeof(Url));
			_tcscpy(web_url,Url);
			//保存URL
			set_web_url(song_number,Url);
		}

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool CHttp_old::upload_file_to_server(song_info video_info)
{
	try
	{
		FILE *fp=NULL;
		int len = 0;
		int len_head = 0;
		int len_end=0;
		char buff[8*1024];
		TCHAR song_number_wide[256];
		TCHAR Url_wide[256];
		TCHAR file_name_wide[256];
		TCHAR song_name_wide[256];
		TCHAR singer_name_wide[256];
		TCHAR tape_time_wide[256];
		TCHAR wave_path_wide[256];
		TCHAR mp3_path_wide[256];
		TCHAR src_song_id_wide[256];
		char url[256];
		char file_name[256];
		bool result=false;
		string_conversion string_conv;
		DWORD file_size=0;
		char song_name[256];
		char singer_name[256];
		char tape_time[256];
		SOCKET send_socket;
		char content_head[256];
		char src_song_id[256];
		

		if (0==strcmp(m_server_ip,""))
		{
			return false;
		}

		memset(buff,0,sizeof(buff));
		memset(song_number_wide,0x0,sizeof(song_number_wide));
		memset(Url_wide,0x0,sizeof(Url_wide));
		memset(file_name_wide,0x0,sizeof(file_name_wide));
		memset(url,0x0,sizeof(url));
		memset(file_name,0x0,sizeof(url));
		memset(song_name_wide,0x0,sizeof(song_name_wide));
		memset(singer_name_wide,0x0,sizeof(singer_name_wide));
		memset(tape_time_wide,0x0,sizeof(tape_time_wide));
		memset(wave_path_wide,0x0,sizeof(wave_path_wide));
		memset(mp3_path_wide,0x0,sizeof(mp3_path_wide));
		memset(song_name,0x0,sizeof(song_name));
		memset(singer_name,0x0,sizeof(singer_name));
		memset(tape_time,0x0,sizeof(tape_time));
		memset(content_head,0x0,sizeof(content_head));
		memset(src_song_id_wide,0x0,sizeof(src_song_id_wide));
		memset(src_song_id,0x0,sizeof(src_song_id));
		

		result = video_info.get_song_id(song_number_wide);
		if (!result)
		{
			return false;
		}

		result = get_web_url(song_number_wide,Url_wide,file_name_wide);
		if (!result)
		{
			return false;
		}
		result = video_info.get_song_name(song_name_wide);
		if (!result)
		{
			return false;
		}
		result = video_info.get_singer_name(singer_name_wide);
		if (!result)
		{
			return false;
		}
		result = video_info.get_recorder_datetime(tape_time_wide);
		if (!result)
		{
			return false;
		}
		result = video_info.get_wave_path(wave_path_wide);
		if (!result)
		{
			return false;
		}
		result = video_info.get_culture_code(src_song_id_wide);
		if (!result)
		{
			return false;
		}
		//转换成utf-8
		string_conv.widechar_to_utf8(src_song_id_wide,src_song_id,sizeof(src_song_id));
		string_conv.widechar_to_utf8(file_name_wide,file_name,sizeof(file_name));
		string_conv.widechar_to_utf8(Url_wide,url,sizeof(url));
		string_conv.widechar_to_utf8(song_name_wide,song_name,sizeof(song_name));
		string_conv.widechar_to_utf8(singer_name_wide,singer_name,sizeof(singer_name));
		string_conv.widechar_to_utf8(tape_time_wide,tape_time,sizeof(tape_time));
		//wave to mp3
		if (_tcsstr(wave_path_wide,L".mp3"))
		{
			//不用转换，本身就是mp3
			_tcscpy(mp3_path_wide,wave_path_wide);
		}
		else //转成mp3
		{
			swprintf(mp3_path_wide,L"%s.mp3",wave_path_wide);
			if (!PathFileExists(mp3_path_wide))
			{
				result = PCM_to_mp3(wave_path_wide,mp3_path_wide);
				if (!result)
				{
					return false;
				}
			}
		}
		// 创建套节字
		send_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(send_socket == INVALID_SOCKET)
		{
			return false;
		}
		//off TIME_WAIT
		struct linger zeroLinger;	
		zeroLinger.l_onoff = 1;	
		zeroLinger.l_linger = 5;

		setsockopt(send_socket,SOL_SOCKET,SO_LINGER,(const char *)&zeroLinger	,sizeof(zeroLinger));

		int m_nSendTimeout = 2000;
		//set send timeout
		setsockopt(send_socket,SOL_SOCKET,SO_SNDTIMEO,(const char *)&m_nSendTimeout,sizeof(m_nSendTimeout));
		setsockopt(send_socket,SOL_SOCKET,SO_RCVTIMEO,(const char *)&m_nSendTimeout,sizeof(m_nSendTimeout));

		// 也可以在这里调用bind函数绑定一个本地地址
		// 否则系统将会自动安排

		// 填写远程地址信息
		sockaddr_in servAddr; 
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = htons(m_server_port);
		// 注意，这里要填写服务器程序（TCPServer程序）所在机器的IP地址
		// 如果你的计算机没有联网，直接使用127.0.0.1即可
		servAddr.sin_addr.S_un.S_addr = inet_addr(m_server_ip);

		if(::connect(send_socket, (sockaddr*)&servAddr, sizeof(servAddr)) == -1)
		{
			closesocket(send_socket);
			return false;
		}
		//upload mp3
		fp=_wfopen(mp3_path_wide,L"rb");
		if(fp==NULL)
		{
			closesocket(send_socket);
			return false;
		}
		//得到文件大小
		fseek(fp,0,SEEK_END);
		file_size = ftell(fp);
		fseek(fp,0,SEEK_SET);

		sprintf(content_head,"--AaB03x\r\nContent-Disposition: attachment; name=\"FileData\"; filename=\"%s\"\r\nContent-Type: application/octet-stream\r\n\r\n",file_name);
		len_head = strlen(content_head);
		len_end = strlen(POST_FILE_END);
		set_post_head(buff,len_head+len_end+file_size,song_name,singer_name,tape_time,url,src_song_id);
		/*发送头指令*/
		::send(send_socket,buff,strlen(buff),0);
		//发送内容头
		memset(buff,0x0,sizeof(buff));
		strcpy(buff,content_head);
		::send(send_socket,buff,strlen(buff),0);
		//发送文件
		while((len=fread(buff,1,sizeof(buff),fp)) > 0){
			::send(send_socket,buff,len,0);
		}
		//发送结束符
		::send(send_socket,POST_FILE_END,len_head,0);
		//接受结果
		recv(send_socket,buff,sizeof(buff),0);

		//关闭
		fclose(fp);
		closesocket(send_socket);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool CHttp_old::set_post_head(char *order,int len,char *song_name,char *singer_name,char *tape_time,char *url,char *song_id)
{
	try
	{
		char buff[2048];
		char no_space_time[256];
		char no_space_song[256];
		char no_space_singer[256];
		char user_info[2048];

		if ((NULL==order)||(NULL==song_name)||(NULL==singer_name)||(NULL==tape_time)||(NULL==url)||(NULL==song_id))
		{
			return false;
		}
		memset(user_info,0x0,sizeof(user_info));
		memset(no_space_time, 0x0, sizeof(no_space_time));
		memset(no_space_song, 0x0, sizeof(no_space_song));
		memset(no_space_singer, 0x0, sizeof(no_space_singer));

		//过滤空格
		convert_blank_space(tape_time, no_space_time);
		convert_blank_space(song_name, no_space_song);
		convert_blank_space(singer_name, no_space_singer);

		//得到用户信息
		if (0 == m_login_type)
		{
			strcpy(user_info,m_pc_share_user_info);
		}
		else
		{
			get_user_info(user_info);
		}

		/*获取歌曲信息*/
		memset(buff,0x0,sizeof(buff));
		sprintf(buff,"POST /outletshandler.ashx/?is_load=1&songname=%s&singername=%s&recordtime=%s&songid=%s&users=%s HTTP/1.1\r\n",no_space_song,no_space_singer,no_space_time,song_id,user_info);
		strcat(order,buff);
		sprintf(buff,"Host: %s:%d\r\n",m_server_ip,m_server_port);/*host*/
		strcat(order,buff);
		memset(buff,0x0,sizeof(buff));
		sprintf(buff,"Content-Length: %d\r\n",len);/*Content-Length*/
		strcat(order,buff);
		strcat(order,"Content-Type: multipart/form-data; boundary=AaB03x\r\n");/*Content-Type*/
		strcat(order,"User-Agent: Mozilla/5.0 (Windows NT 6.1)\r\n");/*User-Agent*/
		memset(buff,0x0,sizeof(buff));
		sprintf(buff,"Referer: %s\r\n",url);/*获取url连接*/
		strcat(order,buff);
		//strcat(order,"Accept-Encoding: gzip,deflate,sdch\r\n");/*Accept-Encoding*/
		strcat(order,"Accept-Language: zh-CN,zh;q=0.8\r\n");/*Accept-Language*/
		strcat(order,"Cache-Control: no-cache\r\n");/*Cache-Control*/
		strcat(order,"Connection: close\r\n\r\n");/*Connection*/

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool CHttp_old::set_get_head(char *order)
{
	try
	{
		char buff[255];

		if (NULL==order)
		{
			return false;
		}

		/*获取歌曲信息*/
		memset(buff,0x0,sizeof(buff));
		strcpy(order,"GET /get_url HTTP/1.1\r\n");
		sprintf(buff,"Host: %s:%d\r\n",m_server_ip,m_server_port);/*host*/
		strcat(order,buff);
		strcat(order,"Cache-Control: no-cache\r\n");/*Cache-Control*/		
		strcat(order,"User-Agent: Mozilla/5.0 (Windows NT 6.1)\r\n");/*User-Agent*/
		strcat(order,"Accept-Language: zh-CN,zh;q=0.8\r\n");/*Accept-Language*/
		strcat(order,"Connection: close\r\n\r\n");/*Connection*/

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool CHttp_old::get_web_url(const TCHAR *song_number,TCHAR *URL,TCHAR *file_name)
{
	try
	{
		if ((NULL==song_number)||(NULL==URL))
		{
			return false;
		}

		for (int i=0;i<TAPE_SONG_MAX_COUNT;i++)
		{
			if (0==_tcscmp(song_number,m_share_url[i].song_number))
			{
				_tcscpy(URL,m_share_url[i].URL);
				if (file_name)
				{
					TCHAR *split_symbol = _tcsrchr(URL,'=');
					if (split_symbol)
					{
						swprintf(file_name,L"%s.mp3",split_symbol+1);
					}
				}

				return true;
			}
		}

		return false;
	}
	catch (...)
	{
		
	}

	return false;
}

bool CHttp_old::set_web_url(TCHAR *song_number,TCHAR *URL)
{
	try
	{
		for (int i=0;i<TAPE_SONG_MAX_COUNT;i++)
		{
			if (0==_tcscmp(m_share_url[i].song_number,song_number))
			{
				_tcscpy(m_share_url[i].song_number,song_number);
				_tcscpy(m_share_url[i].URL,URL);

				return true;
			}
		}
		for (int i=0;i<TAPE_SONG_MAX_COUNT;i++)
		{
			if (0==_tcscmp(m_share_url[i].song_number,L""))
			{
				_tcscpy(m_share_url[i].song_number,song_number);
				_tcscpy(m_share_url[i].URL,URL);

				return true;
			}
		}
		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool CHttp_old::PCM_to_mp3(TCHAR *wave_path,TCHAR *mp3_handle_path)
{
	try
	{
		FILE *pcm_handle = NULL;
		FILE *mp3_handle = NULL;
		size_t nread;
		int ret, nwrite;
		const int pcm_SIZE = 8192;
		const int mp3_SIZE = 8192;
		short pcm_handle_buffer[pcm_SIZE*2];       //双通道双字节
		unsigned char mp3_handle_buffer[mp3_SIZE];

		//open file
		pcm_handle = _wfopen(wave_path, L"rb");
		if (NULL==pcm_handle)
		{
			return false;
		}
		mp3_handle = _wfopen(mp3_handle_path, L"wb");
		if (NULL==mp3_handle)
		{
			fclose(pcm_handle);
			return false;
		}

		// 1. Get lame version (OPTIONAL)
		const char *version = get_lame_version();		

		// 2. Initializing
		lame_t lame = lame_init();
		if (NULL==lame)
		{
			fclose(pcm_handle);
			fclose(mp3_handle);
			return false;
		}

		//set para
		lame_set_in_samplerate(lame,44100);
		lame_set_brate(lame,64);
		lame_set_mode(lame,STEREO); 
		//lame_set_VBR(lame, vbr_default);  //可变码率
		lame_set_VBR_quality(lame, 5);

		// 4. Initialize parameters
		ret = lame_init_params(lame);
		if (ret < 0) {
			lame_close(lame);
			fclose(pcm_handle);
			fclose(mp3_handle);
			return false;
		}

		do {
			// Read pcm_SIZE of array
			nread = fread(pcm_handle_buffer, 2 * sizeof(short), pcm_SIZE, pcm_handle);
			if (nread != 0) {
				// 5. Encode
				int nsamples = nread;
				short buffer_l[pcm_SIZE];
				short buffer_r[pcm_SIZE];

				int j = 0;
				for (int i = 0; i < nsamples; i++) {
					buffer_l[i] = pcm_handle_buffer[j++];
					buffer_r[i] = pcm_handle_buffer[j++];
				}

				nwrite = lame_encode_buffer(lame, buffer_l, buffer_r, nread,mp3_handle_buffer, mp3_SIZE);
			} else {
				// 6. Flush and give some final frames
				nwrite = lame_encode_flush(lame, mp3_handle_buffer, mp3_SIZE);
			}

			if (nwrite < 0) {
				lame_close(lame);
				fclose(pcm_handle);
				fclose(mp3_handle);
				return false;
			}
			fwrite(mp3_handle_buffer, nwrite, 1, mp3_handle);
		} while (nread != 0);

		// 7. Write INFO tag (OPTIONAL)
		// lame_mp3_handle_tags_fid(lame, mp3_handle);

		// 8. Free internal data structures
		lame_close(lame);
		fclose(mp3_handle);
		fclose(pcm_handle); 

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool CHttp_old::save_user_info(char *user_info)
{
	try
	{
		char user_name[256];
		char psw[256];
		char type[256];
		char *split_symbol=NULL;

		if (NULL==user_info)
		{
			return false;
		}

		m_login_type = 1;
		memset(user_name,0x0,sizeof(user_name));
		memset(psw,0x0,sizeof(psw));
		memset(type,0x0,sizeof(type));

		//解析
		split_symbol = strchr(user_info,':');
		if (NULL==split_symbol)
		{
			return false;
		}
		//用户名
		memcpy(user_name,user_info,split_symbol-user_info);
		split_symbol++;
		//密码和类型
		strcpy(psw,split_symbol);
		split_symbol = strchr(psw,':');
		if (NULL==split_symbol)
		{
			return false;
		}
		strcpy(type,split_symbol+1);
		split_symbol[0]='\0';
		//保存
		for(int i=0;i<USER_MAX_COUNT;i++)
		{
			if (0==strcmp(m_user_info[i].user_name,user_name))
			{
				break;
			}
			if (0==strcmp(m_user_info[i].user_name,""))
			{
				strcpy(m_user_info[i].user_name,user_name);
				strcpy(m_user_info[i].passowrd,psw);
				strcpy(m_user_info[i].type,type);

				break;
			}
		}

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool CHttp_old::delete_user_info(char *user_info)
{
	try
	{
		char user_name[256];
		char psw[256];
		char type[256];
		char *split_symbol=NULL;

		if (NULL==user_info)
		{
			return false;
		}

		memset(user_name,0x0,sizeof(user_name));
		memset(psw,0x0,sizeof(psw));
		memset(type,0x0,sizeof(type));

		//解析
		split_symbol = strchr(user_info,':');
		if (NULL==split_symbol)
		{
			return false;
		}
		//用户名
		memcpy(user_name,user_info,split_symbol-user_info);
		split_symbol++;
		//密码和类型
		strcpy(psw,split_symbol);
		split_symbol = strchr(psw,':');
		if (NULL==split_symbol)
		{
			return false;
		}
		strcpy(type,split_symbol+1);
		split_symbol[0]='\0';
		//删除
		for(int i=0;i<USER_MAX_COUNT;i++)
		{
			if ((0==strcmp(m_user_info[i].user_name,user_name))&&(0==strcmp(m_user_info[i].passowrd,psw)))
			{
				memset(&m_user_info[i],0x0,sizeof(USER_INFO_t));
				break;
			}
		}

		return true;
	}
	catch (...)
	{

	}

	return false;
}

void CHttp_old::clear_user_info(void)
{
	try
	{
		for(int i=0;i<USER_MAX_COUNT;i++)
		{
			memset(&m_user_info[i],0x0,sizeof(USER_INFO_t));
		}
	}
	catch (...)
	{
		
	}
	return;
}

bool CHttp_old::set_current_user_info(const TCHAR* date,int upload_type)
{
	try
	{
		string_conversion string_con;
		m_login_type = 0;

		//得到信息
		string_con.widechar_to_multibyte(date,m_pc_share_user_info,sizeof(m_pc_share_user_info));
		
		WriteLog(__FL__, L"上传的用户名和密码为:");
		WriteLog(__FL__, date);
	}
	catch (...)
	{
		
	}

	return false;
}
 

bool CHttp_old::get_user_info(char *user_info)
{
	try
	{
		char one_user[256];
		bool add_dot=false;
		string_conversion string_conv;
		TCHAR log[2048];

		if (NULL==user_info)
		{
			return false;
		}
		//组织成json格式
		strcpy(user_info,"[");
		for(int i=0;i<USER_MAX_COUNT;i++)
		{
			if (0!=strcmp(m_user_info[i].user_name,""))
			{
				memset(one_user,0x0,sizeof(one_user));
				//组织一条用户记录
				sprintf(one_user,"{\"username\":\"%s\",\"password\":\"%s\",\"type\":\"%s\"}",m_user_info[i].user_name,m_user_info[i].passowrd,m_user_info[i].type);
				if (add_dot)
				{
					strcat(user_info,",");
				}
				strcat(user_info,one_user);
				add_dot = true;
			}
		}
		strcat(user_info,"]");

		memset(log,0x0,sizeof(log));
		string_conv.multibyte_to_widechar(user_info,log,sizeof(log));
		WriteLog(__FL__, log);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}


bool CHttp_old::convert_blank_space(char *src_str, char *des_str)
{
	try
	{
		char no_space_string[256];

		memset(no_space_string,0x0,sizeof(no_space_string));

		for (int i=0,j=0; i<strlen(src_str); i++,j++)
		{
			switch (src_str[i])
			{
			case 0x2B:   //+
				{
					strcpy(no_space_string+j,"%2B");
					j+=2;
				}
				break;
			case 0x2D://-
				{
					strcpy(no_space_string+j,"%2D");
					j+=2;
				}
				break;
			case 0x20: //空格
				{
					strcpy(no_space_string+j,"%20");
					j+=2;
				}
				break;
			case 0x21:   //!
				{
					strcpy(no_space_string+j,"%21");
					j+=2;
				}
				break;
			case 0x2F:  // /
				{
					strcpy(no_space_string+j,"%2F");
					j+=2;
				}
				break;
			case 0x3F:   //?
				{
					strcpy(no_space_string+j,"%3F");
					j+=2;
				}
				break;
			case 0x25:  //%
				{
					strcpy(no_space_string+j,"%25");
					j+=2;
				}
				break;
			case 0x23:  //#
				{
					strcpy(no_space_string+j,"%23");
					j+=2;
				}
				break;
			case 0x26:  //&
				{
					strcpy(no_space_string+j,"%26");
					j+=2;
				}
				break;
			case 0x27:  //`
				{
					strcpy(no_space_string+j,"%27");
					j+=2;
				}
				break;
			case 0x28:  //( 
				{
					strcpy(no_space_string+j,"%28");
					j+=2;
				}
				break;
			case 0x29:  //)
				{
					strcpy(no_space_string+j,"%29");
					j+=2;
				}
				break;
			case 0x2A: //*
				{
					strcpy(no_space_string+j,"%2A");
					j+=2;
				}
				break;
			case 0x3D:  // = 
				{
					strcpy(no_space_string+j,"%3D");
					j+=2;
				}
				break;
			case 0x60: //'
				{
					strcpy(no_space_string+j,"%60");
					j+=2;
				}
				break;
			default:
				{
					no_space_string[j] = src_str[i];
				}
				break;
			}
		}

		strcpy(des_str, no_space_string);

		return true;
	}
	catch (...)
	{

	}

	return false;
}

/*
bool CHttp_old::convert_blank_space(char *src_str, char *des_str)
{
	try
	{
		char no_space_string[512];
		char tmp[4];

		memset(no_space_string,0x0,sizeof(no_space_string));

		for (int i=0; i<strlen(src_str); i++)
		{
			memset(tmp, 0x0, sizeof(tmp));

			if (((BYTE)src_str[i]) < 128)
			{
				if( ((src_str[i] >= 'a') && (src_str[i] <= 'z')) || ((src_str[i] >= 'A') && (src_str[i] <= 'Z')) || ((src_str[i] >= '0') && (src_str[i] <= '9') ) )
				{		
					sprintf(tmp,"%c",src_str[i]);
					strcat(no_space_string, tmp);
				}
				else
				{
					strcat(no_space_string, "%");
					sprintf(tmp,"%02X", src_str[i]);
					strcat(no_space_string, tmp);
				}
			}
			else
			{
				no_space_string[strlen(no_space_string)] = src_str[i];
			}			
		}

		strcpy(des_str, no_space_string);

		return true;
	}
	catch (...)
	{

	}

	return false;
}*/
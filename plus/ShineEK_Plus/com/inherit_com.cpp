#include "StdAfx.h"
#include ".\inherit_com.h"
#include "..\file\config_file.h"
#include "com_variable.h"
#include "..\message.h"
#include "..\common\StringCodeConversion.h"
#include "..\common\init_socket.h"

//存储定时器要发送的值
std::wstring g_send_com_value;

#pragma warning(disable: 4267 4311 4312)


#define covert_coordinate(c1,c2) (unsigned short)((c1<<8)|(c2))

inherit_com::inherit_com(void)
{
	m_parent_handle = 0;
	m_com_send_group_count=0;
	m_send_thread_handle=NULL;
	for (int i=0;i<COM_RECEIVE_VALUE_FLAG_MAX_COUNT;i++)
	{
		memset(com_receive_value[i],0x0,sizeof(com_receive_value[i]));
		m_wall_panel_button_rect[i].SetRectEmpty();
	}
	for (int i=0;i<COM_SEND_MAX_GROUP_COUNT;i++)
	{
		memset(m_com_send_value[i],0x0,sizeof(m_com_send_value[i]));
		m_com_send_value_len[i]=0;
	}
	memset(m_recv_com_data,0x0,sizeof(m_recv_com_data));
	m_recv_data_len=0;
	m_light_control = false;
	m_light_control_ex = false;
}

inherit_com::~inherit_com(void)
{
}

bool inherit_com::init_com(HWND handle,int message,TCHAR *file_name)
{
	try
	{
		config_file_manager config_file;
		std::wstring receive_value;

		//记录父句柄
		m_parent_handle = handle;
		m_com_send_message = message;

		//只有针对中控盒等需要发码和接受码值的才需要初始化
		if ((NULL!=file_name)&&(0!=_tcscmp(file_name,L"")))
		{
			config_file.init(file_name);
			switch(message)
			{
			case DM_BOX_COM_RECEIVE_MESSAGE:    //中控盒的串口
				{
					//解析串口接收到得命令
					for (int i=0;i<COM_RECEIVE_VALUE_FLAG_MAX_COUNT;i++)
					{
						receive_value = config_file.read_string(L"receive_value",com_receive_key_name[i],L"");
						if (!receive_value.empty())
						{
							//从十六进制解析成字符串值，用于和接收到的值进行比较
							parse_com_recv_value(receive_value.c_str(),com_receive_value[i]);
						}
					}
					//串口发送间隔
					m_com_send_time_elapse = config_file.read_integer(L"setting",L"min_send_interval",100);
					if (m_com_send_time_elapse<50)
					{
						m_com_send_time_elapse = 50;
					}
					else if (m_com_send_time_elapse>1000)
					{
						m_com_send_time_elapse = 1000;
					}
				}
				break;
			case DM_WALL_PANEL_COM_RECEIVE_MESSAGE:   //墙面板触摸屏串口
				{
					for (int i=0;i<COM_RECEIVE_VALUE_FLAG_MAX_COUNT;i++)
					{
						receive_value = config_file.read_string(L"button_rect",com_receive_key_name[i],L"");
						if (!receive_value.empty())
						{
							//解析坐标，用于和接收到的值进行比较
							parse_button_rect_value(receive_value.c_str(),i);
						}
					}
				}
				break;
			default:
				break;
			}
			//检测是否直接控制音效器
			m_conn_audio_effect = config_file.read_boolean(L"setting",L"conn_audio_effect",false);
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

void inherit_com::on_receive()
{
	try
	{
		unsigned char receive_value[128];
		int byte=0;
		int receive_len=0;
		int string_len=0;

		if (m_recv_data_len>=TOUCH_SCREEN_MAX_BYTE)
		{
			memset(m_recv_com_data,0x0,sizeof(m_recv_com_data));
			m_recv_data_len=0;
		}

		//接受数据
		memset(receive_value,0x0,sizeof(receive_value));
		byte = read(receive_value,sizeof(receive_value));
		//赋值数据
		memcpy(m_recv_com_data+m_recv_data_len,receive_value,byte);
		m_recv_data_len += byte;
		if (m_recv_data_len>0)
		{
			//接收到了数据
			switch(m_com_send_message)
			{
			case DM_BOX_COM_RECEIVE_MESSAGE:  //中控盒消息
				{
					//求字符串长度
					receive_len = strlen((const char *)receive_value);
					for (int i=0;i<COM_RECEIVE_VALUE_FLAG_MAX_COUNT;i++)
					{
						string_len = strlen((const char *)com_receive_value[i]);
#ifdef SHIDIAN_TWO_WALL_PANEL   //视点双墙面板
						if ((0==strncmp((const char *)com_receive_value[i],(const char *)receive_value,receive_len))||(0==strncmp((const char *)com_receive_value[i]+(string_len-receive_len),(const char *)receive_value,receive_len)))
#else
						if (0==strcmp((const char *)com_receive_value[i],(const char *)receive_value) &&
							0!=strcmp("",(const char *)receive_value))
#endif
						{
							//找到了匹配的命令，发送命令标示给主程序
							::PostMessage(m_parent_handle,DM_BOX_COM_RECEIVE_MESSAGE,i,NULL);
						}
					}
					//初始化
					memset(m_recv_com_data,0x0,sizeof(m_recv_com_data));
					m_recv_data_len=0;
				}
				break;
			case DM_SCREEN_COM_RECEIVE_MESSAGE:        //吧台触摸屏消息
			case DM_WALL_PANEL_COM_RECEIVE_MESSAGE:    //墙面板触摸屏消息
			case DM_DOORPLATE_COM_RECV_MESSAGE:        //门牌机
				{
					//if(0xFF==m_recv_com_data[7] && 0x00==m_recv_com_data[8]) //数据报的结束符
					//if (m_recv_com_data[9] == (0xFF&(m_recv_com_data[2]+m_recv_com_data[3]+m_recv_com_data[4]+m_recv_com_data[5]+m_recv_com_data[6]-0xAE)))  //如果校验结果为真
					//不判断结束符和校验位，只判断开始符
					if ((0x55==receive_value[0])&&(0x54==receive_value[1])) //数据报的开始符
					{
						if((0x81 == receive_value[2])&&(byte>=7)) //如果按下
						{
							//转化成坐标 
							int x_coordinate = (unsigned int)covert_coordinate(receive_value[4],receive_value[3]);
							int y_coordinate = (unsigned int)covert_coordinate(receive_value[6],receive_value[5]);
							//发送消息给主程序
							//公版
							::PostMessage(m_parent_handle,m_com_send_message,x_coordinate,y_coordinate);
							
							//云南墙面板
							//::PostMessage(m_parent_handle,m_com_send_message,y_coordinate,x_coordinate);
							//初始化
							memset(m_recv_com_data,0x0,sizeof(m_recv_com_data));
							m_recv_data_len=0;
						}
					}
					else if ((0x55==m_recv_com_data[0])&&(0x54==m_recv_com_data[1])) //数据报的开始符
					{
						if((0x81 == m_recv_com_data[2])&&(TOUCH_SCREEN_MAX_BYTE==m_recv_data_len)) //如果按下
						{
							//转化成坐标 
							int x_coordinate = (unsigned int)covert_coordinate(m_recv_com_data[4],m_recv_com_data[3]);
							int y_coordinate = (unsigned int)covert_coordinate(m_recv_com_data[6],m_recv_com_data[5]);
							//发送消息给主程序
							//公版
							::PostMessage(m_parent_handle,m_com_send_message,x_coordinate,y_coordinate);

							//云南墙面板
							//::PostMessage(m_parent_handle,m_com_send_message,y_coordinate,x_coordinate);
							//初始化
							memset(m_recv_com_data,0x0,sizeof(m_recv_com_data));
							m_recv_data_len=0;
						}
					}
					else if (5==m_recv_data_len)   //另一厂家的就5个字节
					{
						if (0x81==m_recv_com_data[0])
						{
							//按下
							//转化成坐标 
							int x_coordinate = (unsigned int)covert_coordinate(m_recv_com_data[1],m_recv_com_data[2]);
							int y_coordinate = (unsigned int)covert_coordinate(m_recv_com_data[3],m_recv_com_data[4]);
							//发送消息给主程序
							//::PostMessage(m_parent_handle,m_com_send_message,x_coordinate,y_coordinate);
							::PostMessage(m_parent_handle,m_com_send_message,y_coordinate,x_coordinate);
							//初始化
							memset(m_recv_com_data,0x0,sizeof(m_recv_com_data));
							m_recv_data_len=0;
						}
						else if (0x80==m_recv_com_data[0])
						{
							//抬起，初始化
							memset(m_recv_com_data,0x0,sizeof(m_recv_com_data));
							m_recv_data_len=0;
						}
					}
				}
				break;
			default:
				break;
			}
		}
	}
	catch (...)
	{
		
	}
	return;
}

void inherit_com::parse_ps2_value(int recv_value)
{
	try
	{
		char receive_value[16];

		memset(receive_value,0x0,sizeof(receive_value));

		//转化成字符串
		receive_value[0] = recv_value;

		for (int i=0;i<COM_RECEIVE_VALUE_FLAG_MAX_COUNT;i++)
		{
			if (0==strcmp((const char *)com_receive_value[i],(const char *)receive_value))
			{
				//找到了匹配的命令，发送命令标示给主程序
				::PostMessage(m_parent_handle,DM_BOX_COM_RECEIVE_MESSAGE,i,NULL);
				return;
			}
		}
	}
	catch (...)
	{
		
	}
	return;
}

void inherit_com::determine_point_in_rect(int x,int y)
{
	try
	{
		POINT touch_point;

		//构造一个点
		touch_point.x = x;
		touch_point.y = y;

		for (int i=0;i<COM_RECEIVE_VALUE_FLAG_MAX_COUNT;i++)
		{
			if (m_wall_panel_button_rect[i].PtInRect(touch_point))
			{
				//找到了匹配的命令，发送命令标示给主程序
				::PostMessage(m_parent_handle,DM_BOX_COM_RECEIVE_MESSAGE,i,NULL);
				return;
			}
		}
	}
	catch (...)
	{

	}
	return;
}

bool inherit_com::write_data(enum COM_SEND_VALUE_FLAG com_send_flag,TCHAR *file_name,TCHAR *song_number,int music_volume,int microphone_volume,int tune,int adjust_count)
{
	try
	{
		int send_count=0;
		config_file_manager config_file;
		std::wstring com_value;
		bool result=false;
		int light_code=0;
		int close_light_time=0;
		string_conversion string_conv;
		char send_data[256];
		char file_number[256];

		memset(send_data,0x0,sizeof(send_data));
		memset(file_number,0x0,sizeof(file_number));

		//***********************石家庄定制
		if (m_conn_audio_effect)  //202-09-18 modify 直接控制音效器  ZHEN 
		{
  			if (song_number && (0!=_tcscmp(song_number,L"")))
			{
				string_conv.widechar_to_multibyte(song_number,file_number,sizeof(file_number));
			}
			
			if (m_light_control)
			{
				//set_light_value(false);
				m_light_control = false;
				m_light_control_ex = true;
				memset(file_number,0x0,sizeof(file_number));
			}
			switch(com_send_flag)
			{
			case COM_SEND_MICROPHONE_VOLUME_UP:       //麦克风音量加
			case COM_SEND_MICROPHONE_VOLUME_DOWN:     //麦克风音量减
				{
					sprintf(send_data,"SetMicVolume.%d",microphone_volume);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_MUSIC_VOLUME_UP:            //音乐的音量增加
			case COM_SEND_MUSIC_VOLUME_DOWN:          //音乐的音量降低
				{
					sprintf(send_data,"SetMusicVolume.%d",music_volume);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_TUNE_UP:                    //音调增加
			case COM_SEND_TUNE_DOWN:                  //音调降低
			case COM_SEND_TUNE_STANDARD:              //音调标准
				{
					sprintf(send_data,"SetTone.%d",tune);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_AUDIO_EFFECT_STANDARD:      //标准
				{
					strcpy(send_data,"SetEffectsMode.A");
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_AUDIO_EFFECT_THEATER:       //剧场
				{
					strcpy(send_data,"SetEffectsMode.B");
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_AUDIO_EFFECT_PROFESSIONAL:  //唱将
				{
					strcpy(send_data,"SetEffectsMode.C");
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_AUDIO_EFFECT_MAGIC:         //魔音
				{
					strcpy(send_data,"SetEffectsMode.D");
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT_STANDARD:         //灯光 标准
				{
					sprintf(send_data,"SetLightMode.A-%s",file_number);
					write_com_data_UDP_IP(send_data);
					//2015-7-18 12:04:13---明亮
// 					sprintf(send_data,"SetLightMode.N-%s",file_number);
// 					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT_BACKGROUND:           //灯光 背景
				{
					sprintf(send_data,"SetLightMode.B-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT_STAGE:                //灯光 舞台
				{
					sprintf(send_data,"SetLightMode.C-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT_SCINTILLATION:        //灯光 屏闪
				{
					sprintf(send_data,"SetLightMode.D-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT_CLOSE:                //灯光 关闭
				{
					sprintf(send_data,"SetLightMode.E-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT6:   //灯光6
				{
					sprintf(send_data,"SetLightMode.F-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT7:   //灯光7
				{
					sprintf(send_data,"SetLightMode.G-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT8:   //灯光8
				{
					sprintf(send_data,"SetLightMode.H-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT9:   //灯光9
				{
					sprintf(send_data,"SetLightMode.I-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT10:   //灯光10
				{
					sprintf(send_data,"SetLightMode.K-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT1:
				{
					//sprintf(send_data,"SetLightMode.O-%s",file_number);
					//write_com_data_UDP_IP(send_data);
					sprintf(send_data,"SetLightMode.J-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT2:
				{
					//sprintf(send_data,"SetLightMode.N-%s",file_number);
					//write_com_data_UDP_IP(send_data);
					sprintf(send_data,"SetLightMode.I-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT3:
				{
					//sprintf(send_data,"SetLightMode.M-%s",file_number);
					//write_com_data_UDP_IP(send_data);
					sprintf(send_data,"SetLightMode.H-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT4:
				{
					//sprintf(send_data,"SetLightMode.L-%s",file_number);
					//write_com_data_UDP_IP(send_data);
					sprintf(send_data,"SetLightMode.G-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT5:
				{
					//sprintf(send_data,"SetLightMode.K-%s",file_number);
					//write_com_data_UDP_IP(send_data);
					sprintf(send_data,"SetLightMode.F-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT_OPEN:
				{
					sprintf(send_data,"SetLightMode.P-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_PLAYER_PAUSE:     //暂停
				{
					strcpy(send_data,"SetPlayer.PAUSE");
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_PLAYER_PLAY:     //播放
				{
					strcpy(send_data,"SetPlayer.PLAY");
					write_com_data_UDP_IP(send_data);
				}
				break;
			default:
				break;
			}
		}
		//////////////////////////////////////////////////////////////////////////////*/

		//检测串口是否打开成功
		result = is_open();
		if (!result)
		{
			//if open fail, return
			return false;
		}

		memset(send_data,0x0,sizeof(send_data));
		//init com file
		config_file.init(file_name);

		switch(com_send_flag)
		{
		case COM_SEND_POWER_ON:             //开机
			{
				com_value = config_file.read_string(L"send_value",L"power_on",L"");
			}
			break;
		case COM_SEND_POWER_OFF:            //关机
			{
				com_value = config_file.read_string(L"send_value",L"power_off",L"");
			}
			break;
		case COM_SEND_CLOSE_ROOM:           //关房
			{
				com_value = config_file.read_string(L"send_value",L"close_room",L"");
				close_light_time = config_file.read_integer(L"setting",L"close_light_time",0);
				if (close_light_time>0)
				{
					//表示要延时关灯
					g_send_com_value = config_file.read_string(L"send_value",L"light_close",L"");
					if (!g_send_com_value.empty())
					{
						//定时器只启动一次
						timeSetEvent(close_light_time*1000,0,send_com_callback,(DWORD)this,TIME_CALLBACK_FUNCTION|TIME_ONESHOT);
					}					
				}
			}
			break;
		case COM_SEND_OPEN_ROOM:            //开房
			{
				com_value = config_file.read_string(L"send_value",L"open_room",L"");
			}
			break;
		case COM_SEND_NEXT_SONG:         //下一首
			{
				com_value = config_file.read_string(L"send_value",L"next_song",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_STANDARD:   //标准
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_standard",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_THEATER:       //剧场
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_theater",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_PROFESSIONAL:  //唱将
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_professional",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_MAGIC:         //魔音
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_magic",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_RESERVE1:     //音效预留
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_reserve1",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_RESERVE2:     //音效预留
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_reserve2",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_RESERVE3:     //音效预留
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_reserve3",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_RESERVE4:     //音效预留
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_reserve4",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_STANDARD:      //音乐音效标准
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_standard",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_THEATER:       //音乐音效剧场
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_theater",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_PROFESSIONAL:  //音乐音效唱将
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_professional",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_MAGIC:         //音乐音效魔音
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_magic",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_RESERVE1:      //音乐音效预留
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_reserve1",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_RESERVE2:      //音乐音效预留
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_reserve2",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_RESERVE3:      //音乐音效预留
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_reserve3",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_RESERVE4:      //音乐音效预留
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_reserve4",L"");
			}
			break;
		case COM_SEND_MICROPHONE_VOLUME_UP:      //麦克风音量加
			{
				com_value = config_file.read_string(L"send_value",L"microphone_volume_up",L"");
			}
			break;
		case COM_SEND_MICROPHONE_VOLUME_DOWN:     //麦克风音量减
			{
				com_value = config_file.read_string(L"send_value",L"microphone_volume_down",L"");
			}
			break;
		case COM_SEND_TUNE_UP:                    //音调增加
			{
				com_value = config_file.read_string(L"send_value",L"tune_up",L"");
			}
			break;
		case COM_SEND_TUNE_DOWN:                  //音调降低
			{
				com_value = config_file.read_string(L"send_value",L"tune_down",L"");
			}
			break;
		case COM_SEND_TUNE_STANDARD:             //音调标准
			{
				com_value = config_file.read_string(L"send_value",L"tune_standard",L"");
			}
			break;
		case COM_SEND_LIGHT1:                     //灯光1
			{
				com_value = config_file.read_string(L"send_value",L"light_open1",L"");
			}
			break;
		case COM_SEND_LIGHT2:                     //灯光1
			{
				com_value = config_file.read_string(L"send_value",L"light_open2",L"");
			}
			break;
		case COM_SEND_LIGHT3:                     //灯光1
			{
				com_value = config_file.read_string(L"send_value",L"light_open3",L"");
			}
			break;
		case COM_SEND_LIGHT4:                     //灯光1
			{
				com_value = config_file.read_string(L"send_value",L"light_open4",L"");
			}
			break;
		case COM_SEND_LIGHT5:                     //灯光1
			{
				com_value = config_file.read_string(L"send_value",L"light_open5",L"");
			}
			break;
		case COM_SEND_LIGHT6:                     //灯光1
			{
				com_value = config_file.read_string(L"send_value",L"light_open6",L"");
			}
			break;
		case COM_SEND_LIGHT7:                     //灯光1
			{
				com_value = config_file.read_string(L"send_value",L"light_open7",L"");
			}
			break;
		case COM_SEND_LIGHT8:                     //灯光1
			{
				com_value = config_file.read_string(L"send_value",L"light_open8",L"");
			}
			break;
		case COM_SEND_LIGHT_STANDARD:             //灯光 标准
			{
				com_value = config_file.read_string(L"send_value",L"light_standard",L"");
			}
			break;
		case COM_SEND_LIGHT_BACKGROUND:           //灯光 背景
			{
				com_value = config_file.read_string(L"send_value",L"light_background",L"");
			}
			break;
		case COM_SEND_LIGHT_STAGE:                //灯光 舞台
			{
				com_value = config_file.read_string(L"send_value",L"light_stage",L"");
			}
			break;
		case COM_SEND_LIGHT_SCINTILLATION:        //灯光 屏闪
			{
				com_value = config_file.read_string(L"send_value",L"light_scintillation",L"");
			}
			break;
		case COM_SEND_LIGHT_OPEN:                //灯光 开
			{
				com_value = config_file.read_string(L"send_value",L"light_open",L"");
			}
			break;
		case COM_SEND_LIGHT_CLOSE:               //灯光 关闭
			{
				com_value = config_file.read_string(L"send_value",L"light_close",L"");
			}
			break;
		case COM_SEND_LIGHT_MUTE:               //灯光 静音
			{
				com_value = config_file.read_string(L"send_value",L"light_mute",L"");
			}
			break;
		case COM_SEND_LIGHT_PAUSE:               //灯光 暂停
			{
				com_value = config_file.read_string(L"send_value",L"light_pause",L"");
			}
			break;
		case COM_SEND_MUSIC_VOLUME_UP:            //音乐的音量增加
			{
				com_value = config_file.read_string(L"send_value",L"music_volume_up",L"");
			}
			break;
		case COM_SEND_MUSIC_VOLUME_DOWN:          //音乐的音量降低
			{
				com_value = config_file.read_string(L"send_value",L"music_volume_DOWN",L"");
			}
			break;
		case COM_SEND_SCREEN_SWITCH:              //画面交换
			{
				com_value = config_file.read_string(L"send_value",L"tv_screen_switch",L"");
			}
			break;
		case COM_SEND_TV_CHANNEL_UP:              //频道增加
			{
				com_value = config_file.read_string(L"send_value",L"tv_channel_up",L"");
			}
			break;
		case COM_SEND_TV_CHANNEL_DOWN:            //频道减低
			{
				com_value = config_file.read_string(L"send_value",L"tv_channel_down",L"");
			}
			break;
		case COM_SEND_REQUEST_SERVER:           //请求服务
			{
				com_value = config_file.read_string(L"send_value",L"request_server",L"");
			}
			break;
		case COM_SEND_CANCEL_SERVER:              //取消服务
			{
				com_value = config_file.read_string(L"send_value",L"cancel_server",L"");
			}
			break;
		case COM_SEND_CLOSE_SERVICE_LIGHT:        //关闭服务灯
			{
				com_value = config_file.read_string(L"send_value",L"close_service_light",L"");
			}
			break;
		case COM_SEND_REVERBERATION_DOWN:         //混响减
			{
				com_value = config_file.read_string(L"send_value",L"reverberation_down",L"");
			}
			break;
		case COM_SEND_REVERBERATION_UP:           //混响加
			{
				com_value = config_file.read_string(L"send_value",L"reverberation_up",L"");
			}
			break;
		case COM_SEND_AIR_CONDITION_STRONG:       //空调强
			{
				com_value = config_file.read_string(L"send_value",L"air_condition_strong",L"");
			}
			break;
		case COM_SEND_AIR_CONDITION_MID:          //空调中
			{
				com_value = config_file.read_string(L"send_value",L"air_condition_mid",L"");
			}
			break;
		case COM_SEND_AIR_CONDITION_WEAK:         //空调弱
			{
				com_value = config_file.read_string(L"send_value",L"air_condition_weak",L"");
			}
			break;
		case COM_SEND_AIR_CONDITION_CLOSE:        //空调关闭
			{
				com_value = config_file.read_string(L"send_value",L"air_condition_close",L"");
			}
			break;
		case COM_SEND_DISCHARGE_AIR_FUNCTION:     //排风
			{
				com_value = config_file.read_string(L"send_value",L"discharge_air",L"");
			}
			break;
		default:
			return true;
		}
		if (com_value.empty())
		{
			return false;
		}
#ifdef GUANGXI_AUDIO_EFFECT  //广西音效器
		switch(com_send_flag)
		{
		case COM_SEND_MICROPHONE_VOLUME_UP:       //麦克风音量加
		case COM_SEND_MICROPHONE_VOLUME_DOWN:     //麦克风音量减
			{
				sprintf(send_data,"SetMicVolume.%d",microphone_volume);
				write_com_data_UDP_IP(send_data);
			}
			return true;
		case COM_SEND_MUSIC_VOLUME_UP:            //音乐的音量增加
		case COM_SEND_MUSIC_VOLUME_DOWN:          //音乐的音量降低
			{
				sprintf(send_data,"SetMusicVolume.%d",music_volume);
				write_com_data_UDP_IP(send_data);
			}
			return true;
		case COM_SEND_TUNE_UP:                    //音调增加
		case COM_SEND_TUNE_DOWN:                  //音调降低
		case COM_SEND_TUNE_STANDARD:              //音调标准
			{
				sprintf(send_data,"SetTone.%d",tune);
				write_com_data_UDP_IP(send_data);
			}
			return true;
		case COM_SEND_AUDIO_EFFECT_STANDARD:      //标准
			{
				strcpy(send_data,"SetEffectsMode.A");
				write_com_data_UDP_IP(send_data);
			}
			return true;
		case COM_SEND_AUDIO_EFFECT_THEATER:       //剧场
			{
				strcpy(send_data,"SetEffectsMode.B");
				write_com_data_UDP_IP(send_data);
			}
			return true;
		case COM_SEND_AUDIO_EFFECT_PROFESSIONAL:  //唱将
			{
				strcpy(send_data,"SetEffectsMode.C");
				write_com_data_UDP_IP(send_data);
			}
			return true;
		case COM_SEND_AUDIO_EFFECT_MAGIC:         //魔音
			{
				strcpy(send_data,"SetEffectsMode.D");
				write_com_data_UDP_IP(send_data);
			}
			return true;
		default:
			break;
		}
#endif
		//解析成要发送的值
		result = parse_com_send_value(com_value.c_str(),com_send_flag,music_volume,microphone_volume,tune);
		if (result)
		{
			//音调、音乐音量、麦克音量可能同时调整多次
			switch(com_send_flag)
			{
			case COM_SEND_TUNE_UP:                //音调增加
			case COM_SEND_TUNE_DOWN:              //音调降低
			case COM_SEND_MICROPHONE_VOLUME_DOWN: //麦克音量降低
			case COM_SEND_MICROPHONE_VOLUME_UP:   //麦克音量调高
			case COM_SEND_MUSIC_VOLUME_DOWN:      //音乐音量调低
			case COM_SEND_MUSIC_VOLUME_UP:        //音乐音量调高
				{
					if (adjust_count>1)
					{
						if (adjust_count>=COM_SEND_MAX_GROUP_COUNT)
						{
							adjust_count = COM_SEND_MAX_GROUP_COUNT; 
						}
						//记录总的发送数
						m_com_send_group_count = adjust_count-1;
						//第一组做母本，拷贝到其他组
						for (int i=1;i<=m_com_send_group_count;i++)
						{
							memcpy(m_com_send_value[i],m_com_send_value[0],m_com_send_value_len[0]);
							m_com_send_value_len[i] = m_com_send_value_len[0];
						}
					}
				}
				break;
			default:
				break;
			}
			//发送到串口
			if(m_com_send_group_count>0)
			{
				//如果有多组，就要启动定时器来发送
				m_send_thread_handle = AfxBeginThread(inherit_com::send_com_value_thread,this);
			}
			else
			{
				//只有一组，直接发送到串口
				send_count = write(m_com_send_value[0],m_com_send_value_len[0]);
			}
			return true;
		}

		return false;
	}
	catch (...)
	{
		
	}
	return false;
}

bool inherit_com::parse_com_recv_value(const TCHAR *com_value,unsigned char *recv_value)
{
	try
	{
		TCHAR value[256];
		int com_char=0;
		int char_number=0;

			memset(value,0x0,sizeof(value));

		_tcscpy(value,com_value);

		for (unsigned int i=0;i<_tcslen(value);i+=5)
		{
			com_char=0;
			swscanf(value+i+2,L"%x",&com_char);
			recv_value[char_number] = com_char;
			char_number++;
		}

		return true;
	}
	catch (...) {
	}
	
	return false;
}

bool inherit_com::parse_button_rect_value(const TCHAR *rect,int number)
{
	try
	{
		int left_x=0;
		int top_y=0;
		int right_x=0;
		int bottom_y=0;

		//解析各个坐标值
		swscanf(rect,L"%d:%d:%d:%d",&left_x,&top_y,&right_x,&bottom_y);
		//保存坐标
		m_wall_panel_button_rect[number].SetRect(left_x,top_y,right_x,bottom_y);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool inherit_com::parse_com_send_value(const TCHAR *com_value,enum COM_SEND_VALUE_FLAG com_send_flag,int music_volume,int microphone_volume,int tune)
{
	try
	{
		TCHAR value[1024];
		int com_char=0;
		int char_number=0;

		//初始化
		memset(value,0x0,sizeof(value));
		for (int i=0;i<COM_SEND_MAX_GROUP_COUNT;i++)
		{
			memset(m_com_send_value[i],0x0,sizeof(m_com_send_value[i]));
			m_com_send_value_len[i]=0;
		}
		m_com_send_group_count = 0;
		//保存要解析的串口值
		_tcscpy(value,com_value);

		for (unsigned int i=0;i<_tcslen(value);i+=5)
		{
			if (0==_tcsncmp(value+i,L"0xYY",4))
			{
				//遇到分隔符进行分隔
				m_com_send_group_count++;
				if (m_com_send_group_count>=(COM_SEND_MAX_GROUP_COUNT-1))
				{
					break;
				}
				char_number=0;
				continue;
			}
			//2010-11-16 add
			else if (0 == _tcsncmp(value+i,L"0xRR",4))
			{
				//发送实际值
				switch (com_send_flag)
				{
				case COM_SEND_MICROPHONE_VOLUME_UP:      //麦克风音量加
				case COM_SEND_MICROPHONE_VOLUME_DOWN:     //麦克风音量减
					{
						m_com_send_value[m_com_send_group_count][char_number] = microphone_volume;
						m_com_send_value_len[m_com_send_group_count]++;
						char_number++;
					}
					break;
				case COM_SEND_TUNE_UP:                    //音调增加
				case COM_SEND_TUNE_DOWN:                  //音调降低
				case COM_SEND_TUNE_STANDARD:             //音调标准
					{
						m_com_send_value[m_com_send_group_count][char_number] = tune;
						m_com_send_value_len[m_com_send_group_count]++;
						char_number++;
					}
					break;
				case COM_SEND_MUSIC_VOLUME_UP:            //音乐的音量增加
				case COM_SEND_MUSIC_VOLUME_DOWN:          //音乐的音量降低
					{
						m_com_send_value[m_com_send_group_count][char_number] = music_volume;
						m_com_send_value_len[m_com_send_group_count]++;
						char_number++;
					}
					break;
				case COM_SEND_REVERBERATION_DOWN:         //混响减
					break;
				case COM_SEND_REVERBERATION_UP:           //混响加
					break;
				default:
					break;
				}

				continue;
			}
			else if (0 == _tcsncmp(value+i,L"0xSS",4)) 
			{
				//和校验
				BYTE Check = 0;
				for (int k = 0; k < char_number; k++)
				{
					Check += m_com_send_value[m_com_send_group_count][k];
				}
				m_com_send_value[m_com_send_group_count][char_number] = Check;
				m_com_send_value_len[m_com_send_group_count]++;
				char_number++;

				continue;
			}
			else if (0 == _tcsncmp(value+i,L"0xTT",4)) 
			{
				BYTE Check = 0;
				for (int k = 0; k < char_number; k++)
				{
					Check += m_com_send_value[m_com_send_group_count][k];
				}
				m_com_send_value[m_com_send_group_count][char_number] = 0xFF ^ Check;
				m_com_send_value_len[m_com_send_group_count]++;
				char_number++;
				continue;
			}
			else if (0 == _tcsncmp(value+i,L"0xUU",4)) 
			{
				BYTE Check = 0;
				for (int k = 0; k < char_number; k++)
				{
					Check += m_com_send_value[m_com_send_group_count][k];
				}
				m_com_send_value[m_com_send_group_count][char_number] = 256 - Check;
				m_com_send_value_len[m_com_send_group_count]++;
				char_number++;

				continue;
			}
			else if (0 == _tcsncmp(value+i,L"0xVV",4)) 
			{
				BYTE Check = 0;
				for (int k = 2; k < char_number; k++)
				{
					Check += m_com_send_value[m_com_send_group_count][k];	
				}
				m_com_send_value[m_com_send_group_count][char_number] = Check % 0xfe;
				m_com_send_value_len[m_com_send_group_count]++;
				char_number++;

				continue;
			}
			else if (0 == _tcsncmp(value+i,L"0xWW",4)) 
			{
				BYTE Check = 0;
				for (int k = 1; k < char_number; k++)
				{
					Check += m_com_send_value[m_com_send_group_count][k];
				}
				m_com_send_value[m_com_send_group_count][char_number] = Check;
				m_com_send_value_len[m_com_send_group_count]++;
				char_number++;

				continue;
			}
			else if (0 == _tcsncmp(value+i,L"0xGG",4)) 
			{
				if (com_send_flag == COM_SEND_TUNE_UP || com_send_flag == COM_SEND_TUNE_DOWN || com_send_flag ==  COM_SEND_TUNE_STANDARD)
				{
					if (tune < 0)
						m_com_send_value[m_com_send_group_count][char_number] = 0x10 - tune;
					else
						m_com_send_value[m_com_send_group_count][char_number] = tune;
				}
				m_com_send_value_len[m_com_send_group_count]++;
				char_number++;

				continue;
			}
			else if (0 == _tcsncmp(value+i, L"0xHH",4)) 
			{
				m_com_send_value[m_com_send_group_count][char_number - 1] += 0x75;

				continue;
			}

			com_char = 0;
			swscanf(value+i+2,L"%x",&com_char);
			m_com_send_value[m_com_send_group_count][char_number] = com_char;
			m_com_send_value_len[m_com_send_group_count]++;
			char_number++;
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

UINT inherit_com::send_com_value_thread(LPVOID pParam)
{
	try
	{
		inherit_com *pThis = reinterpret_cast<inherit_com *>(pParam);
		pThis->write_com_data();

	}
	catch (...)
	{
		
	}
	return 0;
}

void inherit_com::write_com_data(void)
{
	try
	{
		int send_count=0;
		
		while (1)
		{			
			//发送窗口数据
			send_count = write(m_com_send_value[m_com_send_group_count],m_com_send_value_len[m_com_send_group_count]);
			if (m_com_send_group_count<=0)
			{
				//小于0表示已经发送完毕，结束线程
				break;
			}
			//要发送的组数减一
			m_com_send_group_count--;
			Sleep(m_com_send_time_elapse);
		}
	}
	catch (...)
	{
		
	}
	return;
}

void inherit_com::write_com_data_UDP_IP(char *data)
{
	try
	{
		//创建一个socket
		SOCKET com_socket = ::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

		//off TIME_WAIT
		struct linger zeroLinger;	
		zeroLinger.l_onoff = 1;	
		zeroLinger.l_linger = 5;

		setsockopt(com_socket,SOL_SOCKET,SO_LINGER,(const char *)&zeroLinger	,sizeof(zeroLinger));

		int m_nSendTimeout = 6000;
		//set send timeout
		setsockopt(com_socket,SOL_SOCKET,SO_SNDTIMEO,(const char *)&m_nSendTimeout,sizeof(m_nSendTimeout));

		// 也可以在这里调用bind函数绑定一个本地地址
		// 否则系统将会自动安排

		// 填写远程地址信息
		sockaddr_in servAddr; 
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = htons(1983);
		// 注意，这里要填写服务器程序（TCPServer程序）所在机器的IP地址
		// 如果你的计算机没有联网，直接使用127.0.0.1即可
		servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		//发送数据
		::sendto(com_socket, (char *)data,strlen(data),0,(sockaddr *)&servAddr,sizeof(sockaddr_in));
		// 关闭套节字
		::closesocket(com_socket);
	}
	catch (...)
	{

	}
	return;
}

void WINAPI inherit_com::send_com_callback(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	try
	{
		inherit_com *pThis = reinterpret_cast<inherit_com *>(dwUser);

		pThis->write_com_data_timer();
	}
	catch (...)
	{

	}
	return ;
}

void inherit_com::write_com_data_timer(void)
{
	try
	{
		TCHAR send_value[1024];
		int com_char=0;
		unsigned char com_send_value[256];
		int byte_size=0;
		int send_count=0;

		memset(send_value,0x0,sizeof(send_value));

		_tcscpy(send_value,g_send_com_value.c_str());

		for (unsigned int i=0;i<_tcslen(send_value);i+=5)
		{
			swscanf(send_value+i+2,L"%x",&com_char);
			com_send_value[byte_size] = com_char;
			byte_size++;
		}

		//发送窗口数据
		send_count = write(com_send_value,byte_size);
	}
	catch (...)
	{

	}
	return;
}
void inherit_com::set_light_value(bool light)
{
	try
	{
		m_light_control = light;
	}
	catch(...)
	{

	}
}
 bool inherit_com::get_light_value()
 {
	 try
	 {
		return m_light_control;
	 }
	 catch(...)
	 {

	 }
 }
 void inherit_com::set_light_value_ex(bool light_ex)
 {
	 try
	 {
		 m_light_control_ex = light_ex;
	 }
	 catch(...)
	 {

	 }
 }
 bool inherit_com::get_light_value_ex()
 {
	 try
	 {
		 return m_light_control_ex;
	 }
	 catch(...)
	 {

	 }
 }
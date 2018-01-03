#include "StdAfx.h"
#include ".\inherit_com.h"
#include "..\file\config_file.h"
#include "com_variable.h"
#include "..\message.h"
#include "..\common\StringCodeConversion.h"
#include "..\common\init_socket.h"

//�洢��ʱ��Ҫ���͵�ֵ
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

		//��¼�����
		m_parent_handle = handle;
		m_com_send_message = message;

		//ֻ������пغе���Ҫ����ͽ�����ֵ�Ĳ���Ҫ��ʼ��
		if ((NULL!=file_name)&&(0!=_tcscmp(file_name,L"")))
		{
			config_file.init(file_name);
			switch(message)
			{
			case DM_BOX_COM_RECEIVE_MESSAGE:    //�пغеĴ���
				{
					//�������ڽ��յ�������
					for (int i=0;i<COM_RECEIVE_VALUE_FLAG_MAX_COUNT;i++)
					{
						receive_value = config_file.read_string(L"receive_value",com_receive_key_name[i],L"");
						if (!receive_value.empty())
						{
							//��ʮ�����ƽ������ַ���ֵ�����ںͽ��յ���ֵ���бȽ�
							parse_com_recv_value(receive_value.c_str(),com_receive_value[i]);
						}
					}
					//���ڷ��ͼ��
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
			case DM_WALL_PANEL_COM_RECEIVE_MESSAGE:   //ǽ��崥��������
				{
					for (int i=0;i<COM_RECEIVE_VALUE_FLAG_MAX_COUNT;i++)
					{
						receive_value = config_file.read_string(L"button_rect",com_receive_key_name[i],L"");
						if (!receive_value.empty())
						{
							//�������꣬���ںͽ��յ���ֵ���бȽ�
							parse_button_rect_value(receive_value.c_str(),i);
						}
					}
				}
				break;
			default:
				break;
			}
			//����Ƿ�ֱ�ӿ�����Ч��
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

		//��������
		memset(receive_value,0x0,sizeof(receive_value));
		byte = read(receive_value,sizeof(receive_value));
		//��ֵ����
		memcpy(m_recv_com_data+m_recv_data_len,receive_value,byte);
		m_recv_data_len += byte;
		if (m_recv_data_len>0)
		{
			//���յ�������
			switch(m_com_send_message)
			{
			case DM_BOX_COM_RECEIVE_MESSAGE:  //�пغ���Ϣ
				{
					//���ַ�������
					receive_len = strlen((const char *)receive_value);
					for (int i=0;i<COM_RECEIVE_VALUE_FLAG_MAX_COUNT;i++)
					{
						string_len = strlen((const char *)com_receive_value[i]);
#ifdef SHIDIAN_TWO_WALL_PANEL   //�ӵ�˫ǽ���
						if ((0==strncmp((const char *)com_receive_value[i],(const char *)receive_value,receive_len))||(0==strncmp((const char *)com_receive_value[i]+(string_len-receive_len),(const char *)receive_value,receive_len)))
#else
						if (0==strcmp((const char *)com_receive_value[i],(const char *)receive_value) &&
							0!=strcmp("",(const char *)receive_value))
#endif
						{
							//�ҵ���ƥ���������������ʾ��������
							::PostMessage(m_parent_handle,DM_BOX_COM_RECEIVE_MESSAGE,i,NULL);
						}
					}
					//��ʼ��
					memset(m_recv_com_data,0x0,sizeof(m_recv_com_data));
					m_recv_data_len=0;
				}
				break;
			case DM_SCREEN_COM_RECEIVE_MESSAGE:        //��̨��������Ϣ
			case DM_WALL_PANEL_COM_RECEIVE_MESSAGE:    //ǽ��崥������Ϣ
			case DM_DOORPLATE_COM_RECV_MESSAGE:        //���ƻ�
				{
					//if(0xFF==m_recv_com_data[7] && 0x00==m_recv_com_data[8]) //���ݱ��Ľ�����
					//if (m_recv_com_data[9] == (0xFF&(m_recv_com_data[2]+m_recv_com_data[3]+m_recv_com_data[4]+m_recv_com_data[5]+m_recv_com_data[6]-0xAE)))  //���У����Ϊ��
					//���жϽ�������У��λ��ֻ�жϿ�ʼ��
					if ((0x55==receive_value[0])&&(0x54==receive_value[1])) //���ݱ��Ŀ�ʼ��
					{
						if((0x81 == receive_value[2])&&(byte>=7)) //�������
						{
							//ת�������� 
							int x_coordinate = (unsigned int)covert_coordinate(receive_value[4],receive_value[3]);
							int y_coordinate = (unsigned int)covert_coordinate(receive_value[6],receive_value[5]);
							//������Ϣ��������
							//����
							::PostMessage(m_parent_handle,m_com_send_message,x_coordinate,y_coordinate);
							
							//����ǽ���
							//::PostMessage(m_parent_handle,m_com_send_message,y_coordinate,x_coordinate);
							//��ʼ��
							memset(m_recv_com_data,0x0,sizeof(m_recv_com_data));
							m_recv_data_len=0;
						}
					}
					else if ((0x55==m_recv_com_data[0])&&(0x54==m_recv_com_data[1])) //���ݱ��Ŀ�ʼ��
					{
						if((0x81 == m_recv_com_data[2])&&(TOUCH_SCREEN_MAX_BYTE==m_recv_data_len)) //�������
						{
							//ת�������� 
							int x_coordinate = (unsigned int)covert_coordinate(m_recv_com_data[4],m_recv_com_data[3]);
							int y_coordinate = (unsigned int)covert_coordinate(m_recv_com_data[6],m_recv_com_data[5]);
							//������Ϣ��������
							//����
							::PostMessage(m_parent_handle,m_com_send_message,x_coordinate,y_coordinate);

							//����ǽ���
							//::PostMessage(m_parent_handle,m_com_send_message,y_coordinate,x_coordinate);
							//��ʼ��
							memset(m_recv_com_data,0x0,sizeof(m_recv_com_data));
							m_recv_data_len=0;
						}
					}
					else if (5==m_recv_data_len)   //��һ���ҵľ�5���ֽ�
					{
						if (0x81==m_recv_com_data[0])
						{
							//����
							//ת�������� 
							int x_coordinate = (unsigned int)covert_coordinate(m_recv_com_data[1],m_recv_com_data[2]);
							int y_coordinate = (unsigned int)covert_coordinate(m_recv_com_data[3],m_recv_com_data[4]);
							//������Ϣ��������
							//::PostMessage(m_parent_handle,m_com_send_message,x_coordinate,y_coordinate);
							::PostMessage(m_parent_handle,m_com_send_message,y_coordinate,x_coordinate);
							//��ʼ��
							memset(m_recv_com_data,0x0,sizeof(m_recv_com_data));
							m_recv_data_len=0;
						}
						else if (0x80==m_recv_com_data[0])
						{
							//̧�𣬳�ʼ��
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

		//ת�����ַ���
		receive_value[0] = recv_value;

		for (int i=0;i<COM_RECEIVE_VALUE_FLAG_MAX_COUNT;i++)
		{
			if (0==strcmp((const char *)com_receive_value[i],(const char *)receive_value))
			{
				//�ҵ���ƥ���������������ʾ��������
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

		//����һ����
		touch_point.x = x;
		touch_point.y = y;

		for (int i=0;i<COM_RECEIVE_VALUE_FLAG_MAX_COUNT;i++)
		{
			if (m_wall_panel_button_rect[i].PtInRect(touch_point))
			{
				//�ҵ���ƥ���������������ʾ��������
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

		//***********************ʯ��ׯ����
		if (m_conn_audio_effect)  //202-09-18 modify ֱ�ӿ�����Ч��  ZHEN 
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
			case COM_SEND_MICROPHONE_VOLUME_UP:       //��˷�������
			case COM_SEND_MICROPHONE_VOLUME_DOWN:     //��˷�������
				{
					sprintf(send_data,"SetMicVolume.%d",microphone_volume);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_MUSIC_VOLUME_UP:            //���ֵ���������
			case COM_SEND_MUSIC_VOLUME_DOWN:          //���ֵ���������
				{
					sprintf(send_data,"SetMusicVolume.%d",music_volume);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_TUNE_UP:                    //��������
			case COM_SEND_TUNE_DOWN:                  //��������
			case COM_SEND_TUNE_STANDARD:              //������׼
				{
					sprintf(send_data,"SetTone.%d",tune);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_AUDIO_EFFECT_STANDARD:      //��׼
				{
					strcpy(send_data,"SetEffectsMode.A");
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_AUDIO_EFFECT_THEATER:       //�糡
				{
					strcpy(send_data,"SetEffectsMode.B");
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_AUDIO_EFFECT_PROFESSIONAL:  //����
				{
					strcpy(send_data,"SetEffectsMode.C");
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_AUDIO_EFFECT_MAGIC:         //ħ��
				{
					strcpy(send_data,"SetEffectsMode.D");
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT_STANDARD:         //�ƹ� ��׼
				{
					sprintf(send_data,"SetLightMode.A-%s",file_number);
					write_com_data_UDP_IP(send_data);
					//2015-7-18 12:04:13---����
// 					sprintf(send_data,"SetLightMode.N-%s",file_number);
// 					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT_BACKGROUND:           //�ƹ� ����
				{
					sprintf(send_data,"SetLightMode.B-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT_STAGE:                //�ƹ� ��̨
				{
					sprintf(send_data,"SetLightMode.C-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT_SCINTILLATION:        //�ƹ� ����
				{
					sprintf(send_data,"SetLightMode.D-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT_CLOSE:                //�ƹ� �ر�
				{
					sprintf(send_data,"SetLightMode.E-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT6:   //�ƹ�6
				{
					sprintf(send_data,"SetLightMode.F-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT7:   //�ƹ�7
				{
					sprintf(send_data,"SetLightMode.G-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT8:   //�ƹ�8
				{
					sprintf(send_data,"SetLightMode.H-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT9:   //�ƹ�9
				{
					sprintf(send_data,"SetLightMode.I-%s",file_number);
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_LIGHT10:   //�ƹ�10
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
			case COM_SEND_PLAYER_PAUSE:     //��ͣ
				{
					strcpy(send_data,"SetPlayer.PAUSE");
					write_com_data_UDP_IP(send_data);
				}
				break;
			case COM_SEND_PLAYER_PLAY:     //����
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

		//��⴮���Ƿ�򿪳ɹ�
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
		case COM_SEND_POWER_ON:             //����
			{
				com_value = config_file.read_string(L"send_value",L"power_on",L"");
			}
			break;
		case COM_SEND_POWER_OFF:            //�ػ�
			{
				com_value = config_file.read_string(L"send_value",L"power_off",L"");
			}
			break;
		case COM_SEND_CLOSE_ROOM:           //�ط�
			{
				com_value = config_file.read_string(L"send_value",L"close_room",L"");
				close_light_time = config_file.read_integer(L"setting",L"close_light_time",0);
				if (close_light_time>0)
				{
					//��ʾҪ��ʱ�ص�
					g_send_com_value = config_file.read_string(L"send_value",L"light_close",L"");
					if (!g_send_com_value.empty())
					{
						//��ʱ��ֻ����һ��
						timeSetEvent(close_light_time*1000,0,send_com_callback,(DWORD)this,TIME_CALLBACK_FUNCTION|TIME_ONESHOT);
					}					
				}
			}
			break;
		case COM_SEND_OPEN_ROOM:            //����
			{
				com_value = config_file.read_string(L"send_value",L"open_room",L"");
			}
			break;
		case COM_SEND_NEXT_SONG:         //��һ��
			{
				com_value = config_file.read_string(L"send_value",L"next_song",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_STANDARD:   //��׼
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_standard",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_THEATER:       //�糡
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_theater",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_PROFESSIONAL:  //����
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_professional",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_MAGIC:         //ħ��
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_magic",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_RESERVE1:     //��ЧԤ��
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_reserve1",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_RESERVE2:     //��ЧԤ��
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_reserve2",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_RESERVE3:     //��ЧԤ��
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_reserve3",L"");
			}
			break;
		case COM_SEND_AUDIO_EFFECT_RESERVE4:     //��ЧԤ��
			{
				com_value = config_file.read_string(L"send_value",L"audio_effect_reserve4",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_STANDARD:      //������Ч��׼
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_standard",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_THEATER:       //������Ч�糡
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_theater",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_PROFESSIONAL:  //������Ч����
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_professional",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_MAGIC:         //������Чħ��
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_magic",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_RESERVE1:      //������ЧԤ��
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_reserve1",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_RESERVE2:      //������ЧԤ��
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_reserve2",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_RESERVE3:      //������ЧԤ��
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_reserve3",L"");
			}
			break;
		case COM_SEND_MUSIC_SOUND_RESERVE4:      //������ЧԤ��
			{
				com_value = config_file.read_string(L"send_value",L"music_sound_reserve4",L"");
			}
			break;
		case COM_SEND_MICROPHONE_VOLUME_UP:      //��˷�������
			{
				com_value = config_file.read_string(L"send_value",L"microphone_volume_up",L"");
			}
			break;
		case COM_SEND_MICROPHONE_VOLUME_DOWN:     //��˷�������
			{
				com_value = config_file.read_string(L"send_value",L"microphone_volume_down",L"");
			}
			break;
		case COM_SEND_TUNE_UP:                    //��������
			{
				com_value = config_file.read_string(L"send_value",L"tune_up",L"");
			}
			break;
		case COM_SEND_TUNE_DOWN:                  //��������
			{
				com_value = config_file.read_string(L"send_value",L"tune_down",L"");
			}
			break;
		case COM_SEND_TUNE_STANDARD:             //������׼
			{
				com_value = config_file.read_string(L"send_value",L"tune_standard",L"");
			}
			break;
		case COM_SEND_LIGHT1:                     //�ƹ�1
			{
				com_value = config_file.read_string(L"send_value",L"light_open1",L"");
			}
			break;
		case COM_SEND_LIGHT2:                     //�ƹ�1
			{
				com_value = config_file.read_string(L"send_value",L"light_open2",L"");
			}
			break;
		case COM_SEND_LIGHT3:                     //�ƹ�1
			{
				com_value = config_file.read_string(L"send_value",L"light_open3",L"");
			}
			break;
		case COM_SEND_LIGHT4:                     //�ƹ�1
			{
				com_value = config_file.read_string(L"send_value",L"light_open4",L"");
			}
			break;
		case COM_SEND_LIGHT5:                     //�ƹ�1
			{
				com_value = config_file.read_string(L"send_value",L"light_open5",L"");
			}
			break;
		case COM_SEND_LIGHT6:                     //�ƹ�1
			{
				com_value = config_file.read_string(L"send_value",L"light_open6",L"");
			}
			break;
		case COM_SEND_LIGHT7:                     //�ƹ�1
			{
				com_value = config_file.read_string(L"send_value",L"light_open7",L"");
			}
			break;
		case COM_SEND_LIGHT8:                     //�ƹ�1
			{
				com_value = config_file.read_string(L"send_value",L"light_open8",L"");
			}
			break;
		case COM_SEND_LIGHT_STANDARD:             //�ƹ� ��׼
			{
				com_value = config_file.read_string(L"send_value",L"light_standard",L"");
			}
			break;
		case COM_SEND_LIGHT_BACKGROUND:           //�ƹ� ����
			{
				com_value = config_file.read_string(L"send_value",L"light_background",L"");
			}
			break;
		case COM_SEND_LIGHT_STAGE:                //�ƹ� ��̨
			{
				com_value = config_file.read_string(L"send_value",L"light_stage",L"");
			}
			break;
		case COM_SEND_LIGHT_SCINTILLATION:        //�ƹ� ����
			{
				com_value = config_file.read_string(L"send_value",L"light_scintillation",L"");
			}
			break;
		case COM_SEND_LIGHT_OPEN:                //�ƹ� ��
			{
				com_value = config_file.read_string(L"send_value",L"light_open",L"");
			}
			break;
		case COM_SEND_LIGHT_CLOSE:               //�ƹ� �ر�
			{
				com_value = config_file.read_string(L"send_value",L"light_close",L"");
			}
			break;
		case COM_SEND_LIGHT_MUTE:               //�ƹ� ����
			{
				com_value = config_file.read_string(L"send_value",L"light_mute",L"");
			}
			break;
		case COM_SEND_LIGHT_PAUSE:               //�ƹ� ��ͣ
			{
				com_value = config_file.read_string(L"send_value",L"light_pause",L"");
			}
			break;
		case COM_SEND_MUSIC_VOLUME_UP:            //���ֵ���������
			{
				com_value = config_file.read_string(L"send_value",L"music_volume_up",L"");
			}
			break;
		case COM_SEND_MUSIC_VOLUME_DOWN:          //���ֵ���������
			{
				com_value = config_file.read_string(L"send_value",L"music_volume_DOWN",L"");
			}
			break;
		case COM_SEND_SCREEN_SWITCH:              //���潻��
			{
				com_value = config_file.read_string(L"send_value",L"tv_screen_switch",L"");
			}
			break;
		case COM_SEND_TV_CHANNEL_UP:              //Ƶ������
			{
				com_value = config_file.read_string(L"send_value",L"tv_channel_up",L"");
			}
			break;
		case COM_SEND_TV_CHANNEL_DOWN:            //Ƶ������
			{
				com_value = config_file.read_string(L"send_value",L"tv_channel_down",L"");
			}
			break;
		case COM_SEND_REQUEST_SERVER:           //�������
			{
				com_value = config_file.read_string(L"send_value",L"request_server",L"");
			}
			break;
		case COM_SEND_CANCEL_SERVER:              //ȡ������
			{
				com_value = config_file.read_string(L"send_value",L"cancel_server",L"");
			}
			break;
		case COM_SEND_CLOSE_SERVICE_LIGHT:        //�رշ����
			{
				com_value = config_file.read_string(L"send_value",L"close_service_light",L"");
			}
			break;
		case COM_SEND_REVERBERATION_DOWN:         //�����
			{
				com_value = config_file.read_string(L"send_value",L"reverberation_down",L"");
			}
			break;
		case COM_SEND_REVERBERATION_UP:           //�����
			{
				com_value = config_file.read_string(L"send_value",L"reverberation_up",L"");
			}
			break;
		case COM_SEND_AIR_CONDITION_STRONG:       //�յ�ǿ
			{
				com_value = config_file.read_string(L"send_value",L"air_condition_strong",L"");
			}
			break;
		case COM_SEND_AIR_CONDITION_MID:          //�յ���
			{
				com_value = config_file.read_string(L"send_value",L"air_condition_mid",L"");
			}
			break;
		case COM_SEND_AIR_CONDITION_WEAK:         //�յ���
			{
				com_value = config_file.read_string(L"send_value",L"air_condition_weak",L"");
			}
			break;
		case COM_SEND_AIR_CONDITION_CLOSE:        //�յ��ر�
			{
				com_value = config_file.read_string(L"send_value",L"air_condition_close",L"");
			}
			break;
		case COM_SEND_DISCHARGE_AIR_FUNCTION:     //�ŷ�
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
#ifdef GUANGXI_AUDIO_EFFECT  //������Ч��
		switch(com_send_flag)
		{
		case COM_SEND_MICROPHONE_VOLUME_UP:       //��˷�������
		case COM_SEND_MICROPHONE_VOLUME_DOWN:     //��˷�������
			{
				sprintf(send_data,"SetMicVolume.%d",microphone_volume);
				write_com_data_UDP_IP(send_data);
			}
			return true;
		case COM_SEND_MUSIC_VOLUME_UP:            //���ֵ���������
		case COM_SEND_MUSIC_VOLUME_DOWN:          //���ֵ���������
			{
				sprintf(send_data,"SetMusicVolume.%d",music_volume);
				write_com_data_UDP_IP(send_data);
			}
			return true;
		case COM_SEND_TUNE_UP:                    //��������
		case COM_SEND_TUNE_DOWN:                  //��������
		case COM_SEND_TUNE_STANDARD:              //������׼
			{
				sprintf(send_data,"SetTone.%d",tune);
				write_com_data_UDP_IP(send_data);
			}
			return true;
		case COM_SEND_AUDIO_EFFECT_STANDARD:      //��׼
			{
				strcpy(send_data,"SetEffectsMode.A");
				write_com_data_UDP_IP(send_data);
			}
			return true;
		case COM_SEND_AUDIO_EFFECT_THEATER:       //�糡
			{
				strcpy(send_data,"SetEffectsMode.B");
				write_com_data_UDP_IP(send_data);
			}
			return true;
		case COM_SEND_AUDIO_EFFECT_PROFESSIONAL:  //����
			{
				strcpy(send_data,"SetEffectsMode.C");
				write_com_data_UDP_IP(send_data);
			}
			return true;
		case COM_SEND_AUDIO_EFFECT_MAGIC:         //ħ��
			{
				strcpy(send_data,"SetEffectsMode.D");
				write_com_data_UDP_IP(send_data);
			}
			return true;
		default:
			break;
		}
#endif
		//������Ҫ���͵�ֵ
		result = parse_com_send_value(com_value.c_str(),com_send_flag,music_volume,microphone_volume,tune);
		if (result)
		{
			//���������������������������ͬʱ�������
			switch(com_send_flag)
			{
			case COM_SEND_TUNE_UP:                //��������
			case COM_SEND_TUNE_DOWN:              //��������
			case COM_SEND_MICROPHONE_VOLUME_DOWN: //�����������
			case COM_SEND_MICROPHONE_VOLUME_UP:   //�����������
			case COM_SEND_MUSIC_VOLUME_DOWN:      //������������
			case COM_SEND_MUSIC_VOLUME_UP:        //������������
				{
					if (adjust_count>1)
					{
						if (adjust_count>=COM_SEND_MAX_GROUP_COUNT)
						{
							adjust_count = COM_SEND_MAX_GROUP_COUNT; 
						}
						//��¼�ܵķ�����
						m_com_send_group_count = adjust_count-1;
						//��һ����ĸ����������������
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
			//���͵�����
			if(m_com_send_group_count>0)
			{
				//����ж��飬��Ҫ������ʱ��������
				m_send_thread_handle = AfxBeginThread(inherit_com::send_com_value_thread,this);
			}
			else
			{
				//ֻ��һ�飬ֱ�ӷ��͵�����
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

		//������������ֵ
		swscanf(rect,L"%d:%d:%d:%d",&left_x,&top_y,&right_x,&bottom_y);
		//��������
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

		//��ʼ��
		memset(value,0x0,sizeof(value));
		for (int i=0;i<COM_SEND_MAX_GROUP_COUNT;i++)
		{
			memset(m_com_send_value[i],0x0,sizeof(m_com_send_value[i]));
			m_com_send_value_len[i]=0;
		}
		m_com_send_group_count = 0;
		//����Ҫ�����Ĵ���ֵ
		_tcscpy(value,com_value);

		for (unsigned int i=0;i<_tcslen(value);i+=5)
		{
			if (0==_tcsncmp(value+i,L"0xYY",4))
			{
				//�����ָ������зָ�
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
				//����ʵ��ֵ
				switch (com_send_flag)
				{
				case COM_SEND_MICROPHONE_VOLUME_UP:      //��˷�������
				case COM_SEND_MICROPHONE_VOLUME_DOWN:     //��˷�������
					{
						m_com_send_value[m_com_send_group_count][char_number] = microphone_volume;
						m_com_send_value_len[m_com_send_group_count]++;
						char_number++;
					}
					break;
				case COM_SEND_TUNE_UP:                    //��������
				case COM_SEND_TUNE_DOWN:                  //��������
				case COM_SEND_TUNE_STANDARD:             //������׼
					{
						m_com_send_value[m_com_send_group_count][char_number] = tune;
						m_com_send_value_len[m_com_send_group_count]++;
						char_number++;
					}
					break;
				case COM_SEND_MUSIC_VOLUME_UP:            //���ֵ���������
				case COM_SEND_MUSIC_VOLUME_DOWN:          //���ֵ���������
					{
						m_com_send_value[m_com_send_group_count][char_number] = music_volume;
						m_com_send_value_len[m_com_send_group_count]++;
						char_number++;
					}
					break;
				case COM_SEND_REVERBERATION_DOWN:         //�����
					break;
				case COM_SEND_REVERBERATION_UP:           //�����
					break;
				default:
					break;
				}

				continue;
			}
			else if (0 == _tcsncmp(value+i,L"0xSS",4)) 
			{
				//��У��
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
			//���ʹ�������
			send_count = write(m_com_send_value[m_com_send_group_count],m_com_send_value_len[m_com_send_group_count]);
			if (m_com_send_group_count<=0)
			{
				//С��0��ʾ�Ѿ�������ϣ������߳�
				break;
			}
			//Ҫ���͵�������һ
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
		//����һ��socket
		SOCKET com_socket = ::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

		//off TIME_WAIT
		struct linger zeroLinger;	
		zeroLinger.l_onoff = 1;	
		zeroLinger.l_linger = 5;

		setsockopt(com_socket,SOL_SOCKET,SO_LINGER,(const char *)&zeroLinger	,sizeof(zeroLinger));

		int m_nSendTimeout = 6000;
		//set send timeout
		setsockopt(com_socket,SOL_SOCKET,SO_SNDTIMEO,(const char *)&m_nSendTimeout,sizeof(m_nSendTimeout));

		// Ҳ�������������bind������һ�����ص�ַ
		// ����ϵͳ�����Զ�����

		// ��дԶ�̵�ַ��Ϣ
		sockaddr_in servAddr; 
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = htons(1983);
		// ע�⣬����Ҫ��д����������TCPServer�������ڻ�����IP��ַ
		// �����ļ����û��������ֱ��ʹ��127.0.0.1����
		servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		//��������
		::sendto(com_socket, (char *)data,strlen(data),0,(sockaddr *)&servAddr,sizeof(sockaddr_in));
		// �ر��׽���
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

		//���ʹ�������
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
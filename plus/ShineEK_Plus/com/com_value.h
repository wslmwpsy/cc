#ifndef _COM_VALUE_H_
#define _COM_VALUE_H_

//���͵����ڵ������ʾ
enum COM_SEND_VALUE_FLAG
{
	COM_SEND_POWER_ON,                   //����
	COM_SEND_POWER_OFF,                  //�ػ�
	COM_SEND_CLOSE_ROOM,                 //�ط�
	COM_SEND_OPEN_ROOM,                  //����
	COM_SEND_NEXT_SONG,                  //��һ��
	COM_SEND_AUDIO_EFFECT_STANDARD,      //��׼
	COM_SEND_AUDIO_EFFECT_THEATER,       //�糡
	COM_SEND_AUDIO_EFFECT_PROFESSIONAL,  //����
	COM_SEND_AUDIO_EFFECT_MAGIC,         //ħ��
	COM_SEND_AUDIO_EFFECT_RESERVE1,      //��ЧԤ��
	COM_SEND_AUDIO_EFFECT_RESERVE2,      //��ЧԤ��
	COM_SEND_AUDIO_EFFECT_RESERVE3,      //��ЧԤ��
	COM_SEND_AUDIO_EFFECT_RESERVE4,      //�Զ�
	COM_SEND_MICROPHONE_VOLUME_UP,       //��˷�������
	COM_SEND_MICROPHONE_VOLUME_DOWN,     //��˷�������
	COM_SEND_TUNE_UP,                    //��������
	COM_SEND_TUNE_DOWN,                  //��������
	COM_SEND_TUNE_STANDARD,              //������׼
	COM_SEND_LIGHT_STANDARD,             //�ƹ� ��׼
	COM_SEND_LIGHT_BACKGROUND,           //�ƹ� ����
	COM_SEND_LIGHT_STAGE,                //�ƹ� ��̨
	COM_SEND_LIGHT_SCINTILLATION,        //�ƹ� ����
	COM_SEND_LIGHT_CLOSE,                //�ƹ� �ر�
	COM_SEND_LIGHT_OPEN,                 //�ƹ� ��
	COM_SEND_LIGHT1,                     //�ƹ�1
	COM_SEND_LIGHT2,                     //�ƹ�2
	COM_SEND_LIGHT3,                     //�ƹ�3
	COM_SEND_LIGHT4,                     //�ƹ�4
	COM_SEND_LIGHT5,                     //�ƹ�5
	COM_SEND_LIGHT6,                     //�ƹ�6
	COM_SEND_LIGHT7,                     //�ƹ�7
	COM_SEND_LIGHT8,                     //�ƹ�8
	COM_SEND_LIGHT9,                     //�ƹ�9
	COM_SEND_LIGHT10,                    //�ƹ�10
	COM_SEND_LIGHT_MUTE,				 //����ʱ�ƹ�
	COM_SEND_LIGHT_PAUSE,				 //��ͣʱ�ƹ�
	COM_SEND_MUSIC_VOLUME_UP,            //���ֵ���������
	COM_SEND_MUSIC_VOLUME_DOWN,          //���ֵ���������
	COM_SEND_SCREEN_SWITCH,              //���潻��
	COM_SEND_TV_CHANNEL_UP,              //Ƶ������
	COM_SEND_TV_CHANNEL_DOWN,            //Ƶ������
	COM_SEND_REQUEST_SERVER,             //�������
	COM_SEND_CANCEL_SERVER,              //ȡ������
	COM_SEND_REVERBERATION_DOWN,         //�����
	COM_SEND_REVERBERATION_UP,           //�����
	COM_SEND_AIR_CONDITION_STRONG,       //�յ�ǿ
	COM_SEND_AIR_CONDITION_MID,          //�յ���
	COM_SEND_AIR_CONDITION_WEAK,         //�յ���
	COM_SEND_AIR_CONDITION_CLOSE,        //�յ��ر�
	COM_SEND_DISCHARGE_AIR_FUNCTION,     //�ŷ�
	COM_SEND_CLOSE_SERVICE_LIGHT,        //�رշ����
	COM_SEND_PLAYER_PLAY,                //����
	COM_SEND_PLAYER_PAUSE,               //��ͣ

	COM_SEND_MUSIC_SOUND_STANDARD,      //������Ч��׼
	COM_SEND_MUSIC_SOUND_THEATER,       //������Ч�糡
	COM_SEND_MUSIC_SOUND_PROFESSIONAL,  //������Ч����
	COM_SEND_MUSIC_SOUND_MAGIC,         //������Чħ��
	COM_SEND_MUSIC_SOUND_RESERVE1,      //������ЧԤ��
	COM_SEND_MUSIC_SOUND_RESERVE2,      //������ЧԤ��
	COM_SEND_MUSIC_SOUND_RESERVE3,      //������ЧԤ��
	COM_SEND_MUSIC_SOUND_RESERVE4,      //������ЧԤ��
};

//���մ��ڵ������ʾ,ͬ���޸� TCHAR com_receive_key_name[][]����
enum COM_RECEIVE_VALUE_FLAG
{
	COM_RECEIVE_REQUEST_SERVICE,        //�������
	COM_RECEIVE_CANCEL_SERVICE,         //ȡ������
	COM_RECEIVE_MICROPHONE_VOLUME_UP,   //��˷�������
	COM_RECEIVE_MICROPHONE_VOLUME_DOWN, //��˷�������
	COM_RECEIVE_MUSIC_VOLUME_UP,        //���ֵ�������
	COM_RECEIVE_MUSIC_VOLUME_DOWN,      //���ֵ�������
	COM_RECEIVE_TUNE_UP,                //������
	COM_RECEIVE_TUNE_DOWN,              //������
	COM_RECEIVE_TUNE_STANDARD,          //��׼��
	COM_RECEIVE_NEXT_SONG,              //��һ��
	COM_RECEIVE_REPLAY_SONG,            //�س�
	COM_RECEIVE_KARAOKE_ACCOMPANY,      //ԭ�鳪
	COM_RECEIVE_KARAOKE_TRACK,          //ԭ��
	COM_RECEIVE_ACCOMPANY_TRACK,        //�鳪
	COM_RECEIVE_PLAY_PAUSE,             //������ͣ
	COM_RECEIVE_PLAY,                   //����
	COM_RECEIVE_PAUSE,                  //��ͣ
	COM_RECEIVE_SONG_MUTE,              //����/ȡ������
	COM_RECEIVE_SONG_MUTE_BUTTON,       //����
	COM_RECEIVE_SONG_UNMUTE_BUTTON,     //ȡ������
	COM_RECEIVE_RECORDER,               //¼��
	COM_RECEIVE_ATMOSPHERE_APPLAUSE,    //����
	COM_RECEIVE_ATMOSPHERE_CHEER,       //����
	COM_RECEIVE_ATMOSPHERE_OUTCRY,      //����
	COM_RECEIVE_ATMOSPHERE_WHISTLE,     //��
	COM_RECEIVE_LIGHT1,                 //�ƹ�1
	COM_RECEIVE_LIGHT2,                 //�ƹ�2
	COM_RECEIVE_LIGHT3,                 //�ƹ�3
	COM_RECEIVE_LIGHT4,                 //�ƹ�4
	COM_RECEIVE_LIGHT5,                 //�ƹ�5
	COM_RECEIVE_LIGHT6,                 //�ƹ�6
	COM_RECEIVE_LIGHT7,                 //�ƹ�7
	COM_RECEIVE_LIGHT8,                 //�ƹ�8
	COM_RECEIVE_LIGHT9,                 //�ƹ�9
	COM_RECEIVE_LIGHT10,                //�ƹ�10
	COM_RECEIVE_LIGHT_OPEN,             //�ƹ⿪
	COM_RECEIVE_LIGHT_CLOSE,            //�ƹ�ر�
	COM_RECEIVE_AUDIO_EFFECT_STANDARD,      //��׼
	COM_RECEIVE_AUDIO_EFFECT_THEATER,       //�糡
	COM_RECEIVE_AUDIO_EFFECT_PROFESSIONAL,  //����
	COM_RECEIVE_AUDIO_EFFECT_MAGIC,         //ħ��
	COM_RECEIVE_AUDIO_EFFECT_RESERVE1,      //��ЧԤ��
	COM_RECEIVE_AUDIO_EFFECT_RESERVE2,      //��ЧԤ��
	COM_RECEIVE_AUDIO_EFFECT_RESERVE3,      //��ЧԤ��
	COM_RECEIVE_AUDIO_EFFECT_RESERVE4,      //��ЧԤ��
	COM_RECEIVE_AUDIO_EFFECT_CHANGE,        //��Ч�ı�
	COM_RECEIVE_ENJOY_SONG,                 //����
	COM_RECEIVE_AIR_CONDITION_STRONG,       //�յ�ǿ
	COM_RECEIVE_AIR_CONDITION_MID,          //�յ���
	COM_RECEIVE_AIR_CONDITION_WEAK,         //�յ���
	COM_RECEIVE_AIR_CONDITION_CLOSE,        //�յ��ر�
	COM_RECEIVE_DISCHARGE_AIR_FUNCTION,     //�ŷ�
	COM_RECEIVE_SERVER_LIGHT_STATE,         //�����״̬
	COM_RECEIVE_LIGHT11,                 //�ƹ�9
	COM_RECEIVE_LIGHT12,                //�ƹ�10

	COM_RECEIVE_ATMOSPHERE_HAOZAN,	//����
	COM_RECEIVE_ATMOSPHERE_SHIHUA, //ʯ��
	COM_RECEIVE_ATMOSPHERE_XIEHUA, //�׻�
	COM_RECEIVE_ATMOSPHERE_TUXIE, //��Ѫ
	COM_RECEIVE_ATMOSPHERE_FEIWEN, //����
	COM_RECEIVE_ATMOSPHERE_XINSUI, //����
	COM_RECEIVE_ATMOSPHERE_HAIXIU, //����
	COM_RECEIVE_ATMOSPHERE_ZADAN, //�ҵ�

	COM_RECEIVE_MUSIC_SOUND_STANDARD,      //������Ч��׼
	COM_RECEIVE_MUSIC_SOUND_THEATER,       //������Ч�糡
	COM_RECEIVE_MUSIC_SOUND_PROFESSIONAL,  //������Ч����
	COM_RECEIVE_MUSIC_SOUND_MAGIC,         //������Чħ��
	COM_RECEIVE_MUSIC_SOUND_RESERVE1,      //������ЧԤ��
	COM_RECEIVE_MUSIC_SOUND_RESERVE2,      //������ЧԤ��
	COM_RECEIVE_MUSIC_SOUND_RESERVE3,      //������ЧԤ��
	COM_RECEIVE_MUSIC_SOUND_RESERVE4,      //������ЧԤ��
	COM_RECEIVE_MUSIC_SOUND_CHANGE,        //������Ч�ı�

	COM_RECEIVE_VALUE_FLAG_MAX_COUNT,   //������������
};

#endif
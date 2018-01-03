#pragma once

//������
#define LOCK_OK                   0        //�ɹ�
#define LOCK_CREATE_SOCK_FAIL     11       //����socketʧ��
#define LOCK_NO_SERVER_IP         12       //���ղ���������IP
#define LOCK_CONNECT_SERVER_FAIL  13       //���ӷ�����ʧ��
#define LOCK_SEND_FAIL            14       //��������ʧ��
#define LOCK_RECV_FAIL            15       //��������ʧ��
#define LOCK_RECV_HEART_BEAT_FAIL 16       //���շ���������ʧ��
#define LOCK_PARA_FLAG_ERROR      18       //����Ĳ���flag����

#define LOCK_MODULE_NUM_ERR         50      //ģ���Ų����ڻ����
#define LOCK_MODULE_COUNT_LESS      51      //ģ���������
#define LOCK_OPEN_FAIL              52      //��������ʧ�ܣ����Ҳ���������
#define LOCK_USER_NUMBER_FAIL       53      //�������ڿͻ����ʧ��
#define LOCK_NUMBER_SIGN_NO_EXIST   54      //�����ǩ���ļ�������
#define LOCK_NUMBER_SIGN_ERR        55      //�����ǩ���ļ�����
#define LOCK_FUN_SIGN_NO_EXIST      56      //����ǩ���ļ�������
#define LOCK_FUN_SIGN_ERR           57      //����ǩ���ļ�����
#define LOCK_TIME_EXPIRED           58      //����������

#define LOCK_UNKNOWN_ERR          111       //δ֪����

//�û���Ϣ
typedef struct OUTLETS_DATA_STRU
{
	char UserPlaceName[40]; 						//�û���������
	char UserDisName[40];							//�û���ʾ����
	char UserAddress[80];							//�û���ַ
	char userReservePhone[40];						//�û������绰
	char UserCity[16];								//�û���������	
}OUTLETS_DATA;

//��������Ϣ
typedef struct AGENT_DATA_STRU
{
	char AgentName[16];							//����������
	char AgentAddress[80];							//�����̵�ַ
	char AgentPhone[16];							//�����̵绰
}AGENT_DATA;

//��������Ϣ
typedef struct ISP_DATA_STRU
{
	char DevelopersName[25];						//����������
	char DevelopersPhone[16];						//�����̵绰
	char DevelopersAddress[80];					//�����̵�ַ
}ISP_DATA;


/*******************************************************
�������ƣ�lock_init
����˵������ʼ��������Ϣ�Լ��������շ��������ݵ��߳�
������
    void
����ֵ��
   0 - �ɹ�
   !0 - ʧ��
********************************************************/
extern "C" int lock_init(void);

/*******************************************************
�������ƣ�lock_connect_server
����˵�������ӷ����������������ӡ������ʼ��֮��3��������
������
    void
����ֵ��
   0 - �ɹ�
   !0 - ʧ��
********************************************************/
extern "C" int lock_connect_server(void);

/*******************************************************
�������ƣ�lock_login_check
����˵��������ģ���Ƿ���ã�ͬʱ����ʣ��ʱ��
������
    module_number[in]:ģ����
	valid_time[out]:����ʣ��ʱ�䣬��λ����
����ֵ��
   0 - �ɹ�
   !0 - ʧ��
********************************************************/
extern "C" int lock_login_check(IN int module_number, OUT long *valid_time);

/*******************************************************
�������ƣ�lock_get_data
����˵�����õ��ͻ��������̡������̡��������ܡ����ܸ�ʽ����Ϣ
������
    flag[in]:��Ҫ��ȡ����Ϣ��ʾ 
	        0----��ȡ�ͻ���Ϣ
	        1----��ȡ��������Ϣ
	        2----��ȡ��������Ϣ
	        3----��ȡ����������Ϣ
	        4----��ȡ����ģʽ
	        5----��ȡϵͳ����
			6----��ȡԤ������
			7----��ȡ���Ŀͻ����
	buffer[out]:���ڽ������ݵ��ڴ��ַ���ṹ�巽ʽ
	buf_size[in]���������ݵ��ڴ��ֽ���
����ֵ��
   0 - �ɹ�
   !0 - ʧ��
********************************************************/
extern "C" int lock_get_data(IN int flag, OUT void *buffer, IN int buf_size);

/*******************************************************
�������ƣ�lock_common_check
����˵�������ڼ������Ƿ����
������
    void
����ֵ��
   0 - �ɹ�
   !0 - ʧ��
********************************************************/
extern "C" int lock_common_check(void);

/*******************************************************
�������ƣ�lock_uninit
����˵��������ʼ������ֹ�̺߳��ͷ���Դ
������
    void
����ֵ��
   0 - �ɹ�
   !0 - ʧ��
********************************************************/
extern "C" int lock_uninit(void);

/*******************************************************
�������ƣ�lock_get_server_ip
����˵�����õ�������IP
������
    server_ip��������IP
	size�������ڴ��С
����ֵ��
   0 - �ɹ�
   !0 - ʧ��
********************************************************/
extern "C" int lock_get_server_ip(char *server_ip, int size);


//��Ȩ���ϵͳ�������ܿ��� - AidFun
#define AF_MOBILE_VOD		   	0x00000001 				//�ƶ���蹦��
#define AF_LIVE_SCORE         	0x00000002 				//�ݳ����ֹ���
#define AF_LEADSING_AP         	0x00000004 				//�������๦��
#define AF_INTEGRATE_WEICO    	0x00000008 				//����΢������
#define AF_INTERACTIVE_GAMES  	0x00000010 				//������Ϸ����
#define AF_VIDEO_INTERACTIVE  	0x00000020 				//��Ƶ��������
#define AF_VOD         			0x00000040 				//Ӱ�ӵ㲥����
#define AF_EM_DRINK         	0x00000080  			//��Ƕ��ˮ����
#define AF_ROOM_CONTROL      	0x00000100 				//���ط�����
#define RF_1					0x00000200              //10��ս���
#define RF_2					0x00000400              //�������
#define RF_3					0x00000800
#define RF_4					0x00001000
#define RF_5					0x00002000
#define RF_6					0x00004000
#define RF_7					0x00008000
#define RF_8					0x00010000
#define RF_9					0x00020000
#define RF_10					0x00040000
#define RF_11					0x00080000
#define RF_12					0x00100000
#define RF_13					0x00200000
#define RF_14					0x00400000
#define RF_15					0x00800000
#define RF_16					0x01000000
#define RF_17					0x02000000
#define RF_18					0x04000000
#define RF_19					0x08000000
#define RF_20					0x10000000
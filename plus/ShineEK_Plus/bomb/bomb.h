// bomb.h
//

#ifndef __BOMB_H__
#define __BOMB_H__

//////////////////////////////////////////////////////////////////////////
// ����
const int BOMB_NONE  = 0;      //û��ը��
const int BOMB_SONG  = 1;      //����ը����Ƶ����ͣ,����
const int BOMB_STOP_DOG  = 2;  //�޸ļ��ܹ���ʱ�䣬�������

const int BOMB_MAX_TYPE = 3;  //ը��������

class bomb
{
public:
	bomb();
	~bomb();

	/*
	���ܣ���װ����
	������
	    bomb_type�����׵�����
		allow_broadcast���Ƿ�㲥��ȥ
	����ֵ��
	   true:�ɹ�
	   false��ʧ��
	*/
	bool embed_bomb(int bomb_type,bool allow_broadcast);

	/*
	���ܣ����ҵ���
	������
	   void
   ����ֵ��
       ���׵�����
	*/
	int check_bomb(void);

	/*
	���ܣ��Ƴ�ը������
	������
	   void
   ����ֵ��
       true���ɹ�
	   falseʧ��
	*/
	bool bomb_out(void);

	/*
	���ܣ��㲥ը������
	������
		bomb_type��ը������
	����ֵ��
		void
	*/
	void broadcast(int bomb_type);

	/*
	���ܣ��õ�ը��������
	������
	    void
	����ֵ��
	    ը������
	*/
	int get_bomb_type(void);

	/*
	���ܣ�������֤��
	������
	   code����֤��
   ����ֵ��
       true���ɹ�
	   flase��ʧ��
	*/
	bool make_authentication_code(TCHAR *code);

	/*
	���ܣ�������Կ
	������
	   authentication_code����֤��
	   code1����һ����Կ
	   code2���ڶ�����Կ
   ����ֵ��
       true���ɹ�
	   false��ʧ��
	*/
	bool make_bomb_code(TCHAR *authentication_code,TCHAR *code1,TCHAR *code2);

private:
	/*
	���ܣ���ȡ��д��ע���ը��
	������
		operate:������1����ȡ 2��д 3�����ը��
		bomp_type��ը������
	����ֵ��
		ը������
	*/
	int set_reg_bomb(int operate, int bomp_type);

	/*
	���ܣ���ը��д�뵽�ļ���
	������
		bomb_type��ը������
	����ֵ��
		true;�ɹ�
		false��ʧ��
	*/
	bool write_file_bomb(int bomb_type);

	//��������ը����Ϣ���߳�
	static DWORD WINAPI start_thread(void* pParam);
	void bomb_thread(void);

	int m_bomb_type;	         // ���ױ�־
	TCHAR m_bomb_file_path[256]; // ����׵��ļ�
	bool m_thread_run;           //�߳����б�־
	HANDLE m_thread_event_handle;//�¼����
};

#endif //__BOMB_H__

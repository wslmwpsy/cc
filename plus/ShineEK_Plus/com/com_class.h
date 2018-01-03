/*
���ڻ�����⣨WIN32��	ver 0.1

������ �� BC++ 5; C++ BUILDER 4, 5, 6, X; VC++ 5, 6; VC.NET;  GCC;

class   _base_com : ����� �������ڽӿ�;
class   _aync_com : ͬ��I/O ������;
class   _sync_com : �첽I/O ������;
class _thread_com :	�첽I/O �����������߳� ��ת��������Ϣ ������(�ɼ̳��麯��on_receive���ڶ�����)��

copyright(c) 2004.8 llbird wushaojian@21cn.com
*/

#ifndef	_COM_CLASS_H_
#define _COM_CLASS_H_

#pragma warning(disable: 4530)
#pragma warning(disable: 4786)
#pragma warning(disable: 4800 4018)

#include <cassert>
#include <strstream>
#include <algorithm>
#include <exception>
#include <iomanip>
using namespace std;

#include <windows.h>

#pragma warning(disable: 4018)

class _base_com	  //����� �������ڽӿ�
{
protected:

	volatile int _port;	 //���ں�
	volatile HANDLE _com_handle;//���ھ��
	DCB _dcb;			  //�����ʣ�ֹͣλ����
	int _in_buf, _out_buf; // ������
	COMMTIMEOUTS _co;	 //	��ʱʱ��
	//�麯��,���ڲ�ͬ��ʽ�Ĵ��ڴ�
	virtual bool open_port() = 0;

	void init()	//��ʼ��
	{
		memset(&_dcb, 0, sizeof(_dcb));
		_dcb.DCBlength = sizeof(_dcb);

		_com_handle = INVALID_HANDLE_VALUE;

		_in_buf = _out_buf = 8192;

		memset(&_co, 0, sizeof(_co));
		_co.ReadIntervalTimeout = 0xFFFFFFFF;
		_co.ReadTotalTimeoutMultiplier = 0;
		_co.ReadTotalTimeoutConstant = 0;
		_co.WriteTotalTimeoutMultiplier = 0;
		_co.WriteTotalTimeoutConstant = 5000;
	}

public:
	_base_com()
	{
		init();	
	}
	virtual ~_base_com()
	{
		close();				  
	}
	/*������������*/
	//���ô��ڲ����������ʣ�ֹͣλ����
	inline bool set_para() 
	{
		return is_open() ? SetCommState(_com_handle, &_dcb) : false;
	}
	//�����öԻ���
	bool config_dialog()  
	{
		if(is_open())
		{
			COMMCONFIG cf;
			memset(&cf, 0, sizeof(cf));
			cf.dwSize = sizeof(cf);
			cf.wVersion = 1;

			TCHAR com_str[10];
			swprintf(com_str,L"COM%d",_port);

			if(CommConfigDialog(com_str, NULL, &cf))
			{
				 memcpy(&_dcb, &cf.dcb, sizeof(DCB));
				 return SetCommState(_com_handle, &_dcb);
			}
		}
		return false;
	}
	//֧�������ַ��� "9600, 8, n, 1"
	bool set_dcb(TCHAR *set_str)	
	{
		return bool(BuildCommDCB(set_str, &_dcb));
	}
	//�������ýṹ���ڲ����������ʣ�ֹͣλ
	bool set_dcb(int BaudRate, int ByteSize = 8, int Parity = NOPARITY, int StopBits = ONESTOPBIT)
	{
		_dcb.BaudRate = BaudRate;
		_dcb.ByteSize = ByteSize;
		_dcb.Parity   = Parity;
		_dcb.StopBits = StopBits;
		return true;
	}
	//���û�������С
	inline bool set_buf(int in_buf, int out_buf)
	{
		return is_open() ? SetupComm(_com_handle, in_buf, out_buf) : false;
	}
	//�򿪴��� ȱʡ 9600, 8, n, 1
	inline bool open(int port)
	{
		if(port < 1 || port > 1024)
			return false;

		set_dcb(9600);
		_port = port;

		return open_port();
	}
	//�򿪴��� ȱʡ baud_rate, 8, n, 1
	inline bool open(int port, int baud_rate)
	{
		if(port < 1 || port > 1024)
			return false;

		set_dcb(baud_rate);
		_port = port;

		return open_port();
	}
	//�򿪴���
	inline bool open(int port,const TCHAR *set_str)
	{
		if(port < 1 || port > 1024)
			return false;

		if(!BuildCommDCB(set_str, &_dcb))
			return false;

		_port = port;

		return open_port();
	}
	//�رմ���
	inline virtual void close()
	{
		if(is_open())		
		{
			CloseHandle(_com_handle);
			_com_handle = INVALID_HANDLE_VALUE;
		}
	}
	//�жϴ����ǻ��
	inline bool is_open()
	{
		return _com_handle != INVALID_HANDLE_VALUE;
	}
	//��ô��ھ��
	HANDLE get_handle()
	{
		return _com_handle;
	}
};

class _sync_com	: public _base_com
{
protected:
	//�򿪴���
	virtual bool open_port()
	{
		if(is_open())
			close();

		TCHAR com_str[10];
		swprintf(com_str,L"COM%d",_port);

		_com_handle = CreateFile(
			com_str,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL ,	
			NULL
			);
		//assert(is_open());
		if(!is_open())//��⴮���Ƿ�ɹ���
			return false;
		
		BOOL ret; 
		ret = SetupComm(_com_handle, _in_buf, _out_buf);	//�����Ƽ�������
		//assert(ret);
		ret &= SetCommState(_com_handle, &_dcb);	//���ô��ڲ����������ʣ�ֹͣλ����
		//assert(ret);
		ret &= SetCommTimeouts(_com_handle, &_co);	//���ó�ʱʱ��
		//assert(ret);
		ret &= PurgeComm(_com_handle, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR );	//��մ��ڻ�����
		//assert(ret);
		if(!ret)
		{
			close();
			return false;
		}

		return true;
	}

public:

	_sync_com()
	{
		_co.ReadTotalTimeoutConstant = 5000;
	}
	//ͬ����
	int read(unsigned char *buf, int buf_len)
	{
		if(!is_open())
			return 0;

		buf[0] = '\0';
		
		COMSTAT  stat;
		DWORD error;

		if(ClearCommError(_com_handle, &error, &stat) && error > 0)	//�������
		{
			PurgeComm(_com_handle, PURGE_RXABORT | PURGE_RXCLEAR); /*������뻺����*/
			return 0;
		}
		 
		unsigned long r_len = 0;

		buf_len = min(buf_len - 1, (int)stat.cbInQue);
		if(!ReadFile(_com_handle, buf, buf_len, &r_len, NULL))
				r_len = 0;
		buf[r_len] = '\0';

		return r_len;
	}
	//ͬ��д
	int write(unsigned char *buf, int buf_len)
	{
		if(!is_open() || !buf)
			return 0;
		
		DWORD    error;
		if(ClearCommError(_com_handle, &error, NULL) && error > 0)	//�������
			PurgeComm(_com_handle, PURGE_TXABORT | PURGE_TXCLEAR);

		unsigned long w_len = 0;
		if(!WriteFile(_com_handle, buf, buf_len, &w_len, NULL))
			w_len = 0;

		return w_len;
	}
	//ͬ��д
	inline int write(unsigned char *buf)
	{
		//assert(buf);
		return write(buf, (int)strlen((const char *)buf));
	}
	//ͬ��д, ֧�ֲ������͵������
	template<typename T>
	_sync_com& operator << (T x)
	{
		strstream s;

		s << x;
		write(s.str(), s.pcount());

		return *this;
	}
};

class _asyn_com	: public _base_com
{
protected:

	OVERLAPPED _ro, _wo; //	�ص�I/O

	virtual bool open_port()
	{
		if(is_open())
			close();

		TCHAR com_str[10];
		swprintf(com_str,L"COM%d",_port);

		_com_handle = CreateFile(
			com_str,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,	//�ص�I/O
			NULL
			);
		//assert(is_open());
		if(!is_open())//��⴮���Ƿ�ɹ���
			return false;
		
		BOOL ret; 
		ret = SetupComm(_com_handle, _in_buf, _out_buf);	//�����Ƽ�������
		//assert(ret);
		ret = SetCommState(_com_handle, &_dcb);	//���ô��ڲ����������ʣ�ֹͣλ����
		//assert(ret);
		ret = SetCommTimeouts(_com_handle, &_co);	//���ó�ʱʱ��
		//assert(ret);
		ret = PurgeComm(_com_handle, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR );	//��մ��ڻ�����
		//assert(ret);

		return true;
	}

public:

	_asyn_com()
	{
		memset(&_ro, 0, sizeof(_ro));
		memset(&_wo, 0, sizeof(_wo));

		_ro.hEvent = CreateEvent(NULL, true, false, NULL);
		//assert(_ro.hEvent != INVALID_HANDLE_VALUE); 
		
		_wo.hEvent = CreateEvent(NULL, true, false, NULL);
		//assert(_wo.hEvent != INVALID_HANDLE_VALUE);	
	}
	virtual ~_asyn_com()
	{
		close();

		if(_ro.hEvent != INVALID_HANDLE_VALUE)
			CloseHandle(_ro.hEvent);

		if(_wo.hEvent != INVALID_HANDLE_VALUE)
			CloseHandle(_wo.hEvent);
	}
	//�첽��
	int read(unsigned char *buf, int buf_len)
	{
		if(!is_open())
			return 0;

		buf[0] = '\0';

		COMSTAT  stat;
		DWORD error;

		if(ClearCommError(_com_handle, &error, &stat) && error > 0)	//�������
		{
			PurgeComm(_com_handle, PURGE_RXABORT | PURGE_RXCLEAR); /*������뻺����*/
			return 0;
		}

		if(!stat.cbInQue)// ������������
			return 0;

		unsigned long r_len = 0;

		buf_len = min((int)(buf_len - 1), (int)stat.cbInQue);

		if(!ReadFile(_com_handle, buf, buf_len, &r_len, &_ro)) //2000 �� ReadFile ʼ�շ��� True
		{
			if(GetLastError() == ERROR_IO_PENDING) // �����첽I/O
			{
				if(!GetOverlappedResult(_com_handle, &_ro, &r_len, false))
				{
					if(GetLastError() != ERROR_IO_INCOMPLETE)//��������
							r_len = 0;
				}
			}
			else
				r_len = 0;
		}
			
		buf[r_len] = '\0';
		return r_len;
	}
	//�첽д
	int write(unsigned char *buf, int buf_len)
	{
		if(!is_open())
			return 0;

		//assert(buf);

		DWORD    error;
		if(ClearCommError(_com_handle, &error, NULL) && error > 0)	//�������
			PurgeComm(_com_handle, PURGE_TXABORT | PURGE_TXCLEAR);	

		unsigned long w_len = 0, o_len = 0;
		if(!WriteFile(_com_handle, buf, buf_len, &w_len, &_wo))
			if(GetLastError() != ERROR_IO_PENDING)
				w_len = 0;

		return w_len;
	}
	//�첽д
	inline int write(unsigned char *buf)
	{
		//assert(buf);
		return write(buf, (int)strlen((const char *)buf));
	}
	//�첽д, ֧�ֲ������͵������
	template<typename T>
	_asyn_com& operator << (T x)
	{
		strstream s;

		s << x ;
		write(s.str(), s.pcount());

		return *this;
	}
};

//�����ܵ������͵����ڵ���Ϣ
#define ON_COM_RECEIVE WM_USER + 618	 //	 WPARAM �˿ں�

class _thread_com : public _asyn_com
{
protected:
	volatile HANDLE _thread_handle;	//�����߳�
	volatile HWND _notify_hwnd; // ֪ͨ����
	volatile long _notify_num;//���ܶ����ֽ�(>_notify_num)����֪ͨ��Ϣ
	volatile bool _run_flag; //�߳�����ѭ����־

	OVERLAPPED _wait_o; //WaitCommEvent use

	//�߳��յ���Ϣ�Զ�����, �細�ھ����Ч, �ͳ���Ϣ, �������ڱ��
	virtual void on_receive()
	{
		if(_notify_hwnd)
			PostMessage(_notify_hwnd, ON_COM_RECEIVE, WPARAM(_port), LPARAM(0));
	}
	//�򿪴���,ͬʱ�򿪼����߳�
	virtual bool open_port()
	{
		if(_asyn_com::open_port())
		{
			_run_flag = true; 
			DWORD id;
			_thread_handle = CreateThread(NULL, 0, com_thread, this, 0, &id); //�����߳�
			//assert(_thread_handle);
			if(!_thread_handle)
			{
				CloseHandle(_com_handle);
				_com_handle = INVALID_HANDLE_VALUE;
			}
			else
				return true;
		}
		return false;
	}

public:
	_thread_com()
	{
		_notify_num = 0;
		_notify_hwnd = NULL;
		_thread_handle = NULL;

		memset(&_wait_o, 0, sizeof(_wait_o));
		_wait_o.hEvent = CreateEvent(NULL, true, false, NULL);
		//assert(_wait_o.hEvent != INVALID_HANDLE_VALUE);	
	}
	~_thread_com()
	{
		close();

		if(_wait_o.hEvent != INVALID_HANDLE_VALUE)
			CloseHandle(_wait_o.hEvent);
	}
	//�趨����֪ͨ, �����ַ���Сֵ	 Ĭ�� 0
	void set_notify_num(int num)
	{
		_notify_num = num;
	}
	//����Ϣ�Ĵ��ھ��
	inline void set_hwnd(HWND hWnd)
	{
		_notify_hwnd = hWnd;
	}
	//�ر��̼߳�����
	virtual void close()
	{
		if(is_open())		
		{
			_run_flag = false;
			SetCommMask(_com_handle, 0);
			ResetEvent(_wait_o.hEvent);

			if(WaitForSingleObject(_thread_handle, 100) != WAIT_OBJECT_0)
				TerminateThread(_thread_handle, 0);

			CloseHandle(_com_handle);
			CloseHandle(_thread_handle);

			_thread_handle = NULL;
			_com_handle = INVALID_HANDLE_VALUE;
		}
	}
	/*�����߳̿���*/
	//����߳̾��
	HANDLE get_thread()
	{
		return _thread_handle;
	}
	//��ͣ�����߳�
	bool suspend()
	{
		return _thread_handle != NULL ? SuspendThread(_thread_handle) != 0xFFFFFFFF : false;
	}
	//�ָ������߳�
	bool resume()
	{
		return _thread_handle != NULL ? ResumeThread(_thread_handle) != 0xFFFFFFFF : false;
	}

private:
	//�����߳�
	static DWORD WINAPI com_thread(LPVOID para)
	{
		_thread_com *pcom = (_thread_com *)para;	
		

		if(!SetCommMask(pcom->_com_handle, EV_RXCHAR | EV_ERR))
			return 0;

		COMSTAT  stat;
		DWORD error;

		for(DWORD length, mask = 0; pcom->_run_flag && pcom->is_open(); mask = 0)
		{
			if(!WaitCommEvent(pcom->_com_handle, &mask, &pcom->_wait_o))
			{
				if(GetLastError() == ERROR_IO_PENDING)
				{
					GetOverlappedResult(pcom->_com_handle, &pcom->_wait_o, &length, true);
				}
			}

			if(mask & EV_ERR) // == EV_ERR
				ClearCommError(pcom->_com_handle, &error, &stat);

			if(mask & EV_RXCHAR) // == EV_RXCHAR
			{
				ClearCommError(pcom->_com_handle, &error, &stat);
				if(stat.cbInQue > pcom->_notify_num)
					pcom->on_receive();
			}
		}

		return 0;
	}
	
};

#endif _COM_CLASS_H_

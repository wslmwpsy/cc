
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef WIN32


#ifdef CCDDT_API
#else
#define CCDDT_API // extern "C" _declspec(dllimport) 
#endif
#else
#define	CCDDT_API  
#define	__stdcall 
#endif

#if !defined(_CCDDT_H_)
#define	_CCDDT_H_

#pragma pack( 1 )
#include <time.h>


typedef struct	pwhead
{
	char proto_id[4] ;
	short version ;
	short command ;
	unsigned long packet_len ;
}PWHEAD;



typedef struct pwktvstate
{
	unsigned char auth;
	char  notice[256];
}PWKTVSTATE;



typedef struct pwktvmsg
{
	char songid[20];
	char songname[128];
	char roomid[32];
	char demandtime[20];
	unsigned long playtime;
	unsigned char songtype;
}PWKTVMSG;


typedef struct intervaltime
{
	unsigned long interlen;
}INTERVALTIME;


typedef struct forbidsong
{
	char songid[20];
	char forbidate[12];
}FORBIDSONG;


typedef struct pwnewsonginfo
{
	char name[128];			// ��Ŀ����
	char singername[128];	// �ݳ���
	char language[64];		// ����
	char type[64];			// ����
}PWNEWSONGINFO;

typedef struct pwnewsongid
{
	char id[20];
}PWNEWSONGID;

typedef struct pwtimeverify
{
	time_t ntime;
}PWTIMEVERIFY;

typedef struct ccddt
{
	char aip[32]; // Aǰ�û�IP
	char bip[32]; // Bǰ�û�IP
	int  flag;   // ͨ�ż��ܱ�־

	int  conntimeout;
/*	char certfile[256];  //�ͻ���֤���ļ�·��  client.pem
	char calist[256];    //֤�����ļ�·��  root.pem
*/
}CCDDT;


typedef struct pwrecorderinfo
{
	char songid[20];
	char songname[128];
	char roomid[32];
	char demandtime[20];
	unsigned long playtime;
	unsigned char songtype;
	int price;
}PWRECORDERINFO;


typedef struct pwdetailsearch
{
	char startime[20];
	char endtime[20];
	char roomid[32];
}PWDETAILSEARCH;


#pragma pack()





//******************************************************************//
/*ͨ�Žṹ��ʼ��

		��������struct ccddt *ccddtinit(  char *aip , char *bip )
		
		  ����˵����
		  Char *aip      ��һǰ�û���ip   ��ǰ�û�
		  Char *bip      �ڶ�ǰ�û���ip	  ��ǰ�û�
		  int timeout    ����SSL��������ʱ�ĳ�ʱʱ�䣬ȴʡֵΪ3�� �����÷�Χ�� 2,3,4��
			����ֵ��NULL           ��ʼ��ʧ��
			Struct ccddt *     �ṹ��ָ��
		 ע�⣺������ÿ������ֻ�ܳ�ʼ��һ�Σ������ʼ����ο��ܻ���������쳣
*/

//*******************************************************************//
CCDDT_API struct ccddt * __stdcall  ccddtinit(  char *aip , char *bip  , int timeout );

//******************************************************************//
/*
ͨ�Žṹ�ر�

		��������void ccddtclose( struct ccddt *vodclient )
		����ֵ����
//******************************************************************/

CCDDT_API void __stdcall  ccddtclose( struct ccddt *vodclient );
//******************************************************************//
/*
��ȡǰ�û�״̬

		��������int recvccddtstate( struct ccddt *vodclient )
		
		  ����ֵ��
		  -3 ��ʼ���ͻ���֤���쳣
		  -2 ��̨ǰ�û����쳣
		  -1 ��ǰ�û��쳣
		  0  ��ǰ�û��쳣
		  1  ǰ�û�������
//*****************************************************************/
CCDDT_API int __stdcall recvccddtstate( struct ccddt *vodclient );

//*****************************************************************//
/*��ȡKTV��Ȩ״̬

  ״̬����
  ��������struct ktvstate *recvktvstate( struct ccddt *vodclient )
  
	����˵����
	
	  ����ֵ��
	  NULL ǰ�û��쳣
	  �ṹָ�� �����ɹ�
//*****************************************************************/
CCDDT_API struct pwktvstate  * __stdcall recvktvstate( struct ccddt *vodclient );

//*****************************************************************//
/*		�ͷ�����ktv��Ȩ״̬�ķ����ڴ�

		��������void freektvstate( struct ktvstate *kstate )
//*****************************************************************/

CCDDT_API void __stdcall freektvstate( struct pwktvstate *kstate );

//*****************************************************************//
/*
��ȡ�����б�

  ��ȡ����
  ��������struct forbidsong ** recvforbidlist( struct ccddt *vodclient struct , int &fcount)
  ����˵����
		Int &fcount  ���ؽ�����Ŀ����
		����ֵ��
		NULL  ������ĿΪ��
		ָ��   �����
//****************************************************************/
CCDDT_API struct forbidsong ** __stdcall recvforbidlist( struct ccddt *vodclient, int *fcount);

//****************************************************************//
/*   �ͷ����������Ŀ�����ڴ�
��������void forbidlist( struct forbidsong **flist )
//****************************************************************/
CCDDT_API void __stdcall  freeforbidlist( struct forbidsong **flist , int count);
//****************************************************************//
/*��ȡ�и�ʱ��
��������int recvsongchangetime( struct ccddt* vodclient )

  ����ֵ�� -1 ��ȡʱ��ʧ��
  >0  ��ȡ����ʱ��
*/
//****************************************************************//           
CCDDT_API int __stdcall  recvsongchangetime( struct ccddt* vodclient );


//****************************************************************//           

/*��ȡ��ϸ����¼

  ��������Struct recorderinfo ** recvdetailinfo( struct ccddt *vodclient  , char *startime char *endtime , char *roomno , int &dcount)
  
	����˵����

	

	Char *startime ��ѯ��ʼʱ��     ��ʽ  yyyy-mm-dd hh:mm:ss
	Char *endtime ��ѯ����ʱ��
	Char *roomno ������

	Int &dcount ��ϸ��¼������ ���������������㲥��¼Ϊ300������������������ʹ��recvdetailfile
*/

//****************************************************************//           
CCDDT_API struct pwrecorderinfo ** __stdcall recvdetailinfo( struct ccddt *vodclient  , struct pwdetailsearch pdsearch , int *dcount);


//  �������ļ����ǰ���struct recorderinfo˳�򱣴�;
// �˺���ʹ��ʱ��Ҫ����ļ���
CCDDT_API int __stdcall recvdetailfile( struct ccddt *vodclient , struct pwdetailsearch pdsearch , char *filename );


//****************************************************************//
/*
�ͷ���ϸ�����¼�ķ����ڴ�
void freedetailinfo( struct recorderinfo **dinfo )
*/
//****************************************************************//           
CCDDT_API void __stdcall freedetailinfo( struct pwrecorderinfo **dinfo );

//****************************************************************//
/*���͵㲥��¼

  ��������int sendrecorder( struct ccddt *vodclient , struct ktvmsg *kmsg[] , int msgcount )
  
	����˵����
	
	  Int msgcount ���㲥��Ŀ���������һ���ϴ��㲥��¼30��
	  
		����ֵ��
		<0 �������
		>0 ���ͳɹ�����Ŀ
*/
//****************************************************************//           
CCDDT_API int __stdcall sendrecorder( struct ccddt *vodclient , struct pwktvmsg *kmsg[] , int msgcount );




//****************************************************************//           
/*��ȡ��Ŀͳһ����

  ��������Unsigned long recvsongid( struct ccddt *vodclient , struct songinfo &sinfo )
  
	����˵����
	����ͳһ����
//****************************************************************/           
CCDDT_API struct pwnewsongid * __stdcall recvsongid( struct ccddt *vodclient , struct pwnewsonginfo *sinfo );


CCDDT_API void __stdcall  freesongid( struct pwnewsongid *id );


//****************************************************************//           
/*��ȡǰ�û�ϵͳʱ��

		��������
		unsigned long recvpwtime( struct ccddt *vodcliedt )
		
		  ����ֵ��0  ����ʱ��ʧ��
		  >0 ��1970�������
//****************************************************************/           
CCDDT_API unsigned long __stdcall recvpwtime( struct ccddt *vodclient );

//****************************************************************//           
/*���ķ���Ŀ���ܺ���

  ʹ�ô��ຯ��������ķ���Ŀ���ܵĽ���
  
	��������int ccddtdecoder( char *buff , int bufflen )
	
	  ����˵����
	  buff ����������ܵ����ݣ��ַ����͡�����ʱ������ܺ�����ݡ�
	  len  ���������ݳ���
	  flog ��0������ļ�ͷ��1������ļ��壬2�����ļ�ĩβ


		����ֵ��������      ��ʾ���ܺ���ֽ���
		��           �������ķ���Ŀ��ʽ
		С����       ��ʾ����ʧ�ܡ���ͬ�ķ���ֵ�в�ͬ�ĺ��塣
		-1           ������̫С
		-2           ���������ݲ���
		-3           �����㷨����
		-4           ��Ҫ������̬��
		-5           �����ڴ�ʧ��
	
//****************************************************************/
CCDDT_API int __stdcall ccddtdecoder( char *buff , int bufflen , int flog);
#endif





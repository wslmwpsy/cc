
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
	char name[128];			// 曲目名称
	char singername[128];	// 演唱者
	char language[64];		// 语言
	char type[64];			// 保留
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
	char aip[32]; // A前置机IP
	char bip[32]; // B前置机IP
	int  flag;   // 通信加密标志

	int  conntimeout;
/*	char certfile[256];  //客户端证书文件路径  client.pem
	char calist[256];    //证书链文件路径  root.pem
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
/*通信结构初始化

		函数名：struct ccddt *ccddtinit(  char *aip , char *bip )
		
		  参数说明：
		  Char *aip      第一前置机的ip   主前置机
		  Char *bip      第二前置机的ip	  从前置机
		  int timeout    进行SSL网络连接时的超时时间，却省值为3秒 ，设置范围是 2,3,4秒
			返回值：NULL           初始化失败
			Struct ccddt *     结构体指针
		 注意：本函数每个进程只能初始化一次，如果初始化多次可能会引起程序异常
*/

//*******************************************************************//
CCDDT_API struct ccddt * __stdcall  ccddtinit(  char *aip , char *bip  , int timeout );

//******************************************************************//
/*
通信结构关闭

		函数名：void ccddtclose( struct ccddt *vodclient )
		返回值：无
//******************************************************************/

CCDDT_API void __stdcall  ccddtclose( struct ccddt *vodclient );
//******************************************************************//
/*
获取前置机状态

		函数名：int recvccddtstate( struct ccddt *vodclient )
		
		  返回值：
		  -3 初始化客户端证书异常
		  -2 两台前置机都异常
		  -1 主前置机异常
		  0  从前置机异常
		  1  前置机都正常
//*****************************************************************/
CCDDT_API int __stdcall recvccddtstate( struct ccddt *vodclient );

//*****************************************************************//
/*获取KTV授权状态

  状态请求
  函数名：struct ktvstate *recvktvstate( struct ccddt *vodclient )
  
	参数说明：
	
	  返回值：
	  NULL 前置机异常
	  结构指针 函数成功
//*****************************************************************/
CCDDT_API struct pwktvstate  * __stdcall recvktvstate( struct ccddt *vodclient );

//*****************************************************************//
/*		释放请求ktv授权状态的返回内存

		函数名：void freektvstate( struct ktvstate *kstate )
//*****************************************************************/

CCDDT_API void __stdcall freektvstate( struct pwktvstate *kstate );

//*****************************************************************//
/*
获取禁播列表

  获取函数
  函数名：struct forbidsong ** recvforbidlist( struct ccddt *vodclient struct , int &fcount)
  参数说明：
		Int &fcount  返回禁播曲目条数
		返回值：
		NULL  禁播曲目为空
		指针   结果集
//****************************************************************/
CCDDT_API struct forbidsong ** __stdcall recvforbidlist( struct ccddt *vodclient, int *fcount);

//****************************************************************//
/*   释放请求禁播曲目返回内存
函数名：void forbidlist( struct forbidsong **flist )
//****************************************************************/
CCDDT_API void __stdcall  freeforbidlist( struct forbidsong **flist , int count);
//****************************************************************//
/*获取切歌时长
函数名：int recvsongchangetime( struct ccddt* vodclient )

  返回值： -1 提取时长失败
  >0  提取到的时长
*/
//****************************************************************//           
CCDDT_API int __stdcall  recvsongchangetime( struct ccddt* vodclient );


//****************************************************************//           

/*获取详细点歌纪录

  函数名：Struct recorderinfo ** recvdetailinfo( struct ccddt *vodclient  , char *startime char *endtime , char *roomno , int &dcount)
  
	参数说明：

	

	Char *startime 查询起始时间     格式  yyyy-mm-dd hh:mm:ss
	Char *endtime 查询结束时间
	Char *roomno 包房号

	Int &dcount 详细记录的条数 ，本函数最大请求点播纪录为300条。更大量的数据请使用recvdetailfile
*/

//****************************************************************//           
CCDDT_API struct pwrecorderinfo ** __stdcall recvdetailinfo( struct ccddt *vodclient  , struct pwdetailsearch pdsearch , int *dcount);


//  数据在文件中是按照struct recorderinfo顺序保存;
// 此函数使用时需要添加文件名
CCDDT_API int __stdcall recvdetailfile( struct ccddt *vodclient , struct pwdetailsearch pdsearch , char *filename );


//****************************************************************//
/*
释放详细请求纪录的返回内存
void freedetailinfo( struct recorderinfo **dinfo )
*/
//****************************************************************//           
CCDDT_API void __stdcall freedetailinfo( struct pwrecorderinfo **dinfo );

//****************************************************************//
/*发送点播纪录

  函数名：int sendrecorder( struct ccddt *vodclient , struct ktvmsg *kmsg[] , int msgcount )
  
	参数说明：
	
	  Int msgcount ：点播曲目个数，最大一次上传点播纪录30条
	  
		返回值：
		<0 程序错误
		>0 发送成功的曲目
*/
//****************************************************************//           
CCDDT_API int __stdcall sendrecorder( struct ccddt *vodclient , struct pwktvmsg *kmsg[] , int msgcount );




//****************************************************************//           
/*获取曲目统一编码

  函数名：Unsigned long recvsongid( struct ccddt *vodclient , struct songinfo &sinfo )
  
	参数说明：
	返回统一编码
//****************************************************************/           
CCDDT_API struct pwnewsongid * __stdcall recvsongid( struct ccddt *vodclient , struct pwnewsonginfo *sinfo );


CCDDT_API void __stdcall  freesongid( struct pwnewsongid *id );


//****************************************************************//           
/*获取前置机系统时钟

		函数名：
		unsigned long recvpwtime( struct ccddt *vodcliedt )
		
		  返回值：0  请求时钟失败
		  >0 自1970年的秒数
//****************************************************************/           
CCDDT_API unsigned long __stdcall recvpwtime( struct ccddt *vodclient );

//****************************************************************//           
/*中文发曲目解密函数

  使用此类函数完成中文发曲目加密的解码
  
	函数名：int ccddtdecoder( char *buff , int bufflen )
	
	  参数说明：
	  buff ：传入待解密的数据，字符串型。返回时保存解密后的数据。
	  len  ：传入数据长度
	  flog ：0代表解文件头，1代表解文件体，2代表文件末尾


		返回值：大于零      表示解密后的字节数
		零           不是中文发曲目格式
		小于零       表示解密失败。不同的返回值有不同的含义。
		-1           缓冲区太小
		-2           待解密数据不够
		-3           解密算法错误
		-4           需要升级动态库
		-5           申请内存失败
	
//****************************************************************/
CCDDT_API int __stdcall ccddtdecoder( char *buff , int bufflen , int flog);
#endif





// DogClient.h: interface for the CDogClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined SHINE_ENCRYPT_DOG_CLIENT_H
#define SHINE_ENCRYPT_DOG_CLIENT_H

#if _MSC_VER > 1000
	#ifndef _SHINE_LINUX_
		#pragma once
	#endif
#endif // _MSC_VER > 1000

#define SHINE_ERROR_MOULDID		-10				//LoginCheck Error  模块编号
#define SHINE_ERROR_COUNT		-11				//LoginCheck Error  点数不够
#define SHINE_ERROR_VALIDTIME	-12				//LoginCheck Error  有效期超过
#define SHINE_ERROR_MISMATCH	-13             
#define SHINE_ERROR_COMMONCHECK -14

#define SHINE_ERROR_OTHER		-1
#define SHINE_ERROR_DISCONNECT  -15            //连接不上服务器

class CDogClient
{
public:
	//函数名称：CDogClient
	//函数说明：构造体 
	//输入参数：ServerIP				--	指定服务器IP地址
	//输入参数：ServerPort				--	指定服务器端口
	//输入参数：strModuleNbr			--	模块编码《4字节数字》
	//输入参数：MaxLinkErrors			--	连接服务器的最大出错次数,用于客户端判断服务器端口是否有效
	//输入参数：TimeOut					--	等待服务器回应的超时时间
	//输入参数：WarningTime				--	有效日期报警阀值
	CDogClient (char* ServerIP,int ServerPort, char* strModuleNbr,int MaxLinkErrors,long TimeOut,long WarningTime
				);
	
	//函数名称：CDogClient
	//函数说明：构造体 
	CDogClient ();

	//函数名称：~CDogClient
	//函数说明：析构函数 
	virtual ~CDogClient();
	
public:
	//函数名称：SetParam
	//函数说明：参数设置
	//输入参数：ServerIP				--	指定服务器IP地址
	//输入参数：ServerPort				--	指定服务器端口
	//输入参数：strModuleNbr			--	模块编码《4字节数字》
	//输入参数：MaxLinkErrors			--	连接服务器的最大出错次数,用于客户端判断服务器端口是否有效
	//输入参数：TimeOut					--	等待服务器回应的超时时间
	//输入参数：WarningTime				--	有效日期报警阀值
	void SetParam(char* ServerIP, 
					   int ServerPort, 
					   char* strModuleNbr, 
					   int MaxLinkErrors, 
					   long TimeOut, 
					   long WarningTime );
	//函数名称：ConnectServer
	//函数说明：连接加密狗server
	//返回值  ：TRUE		--	成功
	//          FALSE		--	失败
	bool ConnectServer();

	//函数名称：LoginCheck
	//函数说明：客户端登陆检查，用于进行模块点数注册操作
	//输出参数：long & lngValidTime  有效日期
	//输入参数：char * strModuleNbr 模块编号
	//返回值  ：0		--	成功
	//          !0		--	失败	
	int LoginCheck(long & lngValidTime,char * strModuleNbr);
		
	//函数名称：GetData
	//函数说明：根据不同参数，从狗中读取对应数据文件长度和信息
	//输入参数：vWhichOne	--	文件索引《0-自用文件；1-客户文件；2-代理商文件》
	//输出参数：vBufferLen	--	文件长度
	//输出参数：vBuffer		--	文件内容
	//返回值  ：0		--	成功
	//          !0		--	失败	
	int GetData(int vWhichOne, int & vBufferLen , char*  vBuffer);
	
	//函数名称：CommonCheck
	//函数说明：客户端请求进行加密服务例行检查
	//返回值  ：0		--	成功
	//          !0		--	失败	
	int CommonCheck();
	
	//函数名称：Logout
	//函数说明：客户端登出请求
	//返回值  ：无
	void Logout(void);
	
	//函数名称：IncSongs
	//函数说明：增加计数请求操作
	//输入参数：incSongTimes	--	增加的计数值，写入加密狗
	//输出参数：incSongTimes	--	加密狗内的总计数值
	//返回值  ：0		--	成功
	//          !0		--	失败	
	int IncSongs(long & incSongTimes); 
	
	//函数名称：VerifyTime
	//函数说明：请求校正服务器时钟
	//返回值  ：无
	void VerifyTime(void);

	//函数名称：GetSongs
	//函数说明：取得加密狗内的总计数值
	//输出参数：sumSongs	--	加密狗内的总计数值
	//返回值  ：0		--	成功
	//          !0		--	失败	
	int GetSongs(long & sumSongs);
	
	//函数名称：RunExec
	//函数说明：执行加密狗中算法
	//输入参数：fileID		--	加密狗中算法索引 《取值范围为0-38》
	//输入参数：runData		--	输入的运算参数  《固定为128字节字符数组》
	//输出参数：runData		--	运算结果  《作为输出时只能使用前127字节,最后一个字节无效》
	//返回值  ：0		--	成功
	//          !0		--	失败	
	int RunExec(int fileID, char*  runData);
	
	//函数名称：Encode
	//函数说明：执行加密狗中算法，进行加密操作
	//输入参数：vInput		--	待加密的字符串(128字节——固定长度)
	//输出参数：vOutput		--	加密后的字符串(128字节——固定长度)
	//返回值  ：0		--	成功
	//          !0		--	失败	
	int Encode(char* vInput, char*  vOutput);
	
	//函数名称：Decode
	//函数说明：执行加密狗中算法，进行解密操作
	//输入参数：vInput		--	待解密的字符串(128字节——固定长度)
	//输出参数：vOutput		--	解密后的字符串(128字节——固定长度)
	//返回值  ：0		--	成功
	//          !0		--	失败	
	int Decode(char* vInput, char*  vOutput);
	
	//函数名称：ActiveClockTime
	//函数说明：执行加密狗中算法，进行指定有效日期的设定
	//输入参数：ActiveString		--	时间激活码
	//输入输出参数：ActiveTime		--	指定有效日期
	//返回值  ：0		--	成功
	//          !0		--	失败	
	int ActiveClockTime(char*  ActiveString, long & ActiveTime);

private:
	bool blnInitialize ;
	void AddModule(char* strModuleNbr);
	void RegisterModules();
	
};

#endif // !defined(AFX_SERVERSOCKETMANAGER_H__96F87621_037D_436B_B0C8_3D80D6E3EC32__INCLUDED_)

#ifndef _STRINGCONVERSION_H_
#define _STRINGCONVERSION_H_

#include <string>
using namespace std;

class string_conversion
{
public:
	string_conversion();
	~string_conversion();
	/*
	功能：得到多字节字符串占用的字节数
	参数：
	    widechar_string：宽字符串
	返回值：
	    成功：实际占用的字节数
		失败：-1
	*/
	//ansi
	int get_byte_size_of_multibyte(const TCHAR *widechar_string);
	//utf-8
	int get_byte_size_of_utf8(const TCHAR *widechar_string);

	/*
	功能：得到宽字符串占用的字节数
	参数：
	    multibyte_string:多字节字符串
	返回值：
	    成功：实际占用的字节数
	    失败：-1
	*/
	int get_byte_size_of_widechar(const char *multibyte_string);
	int get_byte_size_of_widechar_utf8(const char *multibyte_string);
	/*
	功能：把多字节字符串转化成宽字符字符串
	参数：
	    multibyte_string:多字节字符串
		widechar_string：宽字符串
		widechar_size：宽字符占的字节数
	返回值：
	    true:成功
		false：失败
	*/
	//ansi-unicode
	bool multibyte_to_widechar(const char *multibyte_string,TCHAR *widechar_string,int widechar_size);
	//utf8-unicode
	bool utf8_to_widechar(const char *multibyte_string,TCHAR *widechar_string,int widechar_size);
	/*
	功能：把宽字符字符串转化成多字节字符串
	参数：
	    widechar_string：宽字符串
		multibyte_string:多字节字符串
		multibyte_size：多字节占的字节数
	返回值：
		true:成功
		false：失败
	*/
	//unicode-ansi
	bool widechar_to_multibyte(const TCHAR *widechar_string,char *multibyte_string,int multibyte_size);
	//unicode-utf8
	bool widechar_to_utf8(const TCHAR *widechar_string,char *multibyte_string,int multibyte_size);

	/* 
	功能：将二进制数据转换成BASE64编码字符串 
	参数说明： 
		inputBuffer：要编码的二进制数据 
		inputCount：数据长度 
		outputBuffer：存储转换后的BASE64编码字符串 
	返回值： 
		 -1：参数错误 
		>=0：有效编码长度（字符数）,不包括字符串结束符。 
	备注： 
		等效于openssl中EVP_EncodeBlock函数 
	*/  
	INT BASE64_Encode( const BYTE* inputBuffer, INT inputCount, TCHAR* outputBuffer );  
  
	/* 
	功能：将BASE64编码字符串转换为二进制数据 
	参数说明： 
		inputBuffer：BASE64编码字符串 
		inputCount：编码长度（字符数）,应该为4的倍数。 
		outputBuffer：存储转换后的二进制数据 
	返回值： 
		 -1：参数错误 
		 -2：数据错误 
		>=0：转换后的字节数 
	备注： 
		等效于openssl中EVP_DecodeBlock函数 
	*/  
	INT BASE64_Decode( const TCHAR* inputBuffer, INT inputCount, BYTE* outputBuffer );  

	/*编码
	DataByte
		[in]输入的数据长度,以字节为单位
	*/
	string Encode(const unsigned char* Data,int DataByte);
	/*解码
	DataByte
		[in]输入的数据长度,以字节为单位
	OutByte
		[out]输出的数据长度,以字节为单位,请不要通过返回值计算
		输出数据的长度
	*/
	string Decode(const char* Data,int DataByte,int& OutByte);

	unsigned char* base64Decode(char* in, unsigned int& resultSize, bool trimTrailingZeros = true);  
	// returns a newly allocated array - of size "resultSize" - that  
	// the caller is responsible for delete[]ing.  

	char* base64Encode(char const* orig, unsigned origLength);  
	// returns a 0-terminated string that  
	// the caller is responsible for delete[]ing.  
protected:
private:
};

#endif
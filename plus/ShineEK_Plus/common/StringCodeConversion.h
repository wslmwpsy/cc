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
	���ܣ��õ����ֽ��ַ���ռ�õ��ֽ���
	������
	    widechar_string�����ַ���
	����ֵ��
	    �ɹ���ʵ��ռ�õ��ֽ���
		ʧ�ܣ�-1
	*/
	//ansi
	int get_byte_size_of_multibyte(const TCHAR *widechar_string);
	//utf-8
	int get_byte_size_of_utf8(const TCHAR *widechar_string);

	/*
	���ܣ��õ����ַ���ռ�õ��ֽ���
	������
	    multibyte_string:���ֽ��ַ���
	����ֵ��
	    �ɹ���ʵ��ռ�õ��ֽ���
	    ʧ�ܣ�-1
	*/
	int get_byte_size_of_widechar(const char *multibyte_string);
	int get_byte_size_of_widechar_utf8(const char *multibyte_string);
	/*
	���ܣ��Ѷ��ֽ��ַ���ת���ɿ��ַ��ַ���
	������
	    multibyte_string:���ֽ��ַ���
		widechar_string�����ַ���
		widechar_size�����ַ�ռ���ֽ���
	����ֵ��
	    true:�ɹ�
		false��ʧ��
	*/
	//ansi-unicode
	bool multibyte_to_widechar(const char *multibyte_string,TCHAR *widechar_string,int widechar_size);
	//utf8-unicode
	bool utf8_to_widechar(const char *multibyte_string,TCHAR *widechar_string,int widechar_size);
	/*
	���ܣ��ѿ��ַ��ַ���ת���ɶ��ֽ��ַ���
	������
	    widechar_string�����ַ���
		multibyte_string:���ֽ��ַ���
		multibyte_size�����ֽ�ռ���ֽ���
	����ֵ��
		true:�ɹ�
		false��ʧ��
	*/
	//unicode-ansi
	bool widechar_to_multibyte(const TCHAR *widechar_string,char *multibyte_string,int multibyte_size);
	//unicode-utf8
	bool widechar_to_utf8(const TCHAR *widechar_string,char *multibyte_string,int multibyte_size);

	/* 
	���ܣ�������������ת����BASE64�����ַ��� 
	����˵���� 
		inputBuffer��Ҫ����Ķ��������� 
		inputCount�����ݳ��� 
		outputBuffer���洢ת�����BASE64�����ַ��� 
	����ֵ�� 
		 -1���������� 
		>=0����Ч���볤�ȣ��ַ�����,�������ַ����������� 
	��ע�� 
		��Ч��openssl��EVP_EncodeBlock���� 
	*/  
	INT BASE64_Encode( const BYTE* inputBuffer, INT inputCount, TCHAR* outputBuffer );  
  
	/* 
	���ܣ���BASE64�����ַ���ת��Ϊ���������� 
	����˵���� 
		inputBuffer��BASE64�����ַ��� 
		inputCount�����볤�ȣ��ַ�����,Ӧ��Ϊ4�ı����� 
		outputBuffer���洢ת����Ķ��������� 
	����ֵ�� 
		 -1���������� 
		 -2�����ݴ��� 
		>=0��ת������ֽ��� 
	��ע�� 
		��Ч��openssl��EVP_DecodeBlock���� 
	*/  
	INT BASE64_Decode( const TCHAR* inputBuffer, INT inputCount, BYTE* outputBuffer );  

	/*����
	DataByte
		[in]��������ݳ���,���ֽ�Ϊ��λ
	*/
	string Encode(const unsigned char* Data,int DataByte);
	/*����
	DataByte
		[in]��������ݳ���,���ֽ�Ϊ��λ
	OutByte
		[out]��������ݳ���,���ֽ�Ϊ��λ,�벻Ҫͨ������ֵ����
		������ݵĳ���
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
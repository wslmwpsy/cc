#include "stdafx.h"
#include "StringCodeConversion.h"

#include <Windows.h>

string_conversion::string_conversion()
{

}
string_conversion::~string_conversion()
{

}

int string_conversion::get_byte_size_of_multibyte(const TCHAR *widechar_string)
{
	try
	{
		int byte_size=0;

        byte_size = WideCharToMultiByte(CP_ACP,0,widechar_string,-1,NULL,0,NULL,NULL);

		return byte_size;
	}
	catch (...)
	{

	}

	return -1;
}

int string_conversion::get_byte_size_of_utf8(const TCHAR *widechar_string)
{
	try
	{
		int byte_size=0;

		byte_size = WideCharToMultiByte(CP_UTF8,0,widechar_string,-1,NULL,0,NULL,NULL);

		return byte_size;
	}
	catch (...)
	{

	}

	return -1;
}

int string_conversion::get_byte_size_of_widechar(const char *multibyte_string)
{
	try
	{
		int byte_size = 0;

		byte_size = MultiByteToWideChar(CP_ACP,0,multibyte_string,-1,NULL,0);

		return byte_size;
	}
	catch (...)
	{

	}

	return -1;
}

int string_conversion::get_byte_size_of_widechar_utf8(const char *multibyte_string)
{
	try
	{
		int byte_size = 0;

		byte_size = MultiByteToWideChar(CP_UTF8,0,multibyte_string,-1,NULL,0);

		return byte_size;
	}
	catch (...)
	{

	}

	return -1;
}

bool string_conversion::multibyte_to_widechar(const char *multibyte_string,TCHAR *widechar_string,int widechar_size)
{
	try
	{
		int result = 0;

        result = MultiByteToWideChar(CP_ACP,0,multibyte_string,-1,widechar_string,widechar_size);
		if (0!=result)
		{
			return true;
		}
		return false;
	}
	catch (...)
	{

	}

	return false;
}

bool string_conversion::utf8_to_widechar(const char *multibyte_string,TCHAR *widechar_string,int widechar_size)
{
	try
	{
		int result = 0;

		result = MultiByteToWideChar(CP_UTF8,0,multibyte_string,-1,widechar_string,widechar_size);
		if (0!=result)
		{
			return true;
		}
		return false;
	}
	catch (...)
	{

	}

	return false;
}

bool string_conversion::widechar_to_multibyte(const TCHAR *widechar_string,char *multibyte_string,int multibyte_size)
{
	try
	{
		int result = 0;

		result = WideCharToMultiByte(CP_ACP,0,widechar_string,-1,multibyte_string,multibyte_size,NULL,NULL);
		if (0!=result)
		{
			return true;
		}
		return false;
	}
	catch (...)
	{
		
	}

	return false;
}

bool string_conversion::widechar_to_utf8(const TCHAR *widechar_string,char *multibyte_string,int multibyte_size)
{
	try
	{
		int result = 0;

		result = WideCharToMultiByte(CP_UTF8,0,widechar_string,-1,multibyte_string,multibyte_size,NULL,NULL);
		if (0!=result)
		{
			return true;
		}
		return false;
	}
	catch (...)
	{

	}

	return false;
}

static const CHAR* DATA_BIN2ASCII = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";  

INT string_conversion::BASE64_Encode( const BYTE* inputBuffer, INT inputCount, TCHAR* outputBuffer )  
{  
	INT i;  
	BYTE b0, b1, b2;  

	if( (inputBuffer == NULL) || (inputCount < 0) )  
	{  
		return -1;  // 2?¨ºy¡ä¨ª?¨®  
	}  

	if( outputBuffer != NULL )  
	{  
		for( i = inputCount; i > 0; i -= 3 )  
		{  
			if( i >= 3 )  
			{   // ??3¡Á??¨²¨ºy?Y¡Áa??3¨¦4??ASCII¡Á?¡¤?  
				b0 = *inputBuffer++;  
				b1 = *inputBuffer++;  
				b2 = *inputBuffer++;  

				*outputBuffer++ = DATA_BIN2ASCII[b0 >> 2];  
				*outputBuffer++ = DATA_BIN2ASCII[((b0 << 4) | (b1 >> 4)) & 0x3F];  
				*outputBuffer++ = DATA_BIN2ASCII[((b1 << 2) | (b2 >> 6)) & 0x3F];  
				*outputBuffer++ = DATA_BIN2ASCII[b2 & 0x3F];  
			}  
			else  
			{  
				b0 = *inputBuffer++;  
				if( i == 2 )b1 = *inputBuffer++; else b1 = 0;  

				*outputBuffer++ = DATA_BIN2ASCII[b0 >> 2];  
				*outputBuffer++ = DATA_BIN2ASCII[((b0 << 4) | (b1 >> 4)) & 0x3F];  
				*outputBuffer++ = (i == 1) ? TEXT('=') : DATA_BIN2ASCII[(b1 << 2) & 0x3F];  
				*outputBuffer++ = TEXT('=');  
			}  
		} // End for i  

		*outputBuffer++ = TEXT('\0');   // ¨¬¨ª?¨®¡Á?¡¤?¡ä??¨¢¨º?¡À¨º??  
	}  

	return ((inputCount + 2) / 3) * 4;  // ¡¤¦Ì??¨®DD¡ì¡Á?¡¤???¨ºy  
}  

#define B64_EOLN            0xF0    // ??DD/n  
#define B64_CR              0xF1    // ??3¦Ì/r  
#define B64_EOF             0xF2    // ¨¢?¡Á?¡¤?-  
#define B64_WS              0xE0    // ¨¬????¨°??????¡ê¡§/t?¡éspace¡ê?  
#define B64_ERROR           0xFF    // ¡ä¨ª?¨®¡Á?¡¤?  
#define B64_NOT_BASE64(a)   (((a)|0x13) == 0xF3)  

static const BYTE DATA_ASCII2BIN[128] = {  
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xF0,0xFF,0xFF,0xF1,0xFF,0xFF,  
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,  
	0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3E,0xFF,0xF2,0xFF,0x3F,  
	0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,  
	0xFF,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,  
	0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0xFF,0xFF,0xFF,0xFF,0xFF,  
	0xFF,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,  
	0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0xFF,0xFF,0xFF,0xFF,0xFF  
};  

INT string_conversion::BASE64_Decode( const TCHAR* inputBuffer, INT inputCount, BYTE* outputBuffer )  
{  
	INT i, j;  
	BYTE b[4];  
	TCHAR ch;  

	if( (inputBuffer == NULL) || (inputCount < 0) )  
	{  
		return -1;  // 2?¨ºy¡ä¨ª?¨®  
	}  

	// ¨¨£¤3y¨ª¡¤2???¡ã¡Á¡Á?¡¤?  
	while( inputCount > 0 )  
	{  
		ch = *inputBuffer;  
		if( (ch < 0) || (ch >= 0x80) )  
		{  
			return -2;  // ¨ºy?Y¡ä¨ª?¨®¡ê?2??¨²ASCII¡Á?¡¤?¡À¨¤??¡¤??¡ì?¨²  
		}  
		else  
		{  
			if( DATA_ASCII2BIN[ch] == B64_WS )  
			{  
				inputBuffer++;  
				inputCount--;  
			}  
			else  
			{  
				break;  
			}  
		}  
	}  

	// ¨¨£¤3y?22?¦Ì???¡ã¡Á¡Á?¡¤??¡é??3¦Ì??DD¡Á?¡¤??¡é¨¢?¡Á?¡¤?  
	while( inputCount >= 4 )  
	{  
		ch = inputBuffer[inputCount - 1];  
		if( (ch < 0) || (ch >= 0x80) )  
		{  
			return -2;  // ¨ºy?Y¡ä¨ª?¨®¡ê?2??¨²ASCII¡Á?¡¤?¡À¨¤??¡¤??¡ì?¨²  
		}  
		else  
		{  
			if( B64_NOT_BASE64(DATA_ASCII2BIN[ch]) )  
			{  
				inputCount--;  
			}  
			else  
			{  
				break;  
			}  
		}  
	}  

	// ¡Á?¡¤?¡ä?3¡è?¨¨¡À?D??a4¦Ì?¡À?¨ºy  
	if( (inputCount % 4) != 0 )  
	{  
		return -2;  // ¨ºy?Y¡ä¨ª?¨®  
	}  

	if( outputBuffer != NULL )  
	{  
		for( i = 0; i < inputCount; i += 4 )  
		{  
			for( j = 0; j < 4; j++ )  
			{  
				ch = *inputBuffer++;  
				if( (ch < 0) || (ch >= 0x80) )  
				{  
					return -2;  // ¨ºy?Y¡ä¨ª?¨®¡ê?2??¨²ASCII¡Á?¡¤?¡À¨¤??¡¤??¡ì?¨²  
				}  
				else  
				{  
					if( ch == '=' ) // ¡¤¡é??BASE64¡À¨¤???D¦Ì?¨¬?3?¡Á?¡¤?  
					{  
						break;  
					}  
					else  
					{  
						b[j] = DATA_ASCII2BIN[ch];  
						if( b[j] & 0x80 )  
						{  
							return -2;  // ¨ºy?Y¡ä¨ª?¨®¡ê??TD¡ì¦Ì?Base64¡À¨¤??¡Á?¡¤?  
						}  
					}                     
				}  
			} // End for j  

			if( j == 4 )  
			{  
				*outputBuffer++ = (b[0] << 2) | (b[1] >> 4);  
				*outputBuffer++ = (b[1] << 4) | (b[2] >> 2 );  
				*outputBuffer++ = (b[2] << 6) | b[3];  
			}  
			else if( j == 3 )  
			{   // ¨®D1??¨¬?3?¡Á??¨²  
				*outputBuffer++ = (b[0] << 2) | (b[1] >> 4);  
				*outputBuffer++ = (b[1] << 4) | (b[2] >> 2 );  

				return (i >> 2) * 3 + 2;  
			}  
			else if( j == 2 )  
			{   // ¨®D2??¨¬?3?¡Á??¨²  
				*outputBuffer++ = (b[0] << 2) | (b[1] >> 4);  

				return (i >> 2) * 3 + 1;  
			}  
			else  
			{  
				return -2;  // ¨ºy?Y¡ä¨ª?¨®¡ê??TD¡ì¦Ì?Base64¡À¨¤??¡Á?¡¤?  
			}             
		}   // End for i  
	}  

	return (inputCount >> 2) * 3;  
}  

string string_conversion::Encode(const unsigned char* Data,int DataByte)
{
	//¡À¨¤??¡À¨ª
	const char EncodeTable[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	//¡¤¦Ì???¦Ì
	string strEncode;
	unsigned char Tmp[4]={0};
	int LineLength=0;
	for(int i=0;i<(int)(DataByte / 3);i++)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		Tmp[3] = *Data++;
		strEncode+= EncodeTable[Tmp[1] >> 2];
		strEncode+= EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
		strEncode+= EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
		strEncode+= EncodeTable[Tmp[3] & 0x3F];
		if(LineLength+=4,LineLength==76) {strEncode+="\r\n";LineLength=0;}
	}
	//??¨º¡ê¨®¨¤¨ºy?Y??DD¡À¨¤??
	int Mod=DataByte % 3;
	if(Mod==1)
	{
		Tmp[1] = *Data++;
		strEncode+= EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode+= EncodeTable[((Tmp[1] & 0x03) << 4)];
		strEncode+= "==";
	}
	else if(Mod==2)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		strEncode+= EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode+= EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
		strEncode+= EncodeTable[((Tmp[2] & 0x0F) << 2)];
		strEncode+= "=";
	}

	return strEncode;
}

string string_conversion::Decode(const char* Data,int DataByte,int& OutByte)
{
	//?a??¡À¨ª
	const char DecodeTable[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		62, // '+'
		0, 0, 0,
		63, // '/'
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
		0, 0, 0, 0, 0, 0, 0,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
		13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
		0, 0, 0, 0, 0, 0,
		26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
	};
	//¡¤¦Ì???¦Ì
	string strDecode;
	int nValue;
	int i= 0;
	while (i < DataByte)
	{
		if (*Data != '\r' && *Data!='\n')
		{
			nValue = DecodeTable[*Data++] << 18;
			nValue += DecodeTable[*Data++] << 12;
			strDecode+=(nValue & 0x00FF0000) >> 16;
			OutByte++;
			if (*Data != '=')
			{
				nValue += DecodeTable[*Data++] << 6;
				strDecode+=(nValue & 0x0000FF00) >> 8;
				OutByte++;
				if (*Data != '=')
				{
					nValue += DecodeTable[*Data++];
					strDecode+=nValue & 0x000000FF;
					OutByte++;
				}
			}
			i += 4;
		}
		else// ??3¦Ì??DD,¨¬?1y
		{
			Data++;
			i++;
		}
	}
	return strDecode;
}

static char base64DecodeTable[256];  


char* strDup(char const* str)   
{  
	if (str == NULL) return NULL;  
	size_t len = strlen(str) + 1;  
	char* copy = new char[len];  

	if (copy != NULL)   
	{  
		memcpy(copy, str, len);  
	}  
	return copy;  
}  

char* strDupSize(char const* str)   
{  
	if (str == NULL) return NULL;  
	size_t len = strlen(str) + 1;  
	char* copy = new char[len];  

	return copy;  
}  



static void initBase64DecodeTable()  
{  
	int i;  
	for (i = 0; i < 256; ++i) base64DecodeTable[i] = (char)0x80;  
	// default value: invalid  

	for (i = 'A'; i <= 'Z'; ++i) base64DecodeTable[i] = 0 + (i - 'A');  
	for (i = 'a'; i <= 'z'; ++i) base64DecodeTable[i] = 26 + (i - 'a');  
	for (i = '0'; i <= '9'; ++i) base64DecodeTable[i] = 52 + (i - '0');  
	base64DecodeTable[(unsigned char)'+'] = 62;  
	base64DecodeTable[(unsigned char)'/'] = 63;  
	base64DecodeTable[(unsigned char)'='] = 0;  
}  

unsigned char* string_conversion::base64Decode(char* in, unsigned int& resultSize, bool trimTrailingZeros)   
{  
	static bool haveInitedBase64DecodeTable = false;  
	if (!haveInitedBase64DecodeTable)  
	{  
		initBase64DecodeTable();  
		haveInitedBase64DecodeTable = true;  
	}  

	unsigned char* out = (unsigned char*)strDupSize(in); // ensures we have enough space  
	int k = 0;  
	int const jMax = strlen(in) - 3;  
	// in case "in" is not a multiple of 4 bytes (although it should be)  
	for (int j = 0; j < jMax; j += 4)   
	{  
		char inTmp[4], outTmp[4];  
		for (int i = 0; i < 4; ++i)   
		{  
			inTmp[i] = in[i+j];  
			outTmp[i] = base64DecodeTable[(unsigned char)inTmp[i]];  
			if ((outTmp[i]&0x80) != 0) outTmp[i] = 0; // pretend the input was 'A'  
		}  

		out[k++] = (outTmp[0]<<2) | (outTmp[1]>>4);  
		out[k++] = (outTmp[1]<<4) | (outTmp[2]>>2);  
		out[k++] = (outTmp[2]<<6) | outTmp[3];  
	}  

	if (trimTrailingZeros)   
	{  
		while (k > 0 && out[k-1] == '\0') --k;  
	}  
	resultSize = k;  
	unsigned char* result = new unsigned char[resultSize];  
	memmove(result, out, resultSize);  
	delete[] out;  

	return result;  
}  

static const char base64Char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";  

char* string_conversion::base64Encode(char const* origSigned, unsigned origLength)   
{  
	unsigned char const* orig = (unsigned char const*)origSigned; // in case any input bytes have the MSB set  
	if (orig == NULL) return NULL;  

	unsigned const numOrig24BitValues = origLength/3;  
	bool havePadding = origLength > numOrig24BitValues*3;  
	bool havePadding2 = origLength == numOrig24BitValues*3 + 2;  
	unsigned const numResultBytes = 4*(numOrig24BitValues + havePadding);  
	char* result = new char[numResultBytes+1]; // allow for trailing '/0'  

	// Map each full group of 3 input bytes into 4 output base-64 characters:  
	unsigned i;  
	for (i = 0; i < numOrig24BitValues; ++i)   
	{  
		result[4*i+0] = base64Char[(orig[3*i]>>2)&0x3F];  
		result[4*i+1] = base64Char[(((orig[3*i]&0x3)<<4) | (orig[3*i+1]>>4))&0x3F];  
		result[4*i+2] = base64Char[((orig[3*i+1]<<2) | (orig[3*i+2]>>6))&0x3F];  
		result[4*i+3] = base64Char[orig[3*i+2]&0x3F];  
	}  

	// Now, take padding into account.  (Note: i == numOrig24BitValues)  
	if (havePadding)   
	{  
		result[4*i+0] = base64Char[(orig[3*i]>>2)&0x3F];  
		if (havePadding2)  
		{  
			result[4*i+1] = base64Char[(((orig[3*i]&0x3)<<4) | (orig[3*i+1]>>4))&0x3F];  
			result[4*i+2] = base64Char[(orig[3*i+1]<<2)&0x3F];  
		}   
		else   
		{  
			result[4*i+1] = base64Char[((orig[3*i]&0x3)<<4)&0x3F];  
			result[4*i+2] = '=';  
		}  
		result[4*i+3] = '=';  
	}  

	result[numResultBytes] = (char)'\0';  
	return result;  
}  
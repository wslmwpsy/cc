#ifndef _COMMON_FUNCTION_H_
#define _COMMON_FUNCTION_H_

//字符串中字符替换
bool char_replace(TCHAR * src_str,TCHAR old_char,TCHAR new_char);
//替换特殊字符
bool flash_replace_special_char(TCHAR *src_string);
//把字符串转化成16进制字符串，十进制中每两个字节表示一个16进制
bool convert_string_10_to_16(const TCHAR *string_10,TCHAR *string_16,int string_len);

#endif
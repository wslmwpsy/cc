#ifndef _COMMON_FUNCTION_H_
#define _COMMON_FUNCTION_H_

//�ַ������ַ��滻
bool char_replace(TCHAR * src_str,TCHAR old_char,TCHAR new_char);
//�滻�����ַ�
bool flash_replace_special_char(TCHAR *src_string);
//���ַ���ת����16�����ַ�����ʮ������ÿ�����ֽڱ�ʾһ��16����
bool convert_string_10_to_16(const TCHAR *string_10,TCHAR *string_16,int string_len);

#endif
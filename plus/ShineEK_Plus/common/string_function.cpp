#include "StdAfx.h"
#include "string_function.h"

bool char_replace(TCHAR * src_str,TCHAR old_char,TCHAR new_char)
{
	try
	{
		TCHAR * head=src_str;

		if (NULL==head)
		{
			return false;
		}

		while(*head!='\0')
		{
			if(*head==old_char)
			{
				*head=new_char;
			}
			head++;
		}
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool flash_replace_special_char(TCHAR *src_string)
{
	try
	{
		TCHAR * head=src_string;

		if (NULL==head)
		{
			return false;
		}

		while(*head!='\0')
		{
			if('\\'==*head)
			{
				*head = '/';
			}
			else if ('\"'==*head)
			{
				*head = '\'';
			}
			else if ('<'==*head)
			{
				*head = '(';
			}
			else if ('>'==*head)
			{
				*head = ')';
			}
			head++;
		}
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool convert_string_10_to_16(const TCHAR *string_10,TCHAR *string_16,int string_len)
{
	try
	{
		TCHAR temp_byte[16];
		int number=0;

		for (int i=0;i<string_len;i+=2)
		{
            memset(temp_byte,0x0,sizeof(temp_byte));
			//每次拷贝两个
			_tcsncpy(temp_byte,string_10+i,2);
			//转化成10进制
			swscanf(temp_byte,L"%d",&number);
			switch(number)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				{
					string_16[i/2]=string_10[i+1];
				}
				break;
			case 10:
				{
					string_16[i/2]='A';
				}
				break;
			case 11:
				{
					string_16[i/2]='B';
				}
				break;
			case 12:
				{
					string_16[i/2]='C';
				}
				break;
			case 13:
				{
					string_16[i/2]='D';
				}
				break;
			case 14:
				{
					string_16[i/2]='E';
				}
				break;
			case 15:
				{
					string_16[i/2]='F';
				}
				break;
			default:
				return false;
			}
		}
		return true;		
	}
	catch (...)
	{
		
	}
	return false;
}
#include "StdAfx.h"
#include ".\parser_color.h"

int parse_hex(char c)
{
	if (c>='0' && c<='9')
	{
		return c-'0';
	}
	else if (c>='a' && c<='f')
	{
		return c-'a'+10;
	}
	else if (c>='A' && c<='F')
	{
		return c-'A'+10;
	}
	else
	{
		return 0;
	}
}

COLORREF parse_color(const TCHAR* text_color)
{
	return RGB((parse_hex((char)text_color[0])<<4) + (parse_hex((char)text_color[1])),
		(parse_hex((char)text_color[2])<<4) + (parse_hex((char)text_color[3])),
		(parse_hex((char)text_color[4])<<4) + (parse_hex((char)text_color[5])));
}

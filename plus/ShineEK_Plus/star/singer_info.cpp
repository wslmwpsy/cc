#include "StdAfx.h"
#include ".\singer_info.h"

singer_info::singer_info(void)
{
	initialized_variables();
}

singer_info::~singer_info(void)
{
}

void singer_info::initialized_variables(void)
{
    memset(singer_name,0x0,sizeof(singer_name));
	memset(singer_region,0x0,sizeof(singer_region));
	memset(singer_id,0x0,sizeof(singer_id));
}

bool singer_info::set_singer_name(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (_tcslen(value)>=sizeof(singer_name)/2)
		{
			return false;
		}
		_tcscpy(singer_name,value);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}
bool singer_info::set_singer_region(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (_tcslen(value)>=sizeof(singer_region)/2)
		{
			return false;
		}
		_tcscpy(singer_region,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool singer_info::set_singer_sex(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (_tcslen(value)>=sizeof(singer_sex)/2)
		{
			return false;
		}
		_tcscpy(singer_sex,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool singer_info::set_singer_id(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (_tcslen(value)>=sizeof(singer_id)/2)
		{
			return false;
		}
		_tcscpy(singer_id,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool singer_info::get_singer_name(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (0==wcscmp(singer_name,L""))
		{
			return false;
		}
		wcscpy(value,singer_name);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool singer_info::get_singer_region(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (0==_tcscmp(singer_region,L""))
		{
			return false;
		}
		wcscpy(value,singer_region);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool singer_info::get_singer_sex(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (0==_tcscmp(singer_sex,L""))
		{
			return false;
		}
		wcscpy(value,singer_sex);

		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool singer_info::get_singer_id(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (0==_tcscmp(singer_id,L""))
		{
			return false;
		}
		wcscpy(value,singer_id);

		return true;
	}
	catch (...)
	{

	}
	return false;
}
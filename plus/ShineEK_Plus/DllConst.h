#pragma once

#include "stdafx.h"

// ͨ�����������ǵ��뻹�ǵ���
#ifdef _EXPORT_KTV_DLL_
#define KTV_DLL_API __declspec(dllexport)
#else
#define KTV_DLL_API __declspec(dllimport)
#endif
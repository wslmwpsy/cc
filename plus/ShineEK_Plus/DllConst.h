#pragma once

#include "stdafx.h"

// 通过宏来控制是导入还是导出
#ifdef _EXPORT_KTV_DLL_
#define KTV_DLL_API __declspec(dllexport)
#else
#define KTV_DLL_API __declspec(dllimport)
#endif
// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被改写。


#include "stdafx.h"
#include "shockwaveflash.h"
#include ".\shockwaveflash.h"

/////////////////////////////////////////////////////////////////////////////
// CShockwaveflash

IMPLEMENT_DYNCREATE(CShockwaveflash, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CShockwaveflash 属性

/////////////////////////////////////////////////////////////////////////////
// CShockwaveflash 操作

void CShockwaveflash::SetWMode(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x85, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

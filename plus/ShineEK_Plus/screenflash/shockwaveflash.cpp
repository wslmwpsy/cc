// ������������� Microsoft Visual C++ ������ IDispatch ��װ��

// ע��: ��Ҫ�޸Ĵ��ļ������ݡ����������
//  Microsoft Visual C++ �������ɣ������޸Ľ�����д��


#include "stdafx.h"
#include "shockwaveflash.h"
#include ".\shockwaveflash.h"

/////////////////////////////////////////////////////////////////////////////
// CShockwaveflash

IMPLEMENT_DYNCREATE(CShockwaveflash, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CShockwaveflash ����

/////////////////////////////////////////////////////////////////////////////
// CShockwaveflash ����

void CShockwaveflash::SetWMode(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x85, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

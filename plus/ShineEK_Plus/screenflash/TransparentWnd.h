#if !defined(AFX_TRANSPARENTWND_H__DE4E13D8_7F8E_4448_AF22_01F68E7DFE3A__INCLUDED_)
#define AFX_TRANSPARENTWND_H__DE4E13D8_7F8E_4448_AF22_01F68E7DFE3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CTransparentWnd.h : header file

#include "shockwaveflash.h"

#define FLASH_INIT				0
#define FLASH_PLAYING			1
#define FLASH_OVER				2

class CTransparentWnd : public CWnd
{
public:
	CTransparentWnd();
	virtual ~CTransparentWnd();

	// 创建窗口
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	//flash界面的消息响应函数
	void FlashCallShockwaveflash(LPCTSTR request);
	// 设置属性
//	int LoadSettings();
	// 设置透明
	int SetWindowStyle(COLORREF crColor , BYTE btAlpha  , DWORD dwFlags = LWA_ALPHA);

	COLORREF CORE_HexToRGB(CString cszHex);
	// 播放flash
	bool PlayFlash(TCHAR *pwFlashPath, CRect rect, UINT flashId = NULL);
	// 停止flash
	void StopFlash();

	void MoveFlashWindow(CRect rt);
	
	void ShowFlashWindow(int nCmdShow);

	void set_message_handle(HWND hWnd);

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
// 	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	//背景色
	CBrush m_brush;
	//设置背景色
	BYTE m_bgR;
	BYTE m_bgG;
	BYTE m_bgB;
	// flash播放对象
	CShockwaveflash *m_pFlash;

	// flash 播放状态 0:初始 1:正在播放 2:播放结束
	int m_nState;

	HWND m_messagehwnd;
	// 
// 	// 窗口是否总在在最上方显示
// 	BOOL m_bTopMost;
// 	//程序是否开机自动运行
// 	BOOL m_bAutoRun;

protected:
	//{{AFX_MSG(CTransparentWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

private:
// 	//读注册表
// 	int QueryRegKey(HKEY hkey, char *subKey, char* valueName, char* pbuf, DWORD *dwSize);
// 	//删除注册表键值
// 	int DelRegValue(HKEY hkey, char *subKey, char* valueName);
// 	//写注册表
// 	int SetRegKeyValue(HKEY hkey, char *subKey, char* valueName, char* pbuf, DWORD dwSize, DWORD dwType);
};

#endif // !defined(AFX_TRANSPARENTWND_H__DE4E13D8_7F8E_4448_AF22_01F68E7DFE3A__INCLUDED_)

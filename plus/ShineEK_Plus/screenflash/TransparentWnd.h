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

	// ��������
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	//flash�������Ϣ��Ӧ����
	void FlashCallShockwaveflash(LPCTSTR request);
	// ��������
//	int LoadSettings();
	// ����͸��
	int SetWindowStyle(COLORREF crColor , BYTE btAlpha  , DWORD dwFlags = LWA_ALPHA);

	COLORREF CORE_HexToRGB(CString cszHex);
	// ����flash
	bool PlayFlash(TCHAR *pwFlashPath, CRect rect, UINT flashId = NULL);
	// ֹͣflash
	void StopFlash();

	void MoveFlashWindow(CRect rt);
	
	void ShowFlashWindow(int nCmdShow);

	void set_message_handle(HWND hWnd);

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
// 	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	//����ɫ
	CBrush m_brush;
	//���ñ���ɫ
	BYTE m_bgR;
	BYTE m_bgG;
	BYTE m_bgB;
	// flash���Ŷ���
	CShockwaveflash *m_pFlash;

	// flash ����״̬ 0:��ʼ 1:���ڲ��� 2:���Ž���
	int m_nState;

	HWND m_messagehwnd;
	// 
// 	// �����Ƿ����������Ϸ���ʾ
// 	BOOL m_bTopMost;
// 	//�����Ƿ񿪻��Զ�����
// 	BOOL m_bAutoRun;

protected:
	//{{AFX_MSG(CTransparentWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

private:
// 	//��ע���
// 	int QueryRegKey(HKEY hkey, char *subKey, char* valueName, char* pbuf, DWORD *dwSize);
// 	//ɾ��ע����ֵ
// 	int DelRegValue(HKEY hkey, char *subKey, char* valueName);
// 	//дע���
// 	int SetRegKeyValue(HKEY hkey, char *subKey, char* valueName, char* pbuf, DWORD dwSize, DWORD dwType);
};

#endif // !defined(AFX_TRANSPARENTWND_H__DE4E13D8_7F8E_4448_AF22_01F68E7DFE3A__INCLUDED_)

// TransparentWnd.cpp : implementation file
//

#include "stdafx.h"
#include "../flashktv10.h"
#include "TransparentWnd.h"
#include "comdef.h"
#include "../parserxml\ParserXml.h"
#include "../file/log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentWnd
/*extern */wstring g_strCurDir;


CTransparentWnd::CTransparentWnd()
{
    m_bgR = 0;
    m_bgG = 0;
    m_bgB = 0;
    m_messagehwnd = NULL;
    m_nState = FLASH_INIT;

    m_pFlash = new CShockwaveflash;

	m_brush.CreateSolidBrush(RGB(0, 0, 0)); // 生成一黑色刷子
}

CTransparentWnd::~CTransparentWnd()
{	
    delete m_pFlash;
    m_pFlash = NULL;
    m_nState= FLASH_INIT;
}


BEGIN_MESSAGE_MAP(CTransparentWnd, CWnd)
    //{{AFX_MSG_MAP(CTransparentWnd)
	ON_WM_CTLCOLOR()
// 	ON_WM_ERASEBKGND()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CTransparentWnd,CWnd)
    ON_EVENT(CTransparentWnd,SCREEN_FLASH_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)	//异形flash
	ON_EVENT(CTransparentWnd,CHALLENGE_STAR_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)	//挑战大咖flash
	ON_EVENT(CTransparentWnd,ACROSS_PASS_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)	//百秒夺奖活动flash
	ON_EVENT(CTransparentWnd,CHALLENGE_STAR_SOFT_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)	//软解挑战大咖flash
	ON_EVENT(CTransparentWnd,ACROSS_PASS_SOFT_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)	//软解百秒夺奖活动flash
	ON_EVENT(CTransparentWnd,WECHAT_INTERACTION_SOFT_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)	//软解微信互动-弹幕flash
	ON_EVENT(CTransparentWnd,WECHAT_INTERACTION_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)	//场景屏微信互动-弹幕flash
	ON_EVENT(CTransparentWnd,WECHAT_GIFT_SOFT_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)	//软解微信互动-礼物（魔法表情）flash
	ON_EVENT(CTransparentWnd,WECHAT_GIFT_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)	//场景屏微信互动-礼物（魔法表情）flash
END_EVENTSINK_MAP()

void CTransparentWnd::FlashCallShockwaveflash(LPCTSTR request)
{
    TCHAR command[1024] = {0x00};
    TCHAR args[2048] = {0x00};
    CParserXml parser_xml;
    bool result = false;

    try
    {
        memset(command, 0x0, sizeof(command));
        memset(args, 0x0, sizeof(args));

        if (_tcslen(request) >= (sizeof(args)/2))
        {
            return;
        }

        //设置键盘焦点到本窗口
        SetFocus();

        //解析消息
        result = parser_xml.parser_flash_request_xml(request, command, args);
        if (!result)
        {
            return;
        }

        if (0 == _tcscmp(command, L"end"))
        {
            StopFlash();

            m_nState = FLASH_OVER;
        }
        else
        {
            if (0!=m_messagehwnd)
            {
                ::SendMessage(m_messagehwnd,DM_SUB_WINDOW_MESSAGE,(WPARAM)request,NULL);
            }
        }
    }
    catch (...)
    {
    }
    return;
}

BOOL CTransparentWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, 
    const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
    CString str = AfxRegisterWndClass(CS_DBLCLKS, ::LoadCursor(AfxGetInstanceHandle(),NULL), 0, 
        ::LoadIcon(AfxGetInstanceHandle(), (LPCTSTR)IDD_DIALOG));

    BOOL bRet = CWnd::CreateEx( WS_EX_TOOLWINDOW|WS_EX_TOPMOST,
        (LPCTSTR)str, _T("Speech Identification"), WS_POPUP, rect, NULL, 0);

	long formstyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	SetWindowLong(m_hWnd,GWL_EXSTYLE, formstyle | WS_EX_LAYERED);
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW, SWP_DRAWFRAME);

    return bRet;
}

bool CTransparentWnd::PlayFlash(TCHAR *pFlashPath, CRect rect, UINT flashId /*= NULL*/)
{
	bool bRet = false;
    //加载设置
//	LoadSettings();

    bRet = m_pFlash->Create(L"flash", WS_CHILD | WS_VISIBLE | WS_HSCROLL| WS_VSCROLL, rect, this, flashId);
	if (!bRet)	return false;

    //读取flash文件并开始播放
    m_pFlash->LoadMovie(0, pFlashPath);

    m_pFlash->SetWMode((CString)_T("transparent"));

//	m_pFlash->put_BackgroundColor(RGB(m_bgR, m_bgG, m_bgB));
	m_pFlash->put_BackgroundColor(0);

    ShowFlashWindow(SW_SHOW);
    
//	m_pFlash->Play();

    m_nState = FLASH_PLAYING;

    return true;
}
void CTransparentWnd::StopFlash()
{
    m_pFlash->StopPlay();

    this->ShowWindow(SW_HIDE);
}

int CTransparentWnd::SetWindowStyle(COLORREF crColor ,BYTE btAlpha , DWORD dwFlags)
{
// 	// 将窗口全屏
// 	long sx = ::GetSystemMetrics(SM_CXSCREEN);
// 	long sy = ::GetSystemMetrics(SM_CYSCREEN);

	BOOL bRet = SetLayeredWindowAttributes(RGB(m_bgR, m_bgG, m_bgB), btAlpha, /*LWA_COLORKEY | LWA_ALPHA*/dwFlags); /*GetSysColor( COLOR_3DFACE )*/
// 	TCHAR log[256] = {0};
// 	swprintf(log, L"SetLayeredWindowAttributes返回值：%d", bRet);
// 	WriteLog(__FL__, log);

	UpdateWindow();

    return 0;
}

void CTransparentWnd::set_message_handle(HWND hWnd)
{
    m_messagehwnd = hWnd;
}

void CTransparentWnd::MoveFlashWindow(CRect rt)
{
    m_pFlash->MoveWindow(rt);
}

void CTransparentWnd::ShowFlashWindow(int nCmdShow)
{
    m_pFlash->ShowWindow(nCmdShow);
}
COLORREF CTransparentWnd::CORE_HexToRGB(CString cszHex)
{
    int nR, nG, nB;
    string_conversion strcov;
    char szTmpR[256] = {0x00}, szTmpG[256] = {0x00}, szTmpB[256] = {0x00};

    if(cszHex.GetLength() == 7)
    {
        CString cszR = _T("0x")+cszHex.Mid(1,2);
        CString cszG = _T("0x")+cszHex.Mid(3,2);
        CString cszB = _T("0x")+cszHex.Mid(5,2);

        strcov.widechar_to_multibyte(cszR.GetBuffer(0), szTmpR, 256);
        nR = strtol(szTmpR, NULL, 16);
        strcov.widechar_to_multibyte(cszR.GetBuffer(0), szTmpG, 256);
        nG = strtol(szTmpG, NULL, 16);
        strcov.widechar_to_multibyte(cszR.GetBuffer(0), szTmpB, 256);
        nB = strtol(szTmpB, NULL, 16);
    }
    else if(cszHex.GetLength() == 6)
    {
        CString cszR = _T("0x")+cszHex.Mid(0,2);
        CString cszG = _T("0x")+cszHex.Mid(2,2);
        CString cszB = _T("0x")+cszHex.Mid(4,2);

        strcov.widechar_to_multibyte(cszR.GetBuffer(0), szTmpR, 256);
        nR = strtol(szTmpR, NULL, 16);
        strcov.widechar_to_multibyte(cszR.GetBuffer(0), szTmpG, 256);
        nG = strtol(szTmpG, NULL, 16);
        strcov.widechar_to_multibyte(cszR.GetBuffer(0), szTmpB, 256);
        nB = strtol(szTmpB, NULL, 16);
    }
    else
    {
        nR = 0;
        nG = 0;
        nB = 0;
    }

    COLORREF crColor = RGB(nR, nG, nB);
    return crColor;
}

HBRUSH CTransparentWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
// 	return NULL;
	return m_brush; //返加黑色刷子
}

// BOOL CTransparentWnd::OnEraseBkgnd(CDC* pDC)
// {
// 	return TRUE;
// 	return CWnd::OnEraseBkgnd(pDC);
// }
/*int CTransparentWnd::LoadSettings(void)
{
    m_bTopMost = FALSE;
    m_bAutoRun = FALSE;

    ULONG ulSize;
    ulSize = sizeof(BOOL);
    QueryRegKey(HKEY_LOCAL_MACHINE,"SoftWare\\Strike1Soft\\DeskTopFlash",
        "TopMost",(char*)&m_bTopMost, &ulSize);
    ulSize = sizeof(BOOL);
    QueryRegKey(HKEY_LOCAL_MACHINE,"SoftWare\\Strike1Soft\\DeskTopFlash",
        "AutoRun",(char*)&m_bAutoRun, &ulSize);	

    return 0;
}
//读注册表
int CTransparentWnd::QueryRegKey(HKEY hkey, char *subKey, char* valueName, char* pbuf, DWORD *dwSize)
{
    HKEY hReg;
    long result;
    result = RegOpenKeyExA(hkey, subKey, NULL, KEY_ALL_ACCESS, &hReg);
    if(ERROR_SUCCESS != result)
    {
        return 1;
    }
    result = RegQueryValueExA(hReg, valueName, NULL, NULL, (LPBYTE)pbuf, dwSize);
    if (ERROR_SUCCESS != result)
        return 2;
    RegCloseKey(hReg);

    return 0;
}
//写注册表
int CTransparentWnd::SetRegKeyValue(HKEY hkey, char *subKey, char* valueName, char* pbuf, DWORD dwSize, DWORD dwType)
{
    long result;
    HKEY hReg;
    result = RegCreateKeyA(hkey, subKey, &hReg);
    if (ERROR_SUCCESS != result)
    {
        return 1;
    }

    result = RegSetValueExA(hReg,      // subkey handle 
        valueName,  // value name 
        0,                 // must be zero 
        dwType,         // value type //REG_BINARY,REG_SZ
        (LPBYTE) pbuf,  // pointer to value data 
        dwSize);    // length of value data

    if (ERROR_SUCCESS != result)
    {
        return 2;
    }
    return 0;
}
//删除注册表键值
int CTransparentWnd::DelRegValue(HKEY hkey, char *subKey, char* valueName)
{
    LONG retVal;
    HKEY hKeyTemp;

    //bKey = GetBaseRegKey(BaseKey);
    retVal = RegOpenKeyExA(hkey,subKey,0,KEY_ALL_ACCESS,&hKeyTemp);  //-- 打开子键
    if (retVal != ERROR_SUCCESS)
    {
        return 1;
    }

    retVal = RegDeleteValue(hKeyTemp,(LPCTSTR)valueName);
    if(retVal !=ERROR_SUCCESS)
    {
        RegCloseKey(hKeyTemp);  
        return 2;
    }
    RegCloseKey(hKeyTemp);
    return 0;
}*/
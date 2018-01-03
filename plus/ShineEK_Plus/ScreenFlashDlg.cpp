// ScreenFlashDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenFlashDlg.h"
#include "afxdialogex.h"


// CScreenFlashDlg 对话框

IMPLEMENT_DYNAMIC(CScreenFlashDlg, CDialogEx)

CScreenFlashDlg::CScreenFlashDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScreenFlashDlg::IDD, pParent)
{

}

CScreenFlashDlg::~CScreenFlashDlg()
{
}

void CScreenFlashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CScreenFlashDlg, CDialogEx)
END_MESSAGE_MAP()


// CScreenFlashDlg 消息处理程序

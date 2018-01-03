#pragma once


// CScreenFlashDlg 对话框

class CScreenFlashDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScreenFlashDlg)

public:
	CScreenFlashDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CScreenFlashDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

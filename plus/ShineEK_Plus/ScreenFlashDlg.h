#pragma once


// CScreenFlashDlg �Ի���

class CScreenFlashDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScreenFlashDlg)

public:
	CScreenFlashDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CScreenFlashDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

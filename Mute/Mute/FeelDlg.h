#pragma once
#include "afxwin.h"


// CFeelDlg ��ȭ �����Դϴ�.

class CFeelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFeelDlg)

public:
	CFeelDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFeelDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FEEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedExciting();
	afx_msg void OnBnClickedSad();
	afx_msg void OnBnClickedCalm();
	afx_msg void OnBnClickedBoring();


	int feelnow;
	afx_msg void OnBnClickedExcited();
};

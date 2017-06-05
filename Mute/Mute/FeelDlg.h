#pragma once
#include "afxwin.h"


// CFeelDlg 대화 상자입니다.

class CFeelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFeelDlg)

public:
	CFeelDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFeelDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FEEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedExciting();
	afx_msg void OnBnClickedSad();
	afx_msg void OnBnClickedCalm();
	afx_msg void OnBnClickedBoring();


	int feelnow;
	afx_msg void OnBnClickedExcited();
};

#pragma once


// CPopup 대화 상자입니다.

class CPopup : public CDialogEx
{
	DECLARE_DYNAMIC(CPopup)

public:
	CPopup(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPopup();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_POPUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPop1();
	afx_msg void OnBnClickedPop2();
	afx_msg void OnBnClickedPop3();
	afx_msg void OnBnClickedPop4();
};

#pragma once


// CPopup ��ȭ �����Դϴ�.

class CPopup : public CDialogEx
{
	DECLARE_DYNAMIC(CPopup)

public:
	CPopup(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPopup();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_POPUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPop1();
	afx_msg void OnBnClickedPop2();
	afx_msg void OnBnClickedPop3();
	afx_msg void OnBnClickedPop4();
};

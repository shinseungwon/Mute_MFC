
// MuteDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMuteDlg ��ȭ ����
class CMuteDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMuteDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MUTE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int feelnow=0;
	struct CurrentList{
		int playcount;
		CString path;
		CString name;		
	};

	struct CurrentList NowOn[100];
	CString nowplaying;

;
afx_msg void OnBnClickedAdd();

CListCtrl nowonlist;
};


// MuteDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMuteDlg 대화 상자
class CMuteDlg : public CDialogEx
{
// 생성입니다.
public:
	CMuteDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MUTE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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

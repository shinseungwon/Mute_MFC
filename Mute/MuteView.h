
// MuteView.h : CMuteView 클래스의 인터페이스
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "mmsystem.h"
class CMuteSet;

class CMuteView : public CRecordView
{
protected: // serialization에서만 만들어집니다.
	CMuteView();
	DECLARE_DYNCREATE(CMuteView)

public:
	enum{ IDD = IDD_MUTE_FORM };
	CMuteSet* m_pSet;

// 특성입니다.
public:
CMuteDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMuteView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListCtrl playlist;

	afx_msg void OnStnClickedFeelnow();
	
	void AddColumn(void);


	void AddMusic(int x);
	afx_msg void OnBnClickedFeel1();
	afx_msg void OnBnClickedFeel2();
	afx_msg void OnBnClickedFeel3();
	afx_msg void OnBnClickedFeel4();


	afx_msg void OnBnClickedDelete();

	afx_msg void OnNMClickPlaylist(NMHDR *pNMHDR, LRESULT *pResult);
	int selectednow;
	int currentlist;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedReset();

	afx_msg void OnNMDblclkPlaylist(NMHDR *pNMHDR, LRESULT *pResult);
	CString nowplaying;
	CEdit showtitle;
	afx_msg void OnEnChangeTitle();

	afx_msg void OnBnClickedNext();
	CString MuteSorting(CString pathsort[],int countsort[],int num);

	//재생변수 선언


	afx_msg void OnBnClickedPlaystop();
	CButton playstop;
	CSliderCtrl seeker;
	afx_msg void OnNMCustomdrawVolume(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl volume;
	afx_msg void OnNMReleasedcaptureSeeker(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit timer;
	afx_msg void OnTimer(UINT nIDEvent);
	int tempposition;
	CString tempstring;

	void playing(void);
	virtual void OnDraw(CDC* /*pDC*/);
	CButton feelcalm;
	CButton feelhappy;
	CButton feelexciting;
	CButton feelindaclub;

	CBitmap x1,x2,x3,x4;
	CButton next;
	CButton reset;
	CButton deletex;
	CButton addx;
};

#ifndef _DEBUG  // MuteView.cpp의 디버그 버전
inline CMuteDoc* CMuteView::GetDocument() const
   { return reinterpret_cast<CMuteDoc*>(m_pDocument); }
#endif


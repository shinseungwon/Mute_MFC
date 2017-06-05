
// MuteDoc.h : CMuteDoc 클래스의 인터페이스
//


#pragma once
#include "MuteSet.h"
#include "Popup.h"

class CMuteDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMuteDoc();
	DECLARE_DYNCREATE(CMuteDoc)

// 특성입니다.
public:
	CMuteSet m_MuteSet;

// 작업입니다.
public:
	
// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMuteDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	
	int feelnow;
	
	afx_msg void OnBnClickedFeel1();
	afx_msg void OnBnClickedFeel2();
	afx_msg void OnBnClickedFeel3();
	afx_msg void OnBnClickedFeel4();
	afx_msg void OnBnClickedPop1();
	afx_msg void OnBnClickedPop2();
	afx_msg void OnBnClickedPop3();
	afx_msg void OnBnClickedPop4();
};


// MuteDoc.h : CMuteDoc Ŭ������ �������̽�
//


#pragma once
#include "MuteSet.h"
#include "Popup.h"

class CMuteDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMuteDoc();
	DECLARE_DYNCREATE(CMuteDoc)

// Ư���Դϴ�.
public:
	CMuteSet m_MuteSet;

// �۾��Դϴ�.
public:
	
// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CMuteDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
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


// MuteDoc.cpp : CMuteDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Mute.h"
#endif

#include "MuteSet.h"
#include "MuteDoc.h"


#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMuteDoc

IMPLEMENT_DYNCREATE(CMuteDoc, CDocument)

BEGIN_MESSAGE_MAP(CMuteDoc, CDocument)
	ON_BN_CLICKED(IDC_FEEL1, &CMuteDoc::OnBnClickedFeel1)
	ON_BN_CLICKED(IDC_FEEL2, &CMuteDoc::OnBnClickedFeel2)
	ON_BN_CLICKED(IDC_FEEL3, &CMuteDoc::OnBnClickedFeel3)
	ON_BN_CLICKED(IDC_FEEL4, &CMuteDoc::OnBnClickedFeel4)
	ON_BN_CLICKED(IDC_POP1, &CMuteDoc::OnBnClickedPop1)
	ON_BN_CLICKED(IDC_POP2, &CMuteDoc::OnBnClickedPop2)
	ON_BN_CLICKED(IDC_POP3, &CMuteDoc::OnBnClickedPop3)
	ON_BN_CLICKED(IDC_POP4, &CMuteDoc::OnBnClickedPop4)
END_MESSAGE_MAP()


// CMuteDoc 생성/소멸

CMuteDoc::CMuteDoc()
	
	: feelnow(0)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMuteDoc::~CMuteDoc()
{
}

BOOL CMuteDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	
	return TRUE;
}



#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMuteDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMuteDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMuteDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMuteDoc 진단

#ifdef _DEBUG
void CMuteDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMuteDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMuteDoc 명령




void CMuteDoc::OnBnClickedFeel1()
{
	feelnow=1;
	
}


void CMuteDoc::OnBnClickedFeel2()
{
	feelnow=2;
}


void CMuteDoc::OnBnClickedFeel3()
{
	feelnow=3;
}


void CMuteDoc::OnBnClickedFeel4()
{
	feelnow=4;
}


void CMuteDoc::OnBnClickedPop1()
{
	feelnow=1;
}


void CMuteDoc::OnBnClickedPop2()
{
	feelnow=2;
}


void CMuteDoc::OnBnClickedPop3()
{
	feelnow=3;
}


void CMuteDoc::OnBnClickedPop4()
{
	feelnow=4;
}

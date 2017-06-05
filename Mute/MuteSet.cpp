
// MuteSet.cpp : CMuteSet 클래스의 구현
//

#include "stdafx.h"
#include "Mute.h"
#include "MuteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMuteSet 구현

// 코드 생성 위치 Saturday, May 23, 2015, 12:06 AM

IMPLEMENT_DYNAMIC(CMuteSet, CRecordset)

CMuteSet::CMuteSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Title = L"";
	m_Path = L"";
	m_PlayCount = 0;
	m_Feel=0;
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
CString CMuteSet::GetDefaultConnect()
{
	return _T("DSN=mute;DBQ=C:\\Users\\seungwon\\Documents\\Mute1.0\\Mute.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CMuteSet::GetDefaultSQL()
{
	return _T("[Music]");
}

void CMuteSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 및 RFX_Int() 같은 매크로는 데이터베이스의 필드
// 형식이 아니라 멤버 변수의 형식에 따라 달라집니다.
// ODBC에서는 자동으로 열 값을 요청된 형식으로 변환하려고 합니다
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Title]"), m_Title);
	RFX_Text(pFX, _T("[Path]"), m_Path);
	RFX_Long(pFX, _T("[PlayCount]"), m_PlayCount);
	RFX_Long(pFX, _T("[Feel]"), m_Feel);

}
/////////////////////////////////////////////////////////////////////////////
// CMuteSet 진단

#ifdef _DEBUG
void CMuteSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMuteSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


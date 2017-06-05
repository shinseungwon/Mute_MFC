
// MuteSet.cpp : CMuteSet Ŭ������ ����
//

#include "stdafx.h"
#include "Mute.h"
#include "MuteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMuteSet ����

// �ڵ� ���� ��ġ Saturday, May 23, 2015, 12:06 AM

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
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
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
// RFX_Text() �� RFX_Int() ���� ��ũ�δ� �����ͺ��̽��� �ʵ�
// ������ �ƴ϶� ��� ������ ���Ŀ� ���� �޶����ϴ�.
// ODBC������ �ڵ����� �� ���� ��û�� �������� ��ȯ�Ϸ��� �մϴ�
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Title]"), m_Title);
	RFX_Text(pFX, _T("[Path]"), m_Path);
	RFX_Long(pFX, _T("[PlayCount]"), m_PlayCount);
	RFX_Long(pFX, _T("[Feel]"), m_Feel);

}
/////////////////////////////////////////////////////////////////////////////
// CMuteSet ����

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


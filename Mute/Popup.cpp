// Popup.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Mute.h"
#include "Popup.h"
#include "afxdialogex.h"
#include "MuteView.h"


// CPopup ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPopup, CDialogEx)

CPopup::CPopup(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPopup::IDD, pParent)
{

}

CPopup::~CPopup()
{
}

void CPopup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPopup, CDialogEx)
	ON_BN_CLICKED(IDC_POP1, &CPopup::OnBnClickedPop1)
	ON_BN_CLICKED(IDC_POP2, &CPopup::OnBnClickedPop2)
	ON_BN_CLICKED(IDC_POP3, &CPopup::OnBnClickedPop3)
	ON_BN_CLICKED(IDC_POP4, &CPopup::OnBnClickedPop4)
END_MESSAGE_MAP()


// CPopup �޽��� ó�����Դϴ�.


void CPopup::OnBnClickedPop1()
{
	
	EndDialog(IDOK);
}


void CPopup::OnBnClickedPop2()
{
	EndDialog(IDOK);
}


void CPopup::OnBnClickedPop3()
{
	EndDialog(IDOK);
}


void CPopup::OnBnClickedPop4()
{
	EndDialog(IDOK);
}

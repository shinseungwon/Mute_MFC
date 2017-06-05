// FeelDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Mute.h"
#include "FeelDlg.h"
#include "afxdialogex.h"
#include "MuteDlg.h"


// CFeelDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFeelDlg, CDialogEx)

CFeelDlg::CFeelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFeelDlg::IDD, pParent)

	, feelnow(0)
{

}

CFeelDlg::~CFeelDlg()
{
}

void CFeelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	

}



BEGIN_MESSAGE_MAP(CFeelDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SAD, &CFeelDlg::OnBnClickedSad)
	ON_BN_CLICKED(IDC_CALM, &CFeelDlg::OnBnClickedCalm)
	ON_BN_CLICKED(IDC_BORING, &CFeelDlg::OnBnClickedBoring)
	ON_BN_CLICKED(IDC_EXCITED, &CFeelDlg::OnBnClickedExcited)
END_MESSAGE_MAP()


// CFeelDlg 메시지 처리기입니다.


void CFeelDlg::OnBnClickedExcited()
{
	feelnow = 1;
	EndDialog(IDOK);
}

void CFeelDlg::OnBnClickedSad()
{
	feelnow = 2;
	EndDialog(IDOK);
}


void CFeelDlg::OnBnClickedCalm()
{
	feelnow = 3;
	EndDialog(IDOK);
}


void CFeelDlg::OnBnClickedBoring()
{
	feelnow = 4;
	EndDialog(IDOK);
}




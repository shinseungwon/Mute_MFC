
// MuteView.cpp : CMuteView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Mute.h"
#endif

#include "MuteSet.h"
#include "MuteDoc.h"
#include "MuteView.h"
#include "Popup.h"
#include "stdlib.h"
#include "time.h"
#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum PlayFlag{
	FPLAY, FPAUSE, FRESUME,						//플레이 상태 (재생, 일시정지, 재개)
	FONSTOP, FOFFSTOP,							//정지 상태(정지버튼이 눌렸는지 여부)
	FNOREPECT, FONEREPECT, FALLREPECT,			//반복 재생 종류(반복없음, 한곡반복, 전체반복)
	FSEQ, FRAN									//랜덤재생 상태(랜덤재생 여부
};

int dwID;					//mci에서 사용

CString path;				//파일의 경로를 저장
CString name;				//파일명 저장

int g_listidx=0;			//리스트에서 현재 선택된 리스트의 인덱스저장
int g_playtime=0;			//슬라이드바로 재생 저장
int g_tend=0;				//현재 재생되는 노래의 총 재생시간을 저장
int g_listcnt=0;			//현재까지 총 추가되거나 열린 노래의 갯수
int g_stop=FOFFSTOP;		//스탑버튼이 눌렸는지의 유무
int g_repect=FNOREPECT;		//반복모드
int g_random=FSEQ;				//랜덤모드
int g_playbutt=FPLAY;		//재생버튼이 눌렸는지 여부
int paused=0;

MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;
MCI_GENERIC_PARMS mciGeneric;
// CMuteView

IMPLEMENT_DYNCREATE(CMuteView, CRecordView)

BEGIN_MESSAGE_MAP(CMuteView, CRecordView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMuteView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()

	ON_BN_CLICKED(IDC_FEEL1, &CMuteView::OnBnClickedFeel1)
	ON_BN_CLICKED(IDC_FEEL2, &CMuteView::OnBnClickedFeel2)
	ON_BN_CLICKED(IDC_FEEL3, &CMuteView::OnBnClickedFeel3)
	ON_BN_CLICKED(IDC_FEEL4, &CMuteView::OnBnClickedFeel4)


	ON_BN_CLICKED(IDC_DELETE, &CMuteView::OnBnClickedDelete)

	ON_NOTIFY(NM_CLICK, IDC_PLAYLIST, &CMuteView::OnNMClickPlaylist)
	ON_BN_CLICKED(IDC_ADD, &CMuteView::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_RESET, &CMuteView::OnBnClickedReset)

	ON_NOTIFY(NM_DBLCLK, IDC_PLAYLIST, &CMuteView::OnNMDblclkPlaylist)

	ON_BN_CLICKED(IDC_NEXT, &CMuteView::OnBnClickedNext)
	ON_BN_CLICKED(IDC_PLAYSTOP, &CMuteView::OnBnClickedPlaystop)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_VOLUME, &CMuteView::OnNMCustomdrawVolume)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SEEKER, &CMuteView::OnNMReleasedcaptureSeeker)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMuteView 생성/소멸

CMuteView::CMuteView()
	: CRecordView(CMuteView::IDD)
	
	, selectednow(0)
	, currentlist(0)
	, nowplaying(_T(""))
{
	m_pSet = NULL;
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMuteView::~CMuteView()
{
}

void CMuteView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	// 컨트롤을 데이터베이스 필드에 '연결'하기 위해 여기에 DDX_Field* 함수를 삽입할 수 있습니다. 예:
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// 자세한 내용은 MSDN 및 ODBC 샘플을 참조하십시오.
	DDX_Control(pDX, IDC_PLAYLIST, playlist);

	DDX_Control(pDX, IDC_TITLE, showtitle);

	DDX_Control(pDX, IDC_PLAYSTOP, playstop);
	DDX_Control(pDX, IDC_SEEKER, seeker);
	DDX_Control(pDX, IDC_VOLUME, volume);
	DDX_Control(pDX, IDC_TIME, timer);
	DDX_Control(pDX, IDC_FEEL1, feelcalm);
	DDX_Control(pDX, IDC_FEEL2, feelhappy);
	DDX_Control(pDX, IDC_FEEL3, feelexciting);
	DDX_Control(pDX, IDC_FEEL4, feelindaclub);
	DDX_Control(pDX, IDC_NEXT, next);
	DDX_Control(pDX, IDC_RESET, reset);
	DDX_Control(pDX, IDC_DELETE, deletex);
	DDX_Control(pDX, IDC_ADD, addx);
}

BOOL CMuteView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CRecordView::PreCreateWindow(cs);
}

void CMuteView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_MuteSet;
	CRecordView::OnInitialUpdate();
	volume.SetRange(0,16);
	volume.SetPos(8);
	AddColumn();	
	AddMusic(0);
	playlist.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	
	x1.LoadBitmapW(IDB_CALM);
	feelcalm.SetBitmap(x1);
	x2.LoadBitmapW(IDB_HAPPY);
	feelhappy.SetBitmap(x2);
	x3.LoadBitmapW(IDB_EXCITING);
	feelexciting.SetBitmap(x3);
	x4.LoadBitmapW(IDB_INDACLUB);
	feelindaclub.SetBitmap(x4);

	CBitmap p0,n0,r0,d0,a0;	
	p0.LoadBitmapW(IDB_PLAYBLACK);
	n0.LoadBitmapW(IDB_NEXTBLACK);
	r0.LoadBitmapW(IDB_RESETBLACK);
	d0.LoadBitmapW(IDB_DELETEBLACK);
	a0.LoadBitmapW(IDB_ADDBLACK);
	playstop.SetBitmap(p0);
	next.SetBitmap(n0);
	reset.SetBitmap(r0);
	deletex.SetBitmap(d0);
	addx.SetBitmap(a0);	

}


// CMuteView 인쇄


void CMuteView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMuteView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMuteView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
	
}

void CMuteView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMuteView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMuteView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMuteView 진단

#ifdef _DEBUG
void CMuteView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CMuteView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CMuteDoc* CMuteView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMuteDoc)));
	return (CMuteDoc*)m_pDocument;
}
#endif //_DEBUG


// CMuteView 데이터베이스 지원
CRecordset* CMuteView::OnGetRecordset()
{
	return m_pSet;
}

void CMuteView::AddColumn(void)
{
	CRect rect;
	playlist.GetClientRect(&rect);
	playlist.InsertColumn(0,_T("ID"),LVCFMT_LEFT,0);
	playlist.InsertColumn(1,_T("Title"),LVCFMT_RIGHT,rect.Width()-51);
	playlist.InsertColumn(2,_T("Count"),LVCFMT_RIGHT,50);
}

void CMuteView::AddMusic(int x)
{
	CMuteSet rsSet(m_pSet->m_pDatabase);
	CString order;
	order.Format(_T("select * from Music WHERE Feel=%d order by PlayCount desc"),x);
	rsSet.Open(CRecordset::dynaset,order);
	playlist.DeleteAllItems();
	int i=0;
	CString strTemp;
	while(rsSet.IsEOF()==FALSE){
		strTemp.Format(_T("%4d"),rsSet.m_ID);
		playlist.InsertItem(i,strTemp,0);
		playlist.SetItemText(i,1,rsSet.m_Title);
		strTemp.Format(_T("%4d"),rsSet.m_PlayCount);
		playlist.SetItemText(i,2,strTemp);
		rsSet.MoveNext();
		i++;
	}
	rsSet.Close();
}


void CMuteView::OnBnClickedFeel1()
{
	Invalidate(true);
	AddMusic(1);
	currentlist=1;
	OnBnClickedNext();
	CBitmap y1;
	y1.LoadBitmapW(IDB_CALM2);
	feelcalm.SetBitmap(y1);
	feelhappy.SetBitmap(x2);
	feelexciting.SetBitmap(x3);
	feelindaclub.SetBitmap(x4);
	CBitmap p1,n1,r1,d1,a1;
	g_playbutt=FPLAY;
	p1.LoadBitmapW(IDB_PAUSEORANGE);
	n1.LoadBitmapW(IDB_NEXTORANGE);
	r1.LoadBitmapW(IDB_RESETORANGE);
	d1.LoadBitmapW(IDB_DELETEORANGE);
	a1.LoadBitmapW(IDB_ADDORANGE);
	playstop.SetBitmap(p1);
	next.SetBitmap(n1);
	reset.SetBitmap(r1);
	deletex.SetBitmap(d1);
	addx.SetBitmap(a1);
	volume.SetPos(12);
}


void CMuteView::OnBnClickedFeel2()
{
	Invalidate(true);
	AddMusic(2);
	currentlist=2;
	OnBnClickedNext();
	CBitmap y2;
	y2.LoadBitmapW(IDB_HAPPY2);
	feelcalm.SetBitmap(x1);
	feelhappy.SetBitmap(y2);
	feelexciting.SetBitmap(x3);
	feelindaclub.SetBitmap(x4);
	CBitmap p2,n2,r2,d2,a2;
	g_playbutt=FPLAY;
	p2.LoadBitmapW(IDB_PAUSEPINK);
	n2.LoadBitmapW(IDB_NEXTPINK);
	r2.LoadBitmapW(IDB_RESETPINK);
	d2.LoadBitmapW(IDB_DELETEPINK);
	a2.LoadBitmapW(IDB_ADDPINK);
	playstop.SetBitmap(p2);
	next.SetBitmap(n2);
	reset.SetBitmap(r2);
	deletex.SetBitmap(d2);
	addx.SetBitmap(a2);
	volume.SetPos(8);
}


void CMuteView::OnBnClickedFeel3()
{
	Invalidate(true);
	AddMusic(3);
	currentlist=3;
	OnBnClickedNext();
	CBitmap y3;
	y3.LoadBitmapW(IDB_EXCITING2);
	feelcalm.SetBitmap(x1);
	feelhappy.SetBitmap(x2);
	feelexciting.SetBitmap(y3);
	feelindaclub.SetBitmap(x4);
	CBitmap p3,n3,r3,d3,a3;
	g_playbutt=FPLAY;
	p3.LoadBitmapW(IDB_PAUSEBLUE);
	n3.LoadBitmapW(IDB_NEXTBLUE);
	r3.LoadBitmapW(IDB_RESETBLUE);
	d3.LoadBitmapW(IDB_DELETEBLUE);
	a3.LoadBitmapW(IDB_ADDBLUE);
	playstop.SetBitmap(p3);
	next.SetBitmap(n3);
	reset.SetBitmap(r3);
	deletex.SetBitmap(d3);
	addx.SetBitmap(a3);
	volume.SetPos(4);
}


void CMuteView::OnBnClickedFeel4()
{
	Invalidate(true);
	AddMusic(4);
	currentlist=4;
	OnBnClickedNext();
	CBitmap y4;
	y4.LoadBitmapW(IDB_INDACLUB2);
	feelcalm.SetBitmap(x1);
	feelhappy.SetBitmap(x2);
	feelexciting.SetBitmap(x3);
	feelindaclub.SetBitmap(y4);
	CBitmap p4,n4,r4,d4,a4;
	g_playbutt=FPLAY;
	p4.LoadBitmapW(IDB_PAUSERED);
	n4.LoadBitmapW(IDB_NEXTRED);
	r4.LoadBitmapW(IDB_RESETRED);
	d4.LoadBitmapW(IDB_DELETERED);
	a4.LoadBitmapW(IDB_ADDRED);
	playstop.SetBitmap(p4);
	next.SetBitmap(n4);
	reset.SetBitmap(r4);
	deletex.SetBitmap(d4);
	addx.SetBitmap(a4);
	volume.SetPos(0);
}

void CMuteView::OnBnClickedDelete()
{
	CMuteSet rsSet(m_pSet->m_pDatabase);
	CString order;
	order.Format(_T("select * from Music WHERE ID=%d"),selectednow);
	rsSet.Open(CRecordset::dynaset,order);
	rsSet.Delete();
	AddMusic(currentlist);
}

void CMuteView::OnNMClickPlaylist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	NM_LISTVIEW* pListView = (NM_LISTVIEW*)pNMHDR;
    int nSel = pListView->iItem;
	int x;
	   if( nSel != -1 )
    {
    	CString temp=playlist.GetItemText( nSel, 0 );
		x = _ttoi(temp);
		selectednow=x;
    }
}

void CMuteView::OnBnClickedAdd()
{

	if(currentlist==0){
		AfxMessageBox(_T("Select Playlist First"));
	}
	else{
	CString szFilters = _T("Mp3 File(*.mp3)|*.mp3|");
	CFileDialog fileDlg(TRUE,_T("mp3"),_T("*.mp3"),OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY | OFN_FILEMUSTEXIST ,szFilters,NULL);
	CMuteSet rsSet(m_pSet->m_pDatabase);
	CString pathName, fileName;
		
	if(fileDlg.DoModal()==IDOK){
		POSITION pos=fileDlg.GetStartPosition();
		while(pos){
			pathName=fileDlg.GetNextPathName(pos);
			fileName= pathName.Right(pathName.GetLength()-fileDlg.GetPathName().GetLength()-1);

			if(fileName==""){													
			pathName = fileDlg.GetPathName();
			fileName = fileDlg.GetFileName();
			m_pSet->AddNew(); 
			m_pSet->m_Title=fileName;
			m_pSet->m_Path=pathName;
			m_pSet->m_Feel=currentlist;
			m_pSet->Update();
			m_pSet->Requery();
			break;
		}		
			m_pSet->AddNew(); 
			m_pSet->m_Title=fileName;
			m_pSet->m_Path=pathName;
			m_pSet->m_Feel=currentlist;			
			m_pSet->Update();
			m_pSet->Requery();
		}
	}
	AddMusic(currentlist);
	}
}

void CMuteView::OnBnClickedReset()
{
	CMuteSet rsSet(m_pSet->m_pDatabase);
	CString order;
	m_pSet->m_strFilter.Format(_T("ID=%d"),selectednow);
	m_pSet->Requery();
	m_pSet->Edit();
	m_pSet->m_PlayCount=0;
	m_pSet->Update();
	m_pSet->Requery();
	AddMusic(currentlist);
}

void CMuteView::OnNMDblclkPlaylist(NMHDR *pNMHDR, LRESULT *pResult)
{
	CMuteSet rsSet(m_pSet->m_pDatabase);
	CString order;
	m_pSet->m_strFilter.Format(_T("ID=%d"),selectednow);
	m_pSet->Requery();
	m_pSet->Edit();
	m_pSet->m_PlayCount++;
	m_pSet->Update();
	m_pSet->Requery();

	order.Format(_T("select * from Music WHERE ID=%d"),selectednow);
	rsSet.Open(CRecordset::dynaset,order);
	nowplaying=rsSet.m_Path;
	showtitle.SetWindowTextW(nowplaying);
	AddMusic(currentlist);
	mciOpen.lpstrElementName = nowplaying;				
	playing();
}

void CMuteView::OnBnClickedNext()
{
	CString pathsort[100];
	int countsort[100];
	int num=0;
	CMuteSet rsSet(m_pSet->m_pDatabase);
	CString order;
	order.Format(_T("select * from Music WHERE Feel=%d order by PlayCount desc"),currentlist);
	rsSet.Open(CRecordset::dynaset,order);
	while(rsSet.IsEOF()==FALSE){
		pathsort[num]=rsSet.m_Path;
		countsort[num]=rsSet.m_PlayCount;
		rsSet.MoveNext();
		num++;
	}
	if(num>2){
	nowplaying=MuteSorting(pathsort,countsort,num);
	showtitle.SetWindowTextW(nowplaying);
	playing();
	}
	else
	{
		AfxMessageBox(_T("Add More Songs"));
	}
}

CString CMuteView::MuteSorting(CString pathsort[], int countsort[],int num)
{
	srand(time(NULL));
	int dice1,dice2;
	int result;
	dice1=rand()%10;
		dice2=num;
		dice2=rand()%(int)(num/3);
	if(dice1<5){
		result=dice2;
	}
	else if(dice1<8){
		result=(int)(num/3)+dice2;
	}
	else{
		result=(int)(2*num/3)+dice2;
	}
	return pathsort[result];
}

void CMuteView::OnBnClickedPlaystop()
{
	mciOpen.lpstrElementName = nowplaying;	
	CBitmap pause,play;
	switch(g_playbutt) {
	case FPLAY:
		
		if(currentlist==1)
			pause.LoadBitmapW(IDB_PAUSEORANGE);
		else if(currentlist==2)
			pause.LoadBitmapW(IDB_PAUSEPINK);
		else if(currentlist==3)
			pause.LoadBitmapW(IDB_PAUSEBLUE);
		else if(currentlist==4)
			pause.LoadBitmapW(IDB_PAUSERED);

		playstop.SetBitmap(pause);
		playing();
			g_playtime=tempposition;
			seeker.SetPos(tempposition);		
			g_playbutt=FPAUSE;
		break;
	
	case FPAUSE:
			
		if(currentlist==1)
			play.LoadBitmapW(IDB_PLAYORANGE);
		else if(currentlist==2)
			play.LoadBitmapW(IDB_PLAYPINK);
		else if(currentlist==3)
			play.LoadBitmapW(IDB_PLAYBLUE);
		else if(currentlist==4)
			play.LoadBitmapW(IDB_PLAYRED);
	
		playstop.SetBitmap(play);
		mciSendCommand(dwID,MCI_PAUSE,MCI_WAIT,(DWORD)&mciGeneric);
		tempposition=g_playtime;
		timer.GetWindowText(tempstring);
		paused=1;
		KillTimer(1);
		g_playbutt=FPLAY;
		break;
	}
}

void CMuteView::playing(void)
{
		mciOpen.lpstrElementName = nowplaying;	
		mciSendCommand(dwID,MCI_PAUSE,MCI_WAIT,(DWORD)&mciGeneric);
		g_playbutt=FPAUSE;
		playstop.SetWindowText(_T("||"));
		mciOpen.lpstrDeviceType = _T("mpegvideo");
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE|MCI_OPEN_ELEMENT,(DWORD)&mciOpen);
		dwID = mciOpen.wDeviceID;
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY,(DWORD)&mciPlay);
		MCI_STATUS_PARMS mciStatusParms;
		mciStatusParms.dwItem = MCI_FORMAT_HMS;												
		mciSendCommand(dwID, MCI_STATUS, MCI_STATUS_ITEM ,(DWORD)(LPVOID)&mciStatusParms);
		seeker.SetRange(0,(mciStatusParms.dwReturn)/1000);						
		g_tend = mciStatusParms.dwReturn/1000;					
		g_playtime=0;
		seeker.SetPos(0);
		SetTimer(1,1000,NULL);	
}

void CMuteView::OnTimer(UINT nIDEvent)
{
    g_playtime += 1;
	seeker.SetPos(g_playtime);
	int min,sec;
	CString printtime;
	min=(int)g_playtime/60;
	sec=(int)g_playtime%60;
	printtime.Format(_T("%d:%d"),min,sec);
	timer.SetWindowTextW(printtime);
}

void CMuteView::OnNMReleasedcaptureSeeker(NMHDR *pNMHDR, LRESULT *pResult)
{
	int pos;
	MCI_PLAY_PARMS mciPlay;
    pos = seeker.GetPos();												
	seeker.SetPos(pos);													
	g_playtime = pos;															
	mciPlay.dwFrom = pos*1000;													
	mciSendCommand(dwID, MCI_PLAY, MCI_FROM,(DWORD)(LPVOID)&mciPlay);
	SetTimer(1,1000,NULL);
	seeker.SetTicFreq(1);
	int min,sec;
	CString printtime;
	min=(int)pos/60;
	sec=(int)pos%60;
	printtime.Format(_T("%d:%d"),min,sec);
	timer.SetWindowTextW(printtime);
	*pResult = 0;
}


void CMuteView::OnNMCustomdrawVolume(NMHDR *pNMHDR, LRESULT *pResult)
{
	int pos;
    pos = 16-volume.GetPos(); 
	DWORD m_nVolume;
	m_nVolume = 0xfff* pos;
	m_nVolume = m_nVolume << 16;
	m_nVolume = m_nVolume + 0xfff* pos;
	waveOutSetVolume(NULL , m_nVolume);
	*pResult = 0;
}

void CMuteView::OnDraw(CDC* pDC)
{
	CMuteDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
		return;
	
	CRect rect;
	GetClientRect(&rect);
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	BITMAP bmpinfo;
	CBitmap bitmap,listbitmap;
	if(currentlist==1){
		bitmap.LoadBitmapW(IDB_ORANGE);
		listbitmap.LoadBitmapW(IDB_ORANGEP);
		playlist.SetBkImage(listbitmap);
	}
	else if(currentlist==2){
		bitmap.LoadBitmapW(IDB_PINK);
		listbitmap.LoadBitmapW(IDB_PINKP);
		playlist.SetBkImage(listbitmap);
	}

	else if(currentlist==3){
		bitmap.LoadBitmapW(IDB_BLUE);
		listbitmap.LoadBitmapW(IDB_BLUEP);
		playlist.SetBkImage(listbitmap);
	}
	else if(currentlist==4){
		bitmap.LoadBitmapW(IDB_RED);
		listbitmap.LoadBitmapW(IDB_REDP);
		playlist.SetBkImage(listbitmap);
	}
	else if(currentlist==0){
		
		bitmap.LoadBitmapW(IDB_BLACK);
		listbitmap.LoadBitmapW(IDB_BLACKP);
		playlist.SetBkImage(listbitmap);
	}
	bitmap.GetBitmap(&bmpinfo);
	CBitmap *pOldBitmap=(CBitmap *)MemDC.SelectObject(&bitmap);
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&MemDC,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
}
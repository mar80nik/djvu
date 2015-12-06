// djvuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "djvu.h"
#include "djvuDlg.h"
#include "searchrsltdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum {DlgSet=0,DlgGet=1};
_PagesItem PagesItem;
_FileNameItem FileNameItem;
_OutDirItem OutDirItem;
_FormatItem FormatItem;
_LayerItem LayerItem;
//-----------------------

UINT Collect_Function2(LPVOID pParam);
void CollectFiles(CString InputDir,CStringArray &Files);


CMutex DjvuBundleRunnning;

CString _PagesItem::GetString()
{	
	CString T,T1;
	CDjvuDlg *dlg; dlg=(CDjvuDlg *)((CDjvuApp*)AfxGetApp())->m_pMainWnd;

	if(dlg->PagesCheck)
	{
//		int min=dlg->m_MinPage, max=dlg->m_MaxPage;
		T=CString("--page-range=")+dlg->PagesString;						
	}
	else T="--page-range=1-";	

	return T;
}

CString _FileNameItem::GetString()
{
	CDjvuDlg *dlg; dlg=(CDjvuDlg *)((CDjvuApp*)AfxGetApp())->m_pMainWnd;

	return '"'+dlg->InputFile+'"';	
	//return '"'+CString("F:\\1.djvu")+'"';
}

CString _OutDirItem::GetString()
{
	CDjvuDlg *dlg; dlg=(CDjvuDlg *)((CDjvuApp*)AfxGetApp())->m_pMainWnd;

	return '"'+dlg->OutputDir+'"';
	//return '"'+CString("F:\\printed images")+'"';
}

CString _FormatItem::GetString()
{
	CDjvuDlg *dlg; dlg=(CDjvuDlg *)((CDjvuApp*)AfxGetApp())->m_pMainWnd;

	return "--output-format="+dlg->FormatStr; 
	//return "--output-format=bmp"; 
}

CString _LayerItem::GetString()
{
	CDjvuDlg *dlg; dlg=(CDjvuDlg *)((CDjvuApp*)AfxGetApp())->m_pMainWnd;

	return CString("--layer=")+dlg->Layers; 
}


/////////////////////////////////////////////////////////////////////////////
// CDjvuDlg dialog

CDjvuDlg::CDjvuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDjvuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDjvuDlg)
	InputFile = _T("");
	OutputDir = _T("F:\\printed images");
	PagesCheck = FALSE;
	m_MaxPage = 5;
	temp = _T("");
	Layers = _T("");
	PagesString = _T("");
	FormatStr = _T("");
	InputDir = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	lpItemDList=NULL;
}

void CDjvuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDjvuDlg)
	DDX_Control(pDX, IDC_LIST1, CollectInfo);
	DDX_Control(pDX, IDC_COMBO2, FormatCombo);
	DDX_Control(pDX, IDC_LIST3, ListBox1);
	DDX_Control(pDX, IDC_BUTTON4, StopButton);
	DDX_Control(pDX, IDC_BUTTON3, StartButton);
	DDX_Control(pDX, IDC_COMBO1, LayersCombo);
	DDX_Control(pDX, IDC_EDIT3, MinPage);
	DDX_Text(pDX, IDC_EDIT1, InputFile);
	DDX_Text(pDX, IDC_EDIT2, OutputDir);
	DDX_Check(pDX, IDC_CHECK1, PagesCheck);
	DDX_CBString(pDX, IDC_COMBO1, Layers);
	DDX_Text(pDX, IDC_EDIT3, PagesString);
	DDX_CBString(pDX, IDC_COMBO2, FormatStr);
	DDX_Text(pDX, IDC_EDIT4, InputDir);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDjvuDlg, CDialog)
	//{{AFX_MSG_MAP(CDjvuDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_BUTTON3, OnStart)
	ON_BN_CLICKED(IDC_BUTTON4, OnStop)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON5, OnInputDir)
	ON_BN_CLICKED(IDC_BUTTON6, OnCollect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDjvuDlg message handlers


BOOL CDjvuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	LayersCombo.SetCurSel(0); FormatCombo.SetCurSel(0);
	UpdateData(DlgGet);
	
	//ListBox1.SetHorizontalExtent(400);

	// TODO: Add extra initialization here
	Items.Add(&PagesItem);
	Items.Add(&FormatItem);
	Items.Add(&LayerItem);	
	Items.Add(&FileNameItem);
	Items.Add(&OutDirItem);

	OnStopUI();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDjvuDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDjvuDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDjvuDlg::OnButton1() 
{
	CFileDialog Dlg1(true,NULL,NULL,NULL,"Djvu files (*.djvu)|*.djvu||");
	if(Dlg1.DoModal())
	{
		InputFile=Dlg1.GetPathName();
		UpdateData(DlgSet);
	}
	else
	{
		
		
	}

	
}

void CDjvuDlg::OnButton2() 
{
	BROWSEINFO bi= {m_hWnd, NULL, NULL, "Please, choose the folder...",
					BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_BROWSEFORCOMPUTER,
					NULL, NULL, 0};
		
	LPCITEMIDLIST lpItemDList;
	if(!(lpItemDList=SHBrowseForFolder(&bi)))
	{
	}
	else
	{
		char buff[200];
		SHGetPathFromIDList(lpItemDList, buff); // 
		OutputDir=buff; UpdateData(DlgSet);
	}	
	
	
}

void CDjvuDlg::OnCheck1() 
{
	UpdateData(DlgGet);
	if(PagesCheck)
	{
		MinPage.EnableWindow(true);
		//MaxPage.EnableWindow(true);
	}
	else
	{
		MinPage.EnableWindow(false);
		//MaxPage.EnableWindow(false);
	}

	
}

void CDjvuDlg::OnStart() 
{
	CString T; 
	UpdateData(DlgGet);
	for(int i=0;i<Items.GetSize();i++)
	{
		if(Items[i]->IsChecked())
		{			
			T+=Items[i]->GetString();			
		}	
		if(i<Items.GetSize()-1) T+=" ";
	}
	int a=5;
	
	CString T1='"'+CString("g:\\My software\\_IMAGE\\_DJVU\\DjVu Small v0.3\\bin\\djvudecode.exe")+'"';

	T=T1+CString(" ")+T;

	STARTUPINFO si;  GetStartupInfo(&si);
	PROCESS_INFORMATION &pi1=MAINAPP->pi;	

	if(!CreateProcess(NULL, (char *)LPCSTR(T), NULL, NULL, FALSE, DETACHED_PROCESS | CREATE_SUSPENDED | IDLE_PRIORITY_CLASS, NULL, NULL, &si, &pi1)) 
	{
		int a=5;
	}
	else
	{
		temp=T; UpdateData(DlgSet); 
		ListBox1.AddString(T); UpdateList();

		MAINAPP->StopThread=0; 
		CSingleLock Lock1(&(MAINAPP->StopMutex)); Lock1.Lock();
		MAINAPP->m_pMainWnd->SetWindowText("Working"); OnStartUI();
		ResumeThread(pi1.hThread);
		MAINAPP->StopThread=AfxBeginThread(Function1,NULL);		
	}
	int b=5;
		
}


void CDjvuDlg::OnStop() 
{
	MAINAPP->StopProcess();
}


UINT Function1(LPVOID pParam)
{
	HANDLE arr[2]; arr[0]=MAINAPP->pi.hThread; arr[1]=MAINAPP->StopMutex;
	WaitForMultipleObjects(2,arr,false,INFINITE);
	MAINAPP->PostThreadMessage(STOP_PROCESS,0,0);
	return 0;
}

void CDjvuDlg::OnStartUI()
{
	StartButton.EnableWindow(false);
	StopButton.EnableWindow(true);
}

void CDjvuDlg::OnStopUI()
{
	StartButton.EnableWindow(true);
	StopButton.EnableWindow(false);
}

void CDjvuDlg::UpdateList()
{
	CRect r; int w,w1; w=w1=0; CString T;
	CClientDC dc(this);
	CFont * pFont = dc.SelectObject(ListBox1.GetFont());
	
	for(int i=0;i<ListBox1.GetCount();i++)
	{
		ListBox1.GetText(i,T);
		w1=(dc.GetTextExtent(T)).cx;
		if(w1>w) w=w1;
	}
	ListBox1.GetClientRect(r);
	ListBox1.SetHorizontalExtent(w+10);
	dc.SelectObject(pFont);
}

void CDjvuDlg::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	UpdateData();
	char buf[1000];
	DragQueryFile(hDropInfo,0,buf,1000);
	InputFile=CString(buf); UpdateData(DlgSet);

	CDialog::OnDropFiles(hDropInfo);
}

void CDjvuDlg::OnInputDir() 
{
	BROWSEINFO bi= {m_hWnd, NULL, NULL, "Please, choose the folder...",
					BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_BROWSEFORCOMPUTER,
					NULL, NULL, 0};

	
	if(!(lpItemDList=SHBrowseForFolder(&bi)))
	{
	}
	else
	{
		char buff[200];
		SHGetPathFromIDList(lpItemDList, buff); // 
		InputDir=buff; UpdateData(DlgSet);
	}		
}

void CDjvuDlg::OnCollect() 
{		
	UpdateData();
	MAINAPP->m_pMainWnd->SetWindowText("Working"); 
	MAINAPP->SRDlg2.DoModal();
}

UINT Collect_Function2(LPVOID pParam)
{
	CSingleLock Lock1(&(MAINAPP->StopMutex)); 
	Lock1.Lock();
	MAINAPP->StopThread=AfxBeginThread(Function1,NULL);	
	int i; CString Path;

	for(i=0;i<MAINAPP->Directories.GetSize();i++)
	{
		Path=MAINAPP->Directories[i]; CStringArray *t=MAINAPP->AllFiles[i];
		CollectFiles(Path,*t);				
		delete t;	
	}
	MAINAPP->AllFiles.RemoveAll();
	Lock1.Unlock();
	return 0;
}

void SearchRsltDlg::OnProced() 
{
	MAINAPP->m_pMainWnd->SetWindowText("Working"); 
	MAINAPP->StopThread=AfxBeginThread(Collect_Function2,NULL);	
	Proceed.EnableWindow(false);
}

void CollectFiles(CString InputDir,CStringArray &Files)
{
	if(!(Files.GetSize())) return;

	CDjvuDlg *parent=(CDjvuDlg *)(MAINAPP->m_pMainWnd);
	SearchRsltDlg *dlg=(SearchRsltDlg *)(&(MAINAPP->SRDlg2));
	CString T,ListFile=InputDir+"\\list.txt";
	CString name,OutFile, OutPath; 
	int i,j; j=InputDir.ReverseFind('\\'); 
	name=InputDir.Right(InputDir.GetLength()-j-1);
	OutPath=InputDir.Left(j);
	OutFile.Format("%s\\%s_$$$.djvu",OutPath,name);

	CFile list; char buf[2]; buf[0]=0x0d; buf[1]=0x0a;
	list.Open(ListFile,CFile::modeCreate | CFile::modeWrite);
	for(i=0;i<Files.GetSize();i++)
	{
		T=InputDir+"\\"+Files[i];
		list.Write(LPCSTR(T),T.GetLength()); list.Write(buf,2);
	}
	list.Close();
	
	
	T.Format("%cdjvubundle.exe%c --files=%c%s%c %c%s%c",34,34,34,ListFile,34,34,OutFile,34);
	STARTUPINFO si;  GetStartupInfo(&si); PROCESS_INFORMATION &pi1=MAINAPP->pi;	
	if(CreateProcess(NULL, (char *)LPCSTR(T), NULL, NULL, FALSE, DETACHED_PROCESS | CREATE_SUSPENDED | IDLE_PRIORITY_CLASS, NULL, NULL, &si, &pi1)) 
	{
		ResumeThread(pi1.hThread);
		WaitForSingleObject(pi1.hThread,INFINITE);

		HANDLE SearchHandle;
		WIN32_FIND_DATA FindFileData;
		if( (SearchHandle=FindFirstFile(LPCSTR(OutFile),&FindFileData) )!=INVALID_HANDLE_VALUE)
		{
			T.Format("%d files bundled SUCSESFULLY",Files.GetSize()); dlg->CollectInfo.AddString(T);
			T.Format("%s",OutFile); dlg->CollectInfo.AddString(T);
			for(i=0;i<Files.GetSize();i++)  {T=InputDir+"\\"+Files[i];DeleteFile(T);}			
			DeleteFile(ListFile);	
		}
		else
		{
			T.Format("There was an ERROR"); dlg->CollectInfo.AddString(T);		
		}		
	}	
}

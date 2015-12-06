#include "stdafx.h"
#include "djvu.h"
#include "SearchRsltDlg.h"
#include "djvuDlg.h"

UINT Collect_Function(LPVOID pParam);
int SearchDirectories(CString,CStringArray&);
int SearchFiles(CString InputDir,CStringArray &Files);

/////////////////////////////////////////////////////////////////////////////
// SearchRsltDlg dialog


SearchRsltDlg::SearchRsltDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SearchRsltDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SearchRsltDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SearchRsltDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SearchRsltDlg)
	DDX_Control(pDX, IDC_BUTTON2, Cancel);
	DDX_Control(pDX, IDC_BUTTON1, Proceed);
	DDX_Control(pDX, IDC_LIST1, CollectInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SearchRsltDlg, CDialog)
	//{{AFX_MSG_MAP(SearchRsltDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnProced)
	ON_BN_CLICKED(IDC_BUTTON2, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SearchRsltDlg message handlers

BOOL SearchRsltDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	Proceed.EnableWindow(false);
	Cancel.EnableWindow(false);

	MAINAPP->StopThread=AfxBeginThread(Collect_Function,NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void SearchRsltDlg::OnCancel() 
{
	for(int i=0;i<MAINAPP->AllFiles.GetSize();i++)
	{
		CStringArray *t=MAINAPP->AllFiles[i]; delete t;	
	}
	MAINAPP->AllFiles.RemoveAll();

	OnOK();	
}

UINT Collect_Function(LPVOID pParam)
{
	CSingleLock Lock1(&(MAINAPP->StopMutex)); 
	Lock1.Lock();
	MAINAPP->StopThread=AfxBeginThread(Function1,NULL);	

	CStringArray NewDirs,TempDirs, *Files; int i,dir,files;	
	CString Path,T; 

	CDjvuDlg *parent=(CDjvuDlg *)(MAINAPP->m_pMainWnd);
	SearchRsltDlg *dlg=(SearchRsltDlg *)(&(MAINAPP->SRDlg2));

	MAINAPP->Directories.RemoveAll(); NewDirs.Add(parent->InputDir);

	for(i=0;i<NewDirs.GetSize();i++)
	{
		Path=NewDirs[i]; Files=new CStringArray();
		files=SearchFiles(Path,*Files); 
		if(files)
		{
			MAINAPP->Directories.Add(Path); MAINAPP->AllFiles.Add(Files);
		}
		else
		{
			delete Files;		
		}
		TempDirs.RemoveAll(); dir=SearchDirectories(Path,TempDirs); 	
		for(int j=0;j<TempDirs.GetSize();j++) NewDirs.Add(TempDirs[j]);

		T.Format("Searching at %s",Path); dlg->CollectInfo.AddString(T);	
		if(files)
		{T.Format("Found %d files",files); dlg->CollectInfo.AddString(T);}	
		if(dir)
		{T.Format("Found %d directories",dir); dlg->CollectInfo.AddString(T);}
	}		
	Lock1.Unlock();
	dlg->Proceed.EnableWindow(); dlg->Cancel.EnableWindow();
	return 0;
}

int SearchFiles(CString InputDir,CStringArray &Files)
{
	CString T,SearchPattern=InputDir+"\\*.djvu"; HANDLE SearchHandle;
	WIN32_FIND_DATA FindFileData;
	if( (SearchHandle=FindFirstFile(LPCSTR(SearchPattern),&FindFileData) )!=INVALID_HANDLE_VALUE)
	{

		T=FindFileData.cFileName; Files.Add(T);

		while(FindNextFile(SearchHandle,&FindFileData))
		{
			T=FindFileData.cFileName; Files.Add(T);			
		}
		FindClose(SearchHandle);
	}	
	return Files.GetSize();
}

int SearchDirectories(CString InputDir,CStringArray &Directories)
{
	HANDLE SearchHandle; WIN32_FIND_DATA FindFileData;
	CString T,SearchPattern=InputDir+"\\*";	
	if( (SearchHandle=FindFirstFile(LPCSTR(SearchPattern),&FindFileData) )!=INVALID_HANDLE_VALUE)
	{

		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{			
			T=FindFileData.cFileName; 
			if(T!="." && T!="..") 
				Directories.Add(InputDir+"\\"+T);
		}

		while(FindNextFile(SearchHandle,&FindFileData))
		{
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				T=FindFileData.cFileName; 
				if(T!="." && T!="..") 
					Directories.Add(InputDir+"\\"+T);
			}
		}
		FindClose(SearchHandle);
	}	
	return Directories.GetSize();
}
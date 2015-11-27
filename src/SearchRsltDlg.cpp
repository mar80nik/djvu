// SearchRsltDlg.cpp : implementation file
//

#include "stdafx.h"
#include "djvu.h"
#include "SearchRsltDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

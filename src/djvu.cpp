// djvu.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "djvu.h"
#include "djvuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDjvuApp

BEGIN_MESSAGE_MAP(CDjvuApp, CWinApp)
	//{{AFX_MSG_MAP(CDjvuApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
	ON_THREAD_MESSAGE( STOP_PROCESS, OnStopProcess )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDjvuApp construction

CDjvuApp::CDjvuApp() : Lock1(&(StopMutex))
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDjvuApp object

CDjvuApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDjvuApp initialization

BOOL CDjvuApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CDjvuDlg dlg;
	m_pMainWnd = &dlg;

	//Lock1.Lock();


	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.


	return FALSE;
}



//--page-range="1-5"


int CDjvuApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	TerminateThread(pi.hThread,1);

	return CWinApp::ExitInstance();
}

void CDjvuApp::StopProcess()
{
	TerminateThread(pi.hThread,1);
	Lock1.Unlock();	
}

void CDjvuApp::OnStopProcess( UINT u, LONG l)
{
	//Lock1.Unlock();
	m_pMainWnd->SetWindowText("Idle");
	CDjvuDlg *dlg=(CDjvuDlg *)m_pMainWnd;
	dlg->OnStopUI();
}
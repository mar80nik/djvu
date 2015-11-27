// djvu.h : main header file for the DJVU application
//

#if !defined(AFX_DJVU_H__FBA28827_A57C_44DF_9263_D318EAB03CD7__INCLUDED_)
#define AFX_DJVU_H__FBA28827_A57C_44DF_9263_D318EAB03CD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <afxmt.h>
#include <afxcoll.h>
#include <afxtempl.h>

#define MAINAPP ((CDjvuApp*)AfxGetApp())
#define STOP_PROCESS (WM_USER+1)
#include "searchrsltdlg.h"
/////////////////////////////////////////////////////////////////////////////
// CDjvuApp:
// See djvu.cpp for the implementation of this class
//

class CDjvuApp : public CWinApp
{
public:
	void StopProcess();
	CDjvuApp();
	PROCESS_INFORMATION pi;
	CWinThread *StopThread;
	CMutex StopMutex;
	CSingleLock Lock1;
	SearchRsltDlg SRDlg2;

	CStringArray Directories;
	CArray<CStringArray*,CStringArray*> AllFiles;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDjvuApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	afx_msg void OnStopProcess( UINT, LONG );
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDjvuApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DJVU_H__FBA28827_A57C_44DF_9263_D318EAB03CD7__INCLUDED_)

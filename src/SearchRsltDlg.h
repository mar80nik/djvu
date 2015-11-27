#if !defined(AFX_SEARCHRSLTDLG_H__D2762B2E_4C32_4CC6_8E66_4679102D585A__INCLUDED_)
#define AFX_SEARCHRSLTDLG_H__D2762B2E_4C32_4CC6_8E66_4679102D585A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchRsltDlg.h : header file
//
#include "mylistbox.h"
/////////////////////////////////////////////////////////////////////////////
// SearchRsltDlg dialog

class SearchRsltDlg : public CDialog
{
// Construction
public:
	SearchRsltDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SearchRsltDlg)
	enum { IDD = IDD_DIALOG1 };
	CButton	Cancel;
	CButton	Proceed;
	MyListBox	CollectInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SearchRsltDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SearchRsltDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnProced();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHRSLTDLG_H__D2762B2E_4C32_4CC6_8E66_4679102D585A__INCLUDED_)

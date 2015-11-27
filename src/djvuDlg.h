// djvuDlg.h : header file
//

#if !defined(AFX_DJVUDLG_H__E0F3B86B_3DB5_4570_B156_E5D2335DC203__INCLUDED_)
#define AFX_DJVUDLG_H__E0F3B86B_3DB5_4570_B156_E5D2335DC203__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include "mylist.h"
/////////////////////////////////////////////////////////////////////////////
// CDjvuDlg dialog

enum CheckStatus {CheckError=-1, CheckYes=0, CheckNo=1};

class CommandLineItem
{	
	CheckStatus Status;
public:
	CommandLineItem() {Status=CheckError; }	

	virtual CString GetString() {return CString("Error");};
	virtual BOOL IsChecked() {return false;}
};

class _PagesItem : public CommandLineItem
{
public:
	_PagesItem(){};	

	virtual CString GetString();
	virtual BOOL IsChecked() {return true;};
};

class _FileNameItem : public CommandLineItem
{
public:
	_FileNameItem(){};	
	virtual CString GetString();	
	virtual BOOL IsChecked() {return true;};
};

class _OutDirItem : public CommandLineItem
{
public:
	_OutDirItem(){};	
	virtual CString GetString();	
	virtual BOOL IsChecked() {return true;};
};

class _FormatItem : public CommandLineItem
{
public:
	_FormatItem(){};	
	virtual CString GetString();	
	virtual BOOL IsChecked() {return true;};
};

class _LayerItem : public CommandLineItem
{
public:
	_LayerItem(){};	
	virtual CString GetString();	
	virtual BOOL IsChecked() {return true;};
};

//----------------------------------------------------
class CDjvuDlg : public CDialog
{
// Construction
public:
	void UpdateList();
	void OnStopUI();
	void OnStartUI();
	CDjvuDlg(CWnd* pParent = NULL);	// standard constructor

	CArray<CommandLineItem*,CommandLineItem*> Items;
	CArray<CString,CString&> InputFiles;
	LPCITEMIDLIST lpItemDList;

// Dialog Data
	//{{AFX_DATA(CDjvuDlg)
	enum { IDD = IDD_DJVU_DIALOG };
	MyList	CollectInfo;
	CComboBox	FormatCombo;
	CListBox	ListBox1;
	CButton	StopButton;
	CButton	StartButton;
	CComboBox	LayersCombo;
	CEdit	MaxPage;
	CEdit	MinPage;
	CString	InputFile;
	CString	OutputDir;
	BOOL	PagesCheck;
	int		m_MaxPage;
	CString	temp;
	CString	Layers;
	CString	PagesString;
	CString	FormatStr;
	CString	InputDir;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDjvuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDjvuDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnCheck1();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnInputDir();
	afx_msg void OnCollect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.



#endif // !defined(AFX_DJVUDLG_H__E0F3B86B_3DB5_4570_B156_E5D2335DC203__INCLUDED_)

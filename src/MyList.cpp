// MyList.cpp : implementation file
//

#include "stdafx.h"
#include "djvu.h"
#include "MyList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyList

MyList::MyList()
{
	HorizontalExtent=0;
}

MyList::~MyList()
{
}


BEGIN_MESSAGE_MAP(MyList, CListBox)
	//{{AFX_MSG_MAP(MyList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyList message handlers

int MyList::AddString(CString& lpszItem)
{
	CDC *dc=GetDC();
	CSize ss=dc->GetTextExtent(lpszItem);
	if(HorizontalExtent<ss.cx)
	{
		HorizontalExtent=ss.cx;
		SetHorizontalExtent(HorizontalExtent);
	}


	int n1=GetCount();
	SetCaretIndex(n1); SetSel(n1);

	return CListBox::AddString(lpszItem);
}

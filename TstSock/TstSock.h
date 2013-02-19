// TstSock.h : main header file for the TSTSOCK application
//

#if !defined(AFX_TSTSOCK_H__6AC6680E_9B51_480D_9C3F_FD5A6B50358A__INCLUDED_)
#define AFX_TSTSOCK_H__6AC6680E_9B51_480D_9C3F_FD5A6B50358A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define WM_UPDATEMSG				WM_USER + 101

// CListBox* gpListBox = 0;
/////////////////////////////////////////////////////////////////////////////
// CTstSockApp:
// See TstSock.cpp for the implementation of this class
//

class CTstSockApp : public CWinApp
{
public:
	CTstSockApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTstSockApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTstSockApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TSTSOCK_H__6AC6680E_9B51_480D_9C3F_FD5A6B50358A__INCLUDED_)

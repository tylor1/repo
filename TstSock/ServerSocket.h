#if !defined(AFX_SERVERSOCKET_H__1D364A74_B490_45F7_82BF_FF5645DA5CAC__INCLUDED_)
#define AFX_SERVERSOCKET_H__1D364A74_B490_45F7_82BF_FF5645DA5CAC__INCLUDED_

#include "Thread.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CServerSocket command target

class CServerSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CServerSocket();
	virtual ~CServerSocket();

	void SetParentThread(CThread* pThread) { m_pParentThread = pThread; };
// Overrides
public:
	CWnd* m_pMainWnd;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CThread* m_pParentThread;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSOCKET_H__1D364A74_B490_45F7_82BF_FF5645DA5CAC__INCLUDED_)

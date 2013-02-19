#if !defined(AFX_CLIENTSOCKET_H__4738EB91_6520_4DB0_A304_6FF2BB89452B__INCLUDED_)
#define AFX_CLIENTSOCKET_H__4738EB91_6520_4DB0_A304_6FF2BB89452B__INCLUDED_

#include "Thread.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target

class CClientSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CClientSocket();
	virtual ~CClientSocket();

	void SetParentThread(CThread* pThread) { m_pParentThread = pThread; };

// Overrides
public:
	CWnd* m_pMainWnd;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CThread* m_pParentThread;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__4738EB91_6520_4DB0_A304_6FF2BB89452B__INCLUDED_)

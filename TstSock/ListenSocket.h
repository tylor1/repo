#if !defined(AFX_LISTENSOCKET_H__3AFF502F_43FF_4926_8B4A_56E252550B68__INCLUDED_)
#define AFX_LISTENSOCKET_H__3AFF502F_43FF_4926_8B4A_56E252550B68__INCLUDED_

#include "Thread.h"
#include "ServerSocket.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//

typedef CServerSocket* LPSVRSOCKET;
typedef CList<LPSVRSOCKET, LPSVRSOCKET&> LstSvrSocket;
/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target

class CListenSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CListenSocket();
	virtual ~CListenSocket();

	void SetParentThread(CThread* pThread) { m_pParentThread = pThread; };

// Overrides
public:
	CWnd* m_pMainWnd;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
	LstSvrSocket m_lstSvrSocket;
	CThread* m_pParentThread;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__3AFF502F_43FF_4926_8B4A_56E252550B68__INCLUDED_)

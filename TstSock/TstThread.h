#if !defined(AFX_TSTTHREAD_H__AF3F5992_D391_4052_8038_E7A4863CD9FF__INCLUDED_)
#define AFX_TSTTHREAD_H__AF3F5992_D391_4052_8038_E7A4863CD9FF__INCLUDED_

#include "ClientSocket.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TstThread.h : header file
//

#define WM_INIT							WM_USER + 101
#define WM_CONNECT						WM_USER + 102
#define WM_SEND							WM_USER + 103
#define WM_CLEARUP						WM_USER + 105

/////////////////////////////////////////////////////////////////////////////
// CTstThread thread

class CTstThread : public CWinThread
{
	DECLARE_DYNCREATE(CTstThread)
protected:
// 	CTstThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	CTstThread();           // protected constructor used by dynamic creation
	virtual ~CTstThread();
	void SetSocket(SOCKET sock);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTstThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void OnFinalRelease();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual void Serialize(CArchive& ar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle(LONG lCount);
	virtual CWnd* GetMainWnd();
	//}}AFX_VIRTUAL

// Implementation
protected:
// 	virtual ~CTstThread();

	// Generated message map functions
	//{{AFX_MSG(CTstThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg void OnInit(WPARAM wParam, LPARAM lParam);
	afx_msg void OnConnect(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSend(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClearup(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	SOCKET m_sock;
	CClientSocket m_socket;
	CClientSocket* m_pSocket;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TSTTHREAD_H__AF3F5992_D391_4052_8038_E7A4863CD9FF__INCLUDED_)

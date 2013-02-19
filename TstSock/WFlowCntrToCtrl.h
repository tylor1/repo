// WFlowCntrToCtrl.h: interface for the CWFlowCntrToCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WFLOWCNTRTOCTRL_H__A2C3F439_4957_4F89_A28B_C0DDF46618AB__INCLUDED_)
#define AFX_WFLOWCNTRTOCTRL_H__A2C3F439_4957_4F89_A28B_C0DDF46618AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"
#include "ClientSocket.h"	// Added by ClassView

class CWFlowCntrToCtrl : public CThread  
{
public:
	CWFlowCntrToCtrl(DWORD dwParentId = 0, THREADPARENT eType = PT_THREAD);
	virtual ~CWFlowCntrToCtrl();

	virtual bool OnStartup();
	virtual void OnCleanup();
	virtual void OnConnect(WPARAM wParam, LPARAM lParam);
	virtual void OnSend(WPARAM wParam, LPARAM lParam);
	virtual void OnReceive(WPARAM wParam, LPARAM lParam);

	virtual void OnMessage(MSG & msg);

	CClientSocket* m_pSocket;
};

#endif // !defined(AFX_WFLOWCNTRTOCTRL_H__A2C3F439_4957_4F89_A28B_C0DDF46618AB__INCLUDED_)

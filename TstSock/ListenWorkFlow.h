// ListenWorkFlow.h: interface for the CListenWorkFlow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTENWORKFLOW_H__5A5F6832_1C57_4567_83B9_387820241947__INCLUDED_)
#define AFX_LISTENWORKFLOW_H__5A5F6832_1C57_4567_83B9_387820241947__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"
#include "ListenSocket.h"	// Added by ClassView
#include "ServerWorkFlow.h"	// Added by ClassView

typedef CServerWorkFlow* LPSVRWORKFLOW;
typedef CList<LPSVRWORKFLOW, LPSVRWORKFLOW&> LstSvrWorkFlow;

class CListenWorkFlow : public CThread
{
public:
	CListenWorkFlow(DWORD dwParentId = 0, THREADPARENT eType = PT_THREAD);
	virtual ~CListenWorkFlow();

	virtual bool OnStartup();
	virtual void OnCleanup();
	virtual void OnAccept(WPARAM wParam, LPARAM lParam);
	virtual void OnSend(WPARAM wParam, LPARAM lParam);
	virtual void OnReceive(WPARAM wParam, LPARAM lParam);

	virtual void OnMessage(MSG & msg);

private:
	CListenSocket* m_pListenSocket;
	LstSvrWorkFlow m_lstSvrWorkFlow;
	LstSvrWorkFlow m_lstDisconnectSvrWorkFlow;
	int m_nPort;
};

#endif // !defined(AFX_LISTENWORKFLOW_H__5A5F6832_1C57_4567_83B9_387820241947__INCLUDED_)

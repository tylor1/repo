// ServerWorkFlow.h: interface for the CServerWorkFlow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERWORKFLOW_H__74E12366_5A84_440F_965A_73BB32E012C7__INCLUDED_)
#define AFX_SERVERWORKFLOW_H__74E12366_5A84_440F_965A_73BB32E012C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"
#include "ServerSocket.h"	// Added by ClassView


class CServerWorkFlow : public CThread  
{
public:
	CServerWorkFlow(DWORD dwParentId = 0, THREADPARENT eType = PT_THREAD);
	virtual ~CServerWorkFlow();

	virtual bool Accept(SOCKET hListenSock);

	virtual bool OnStartup();
	virtual void OnCleanup();
	virtual void OnSend(WPARAM wParam, LPARAM lParam);
	virtual void OnReceive(WPARAM wParam, LPARAM lParam);

	virtual void OnMessage(MSG & msg);

private:
	CServerSocket* m_pServerSocket;
};

#endif // !defined(AFX_SERVERWORKFLOW_H__74E12366_5A84_440F_965A_73BB32E012C7__INCLUDED_)

// ClientWorkFlow.h: interface for the CClientWorkFlow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTWORKFLOW_H__5C376295_92B5_40FE_938B_D7AA8DC18110__INCLUDED_)
#define AFX_CLIENTWORKFLOW_H__5C376295_92B5_40FE_938B_D7AA8DC18110__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"
#include "ClientSocket.h"	// Added by ClassView

class CClientWorkFlow : public CThread  
{
public:
	CClientWorkFlow(DWORD dwParentId = 0, THREADPARENT eType = PT_THREAD);
	virtual ~CClientWorkFlow();

	virtual bool OnStartup();
	virtual void OnCleanup();
	virtual void OnConnect(WPARAM wParam, LPARAM lParam);
	virtual void OnSend(WPARAM wParam, LPARAM lParam);
	virtual void OnReceive(WPARAM wParam, LPARAM lParam);

	virtual void OnMessage(MSG & msg);

private:
	CClientSocket* m_pClientSocket;
};

#endif // !defined(AFX_CLIENTWORKFLOW_H__5C376295_92B5_40FE_938B_D7AA8DC18110__INCLUDED_)

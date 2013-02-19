// ListenWorkFlow.cpp: implementation of the CListenWorkFlow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
// #include "TstSock.h"
#include "ListenWorkFlow.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListenWorkFlow::CListenWorkFlow(DWORD dwParentId, THREADPARENT eType)
	:CThread(dwParentId, eType),
	m_pListenSocket(0)
{

}

CListenWorkFlow::~CListenWorkFlow()
{

}

bool CListenWorkFlow::OnStartup()
{
	AfxSocketInit();
	m_pListenSocket = new CListenSocket;
	return true;
}

void CListenWorkFlow::OnMessage(MSG & msg)
{
	switch(msg.message)
	{
	case WM_ACCEPT:
		OnAccept(msg.wParam, msg.lParam);
		break;
	case WM_SEND:
		OnSend(msg.wParam, msg.lParam);
		break;
	case WM_RECEIVE:
		OnReceive(msg.wParam, msg.lParam);
	    break;
	default:
	    break;
	}
}

void CListenWorkFlow::OnCleanup()
{

}

void CListenWorkFlow::OnAccept(WPARAM wParam, LPARAM lParam)
{
	CServerWorkFlow* pSvrFlow = 0;

	/** �Ȳ����������Ƿ��Ѿ����ڣ� ��������������ߴ��� */

	// ���ߴ���ʼ
	// ���ߴ�����
	// ���ߴ������


	int nDisconnect = m_lstDisconnectSvrWorkFlow.GetCount();
	if (0 == nDisconnect)
	{
		pSvrFlow = new CServerWorkFlow(GetThreadID(), PT_THREAD);
	}
	else
	{
		pSvrFlow = m_lstDisconnectSvrWorkFlow.GetTail();
		m_lstDisconnectSvrWorkFlow.RemoveTail();
	}

	/** �������� */
	SOCKET hListenSocket = m_pListenSocket->Detach();
	pSvrFlow->Accept(hListenSocket);
	m_pListenSocket->Attach(hListenSocket);

	m_lstSvrWorkFlow.AddTail(pSvrFlow);
}

void CListenWorkFlow::OnSend(WPARAM wParam, LPARAM lParam)
{

}

void CListenWorkFlow::OnReceive(WPARAM wParam, LPARAM lParam)
{

}


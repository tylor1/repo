// ServerWorkFlow.cpp: implementation of the CServerWorkFlow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
// #include "TstSock.h"
#include "ServerWorkFlow.h"
#include "..\utils\api.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServerWorkFlow::CServerWorkFlow(DWORD dwParentId, THREADPARENT eType)
	:CThread(dwParentId, eType),
	m_pServerSocket(0)
{

}

CServerWorkFlow::~CServerWorkFlow()
{

}

bool CServerWorkFlow::Accept(SOCKET hListenSock)
{
	CSocket socket;
	SOCKET hOldSock = socket.Detach();
	socket.Attach(hListenSock);
	BOOL bAccept = socket.Accept(*m_pServerSocket);
	socket.Detach();
	socket.Attach(hOldSock);
	return (TRUE == bAccept);
}

bool CServerWorkFlow::OnStartup()
{
	AfxSocketInit();
	m_pServerSocket = new CServerSocket;
	return true;
}

void CServerWorkFlow::OnCleanup()
{
	if (m_pServerSocket)
	{
		delete m_pServerSocket;
	}
}

void CServerWorkFlow::OnSend(WPARAM wParam, LPARAM lParam)
{

}

void CServerWorkFlow::OnReceive(WPARAM wParam, LPARAM lParam)
{

}

void CServerWorkFlow::OnMessage(MSG & msg)
{
	switch(msg.message)
	{
	case WM_SEND:
		OnSend(msg.wParam, msg.lParam);
		break;
	case WM_RECEIVE:
		OnReceive(msg.wParam, msg.lParam);
	    break;
	default:
	    break;
	}

	CThread::OnMessage(msg);
}

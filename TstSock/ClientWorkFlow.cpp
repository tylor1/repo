// ClientWorkFlow.cpp: implementation of the CClientWorkFlow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
// #include "TstSock.h"
#include "ClientWorkFlow.h"
#include "..\utils\api.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClientWorkFlow::CClientWorkFlow(DWORD dwParentId, THREADPARENT eType)
	:CThread(dwParentId,eType)
{

}

CClientWorkFlow::~CClientWorkFlow()
{

}

bool CClientWorkFlow::OnStartup()
{
	AfxSocketInit();
	m_pClientSocket = new CClientSocket;
	return true;
}

void CClientWorkFlow::OnCleanup()
{
	if (m_pClientSocket)
	{
		delete m_pClientSocket;
	}
}

void CClientWorkFlow::OnConnect(WPARAM wParam, LPARAM lParam)
{
	Log("CClientWorkFlow::OnConnect");
	m_pClientSocket->Close();
	m_pClientSocket->Create();
	BOOL bConnect = m_pClientSocket->Connect("127.0.0.1", 1500);
	if (bConnect)
	{
		AfxMessageBox("连接成功");
	}
	else
	{
		AfxMessageBox("连接失败");
	}
}

void CClientWorkFlow::OnSend(WPARAM wParam, LPARAM lParam)
{

}

void CClientWorkFlow::OnReceive(WPARAM wParam, LPARAM lParam)
{

}

void CClientWorkFlow::OnMessage(MSG & msg)
{

	switch(msg.message)
	{
	case WM_CONNECT:
		OnConnect(msg.wParam, msg.lParam);
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

	CThread::OnMessage(msg);
}

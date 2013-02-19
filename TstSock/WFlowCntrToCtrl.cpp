// WFlowCntrToCtrl.cpp: implementation of the CWFlowCntrToCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TstSock.h"
#include "WFlowCntrToCtrl.h"
#include "..\utils\api.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWFlowCntrToCtrl::CWFlowCntrToCtrl(DWORD dwParentId, THREADPARENT eType)
:CThread(dwParentId, eType),
m_pSocket(0)
{

}

CWFlowCntrToCtrl::~CWFlowCntrToCtrl()
{

}


bool CWFlowCntrToCtrl::OnStartup()
{
	AfxSocketInit();
	m_pSocket = new CClientSocket;
	return true;
}

void CWFlowCntrToCtrl::OnCleanup()
{
	if (m_pSocket)
	{
		delete m_pSocket;
	}
}

void CWFlowCntrToCtrl::OnConnect(WPARAM wParam, LPARAM lParam)
{
	Log("CWFlowCntrToCtrl::OnConnect");
	m_pSocket->Close();
	m_pSocket->Create();
	BOOL bConnect = m_pSocket->Connect("127.0.0.1", 1500);
	if (bConnect)
	{
		AfxMessageBox("连接成功");
	}
	else
	{
		AfxMessageBox("连接失败");
	}
}

void CWFlowCntrToCtrl::OnSend(WPARAM wParam, LPARAM lParam)
{

}

void CWFlowCntrToCtrl::OnReceive(WPARAM wParam, LPARAM lParam)
{

}

void CWFlowCntrToCtrl::OnMessage(MSG & msg)
{
	CThread::OnMessage(msg);
}

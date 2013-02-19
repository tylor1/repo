// TstThread.cpp : implementation file
//

#include "stdafx.h"
#include "TstSock.h"
#include "TstThread.h"

#include "..\utils\api.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTstThread

IMPLEMENT_DYNCREATE(CTstThread, CWinThread)

CTstThread::CTstThread()
	:m_sock(0),
	m_pSocket(0)
{
}

CTstThread::~CTstThread()
{
	if (m_pSocket)
	{
		delete m_pSocket;
	}
}

BOOL CTstThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CTstThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CTstThread, CWinThread)
	//{{AFX_MSG_MAP(CTstThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_THREAD_MESSAGE(WM_INIT, OnInit)
		ON_THREAD_MESSAGE(WM_CONNECT, OnConnect)
		ON_THREAD_MESSAGE(WM_SEND, OnSend)
		ON_THREAD_MESSAGE(WM_CLEARUP, OnClearup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTstThread message handlers

void CTstThread::SetSocket(SOCKET sock)
{
	m_sock = sock;
	PostThreadMessage(WM_INIT,0,0);
}

void CTstThread::OnInit(WPARAM wParam, LPARAM lParam)
{
	AfxSocketInit();

	Log("CTstThread::OnInit");
	m_bAutoDelete = FALSE;

// 	m_socket.Close();
// 	m_socket.Create();
// 	SOCKET hOldSocket = m_socket.Detach();
// 	m_socket.Attach(m_sock);
// 	CloseHandle((void*)hOldSocket);

	Log("CTstThread::OnInit1");
	PostThreadMessage(WM_CONNECT, 0, 0);
	Log("CTstThread::OnInit2");
}

void CTstThread::OnConnect(WPARAM wParam, LPARAM lParam)
{
	Log("CTstThread::OnConnect");

// 	if (m_socket.Connect("192.168.2.107",1500))
// 	{
// 		AfxMessageBox("联机成功!");
// 		// m_socket.m_pMainWnd = this;
// 	}
// 	else
// 	{
// 		OutputDebugString(_T("联机失败！"));
// 	}
// 	m_socket.Detach();

	// PostThreadMessage(WM_QUIT,0,0);

	if (0 == m_pSocket)
	{
		m_pSocket = new CClientSocket;
	}

	if (m_pSocket)
	{
		m_pSocket->Close();
		m_pSocket->Create();
		if (m_pSocket->Connect("192.168.2.107",1500))
		{
			AfxMessageBox("联机成功!");
			// m_socket.m_pMainWnd = this;
		}
		else
		{
			OutputDebugString(_T("联机失败！"));
		}
	}
/*
	*/
	// m_socket
// 	m_socket.Close();
// 	m_socket.Create();
// 	m_socket.Connect("192.168.2.107", 1500);

}

void CTstThread::OnFinalRelease() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CWinThread::OnFinalRelease();
}

BOOL CTstThread::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (nID == WM_QUIT)
	{
		m_socket.Detach();
	}
	
	return CWinThread::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CTstThread::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

BOOL CTstThread::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_QUIT == pMsg->message)
	{
		m_socket.Detach();
	}
	
	return CWinThread::PreTranslateMessage(pMsg);
}

BOOL CTstThread::OnIdle(LONG lCount) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWinThread::OnIdle(lCount);
}

CWnd* CTstThread::GetMainWnd() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWinThread::GetMainWnd();
}

void CTstThread::OnSend(WPARAM wParam, LPARAM lParam)
{
	int nRes = 0;
	CString strMsg = "How are you?";
	if (m_pSocket)
	{
		nRes = m_pSocket->Send(strMsg, strMsg.GetLength());
	}
}

void CTstThread::OnClearup(WPARAM wParam, LPARAM lParam)
{
	// m_bReady = FALSE;
	if (m_pSocket)
	{
		m_pSocket->Close();
		delete m_pSocket;
		m_pSocket = 0;
	}
}

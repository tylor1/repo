// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "TstSock.h"
#include "ClientSocket.h"

#include "TstSockDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket()
	:m_pMainWnd(0),
	m_pParentThread(0)

{
}

CClientSocket::~CClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions

void CClientSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	char buf[1024];
	memset(buf,0,1024);
	int nLen = CSocket::Receive(buf,1024);
	// 	m_pParentWnd->PostMessage()
	// AfxMessageBox(buf);

	// CWnd *pWnd = AfxGetMainWnd();
	// CTstSockDlg* p = (CTstSockDlg*)m_pMainWnd;

	// p->m_lstMsg.AddString(buf);
// 	int nCmp = strcmp(buf,"OK");
// 	if (0 != nCmp)
		m_pMainWnd->PostMessage(WM_UPDATEMSG,(WPARAM)buf,(LPARAM)nLen);

	CSocket::OnReceive(nErrorCode);

	while(true)
	{
		OutputDebugString("CClientSocket::OnReceive\r\n");
		// Sleep(1000);
	}
// 
// 	if (0 != nCmp)
// 		Send("OK",2);
}

void CClientSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	AfxMessageBox("CClientSocket::OnClose");

	CSocket::OnClose(nErrorCode);
}

void CClientSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString str = "";
	str.Format("CClientSocket::OnSend: nRes = %d.\r\n",nErrorCode);
	OutputDebugString(str);

	CSocket::OnSend(nErrorCode);
}

void CClientSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString str = "";
	str.Format("CClientSocket::OnAccept: nRes = %d.\r\n",nErrorCode);
	OutputDebugString(str);
	
	CSocket::OnAccept(nErrorCode);
}

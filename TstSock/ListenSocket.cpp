// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "TstSock.h"
#include "ListenSocket.h"
#include "ServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSocket

CListenSocket::CListenSocket()
	:m_pMainWnd(0),
	m_pParentThread(0)

{
}

CListenSocket::~CListenSocket()
{
	CServerSocket* pSvr = 0;
	if (m_lstSvrSocket.GetCount())
	{
		pSvr = m_lstSvrSocket.GetTail();
		m_lstSvrSocket.RemoveTail();
		delete pSvr;
	}
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListenSocket, CSocket)
	//{{AFX_MSG_MAP(CListenSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSocket member functions

void CListenSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	CServerSocket* pSvr = new CServerSocket;
	CSocket::Accept(*pSvr);
	pSvr->m_pMainWnd = m_pMainWnd;

	CString strPear;
	UINT nPort;
	pSvr->GetPeerName(strPear, nPort);

	m_lstSvrSocket.AddTail(pSvr);
	OutputDebugString("-------------------------------------------------\r\n");
	OutputDebugString("*************************************************\r\n");
/*
	// Keep Alive
	SOCKET sock = pSvr->m_hSocket;
    tcp_keepalive inKeepAlive = {0}; // �������
    unsigned long ulInLen = sizeof(tcp_keepalive);
    tcp_keepalive outKeepAlive = {0}; // �������
    unsigned long ulOutLen = sizeof(tcp_keepalive);
    unsigned long ulBytesReturn = 0;

    // ����socket��keep aliveΪ5�룬���ҷ��ʹ���Ϊ3��
    inKeepAlive.onoff = 1;
    inKeepAlive.keepaliveinterval = 1000; // ����KeepAlive̽����ʱ����
    inKeepAlive.keepalivetime = 5000; // ��ʼ�״�KeepAlive̽��ǰ��TCP�ձ�ʱ��

    if (WSAIoctl(sock, SIO_KEEPALIVE_VALS,
        (LPVOID)&inKeepAlive, ulInLen,
        (LPVOID)&outKeepAlive, ulOutLen,
        &ulBytesReturn, NULL, NULL) == SOCKET_ERROR)
    {
		return;
        // return 0;
    }
*/
	CSocket::OnAccept(nErrorCode);
}

int CListenSocket::Send(const void* lpBuf, int nBufLen, int nFlags) 
{
	// TODO: Add your specialized code here and/or call the base class

	POSITION pos = m_lstSvrSocket.GetHeadPosition();
	while ( NULL != pos )
	{
		CServerSocket* pSvr = m_lstSvrSocket.GetNext(pos);
		pSvr->Send(lpBuf,nBufLen,nFlags);
	}

	return CSocket::Send(lpBuf, nBufLen, nFlags);
}

void CListenSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	AfxMessageBox("CListenSocket::OnClose");

	CSocket::OnClose(nErrorCode);
}

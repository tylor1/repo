// WFlowCntrToDB.cpp: implementation of the CWFlowCntrToDB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TstSock.h"
#include "WFlowCntrToDB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWFlowCntrToDB::CWFlowCntrToDB(DWORD dwParentId, THREADPARENT eType)
:CThread(dwParentId, eType)
{

}

CWFlowCntrToDB::~CWFlowCntrToDB()
{

}

bool CWFlowCntrToDB::OnStartup()
{
	return true;
}

void CWFlowCntrToDB::OnCleanup()
{

}

void CWFlowCntrToDB::OnConnect(WPARAM wParam, LPARAM lParam)
{

}

void CWFlowCntrToDB::OnSend(WPARAM wParam, LPARAM lParam)
{

}

void CWFlowCntrToDB::OnReceive(WPARAM wParam, LPARAM lParam)
{

}

void CWFlowCntrToDB::OnMessage(MSG & msg)
{
	CThread::OnMessage(msg);
}

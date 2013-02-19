/**********************************************************************
 * 工程名:	DrvExam
 * 文件名:	Thread.cpp
 * 版本号:	1.0
 * 功能:	
 * 作者:	tylor
 * 创建日期:	2012-03-31
 * 版权所有 (C) 2011 重庆奥彬科技有限公司
 *********************************************************************/

#include "stdafx.h"
#include "thread.h"

CThread::CThread(DWORD dwParent, THREADPARENT eParent)
{
	m_hThread	  = 0;
	m_iThreadID	  = 0;
	m_bMsgQueueOK = false;
	m_bQuitable	  = true;
	m_bRunning	  = false;

	m_dwParent			= dwParent;
	m_eParent			= eParent;

}

void CThread::Startup()
{
	m_hThread = CreateThread(NULL, NULL,ThreadProc, this, 0, &m_iThreadID);

	/** 等待、检查线程消息队列是否已经准备好 */
	while (!m_bMsgQueueOK || !m_bRunning)
		Sleep(50);
}

void CThread::Cleanup()
{
	if (m_hThread)
	{
		while ( !GetQuitable() )
			Sleep(50);
		
		PostMessage(WM_QUIT, 0, 0);
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		m_hThread = 0;
	}
}

CThread::~CThread()
{
}

/**********************************************************************
 * 函数名: OnMessage
 * 功能: 线程消息执行函数
 * @参数 msg: 
 * @返回值: void
 *********************************************************************/
void CThread::OnMessage(MSG & msg)
{

}

/**********************************************************************
 * 函数名: OnStartup
 * 功能: 当线程创建时，被线程调用
 * @返回值: 
 *********************************************************************/
bool CThread::OnStartup()
{
	return true;
}

/**********************************************************************
 * 函数名: OnCleanup
 * 功能: 线程内部调用，当线程结束时。
 * @返回值: void
 *********************************************************************/
void CThread::OnCleanup()
{
}

/**********************************************************************
 * 函数名: PostMessage
 * 功能: 
 * @参数 uiMsg: 
 * @参数 wParam: 
 * @参数 lParam: 
 * @返回值: 
 *********************************************************************/
bool CThread::PostMessage(UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	return ( 0 != PostThreadMessage(m_iThreadID, uiMsg, wParam, lParam) );
}

/**********************************************************************
 * 函数名: PostMessage
 * 功能: 
 * @参数 msg: 
 * @返回值: 
 *********************************************************************/
bool CThread::PostMessage(MSG& msg)
{
	return ( 0 != PostThreadMessage(m_iThreadID, msg.message, msg.wParam, msg.lParam) );
}

/**********************************************************************
 * 函数名: WillQuit
 * 功能: 检查退出消息。
 * @返回值: true---退出。
 *********************************************************************/
bool CThread::WillQuit()
{
	MSG msg;
	return TRUE == PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_NOREMOVE);
}

/**********************************************************************
 * 函数名: GetExitCode
 * 功能: 返回线程退出码
 * @返回值: 线程退出码
 *********************************************************************/
int  CThread::GetExitCode()
{
	MSG msg;
	
	if ( FALSE == PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_NOREMOVE) )
		return -1;

	return msg.wParam;
}

/**********************************************************************
 * 函数名: NotifyParent
 * 功能: post消息到窗口或父线程。
 * @参数 uiMsg: 
 * @参数 lParam: 
 * @参数 lParam: 
 * @返回值: void
 *********************************************************************/
void CThread::NotifyParent(UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (PT_WINDOW == GetParentType() )
		::PostMessage((HWND) GetParent(), uiMsg, wParam, lParam);
	else
		PostThreadMessage(GetParent(), uiMsg, wParam, lParam);
}

/**********************************************************************
 * 函数名: ThreadProc
 * 功能: 创建线程，创建消息队列，进入消息队列。
 * @参数 p: 
 * @返回值: 
 *********************************************************************/
DWORD WINAPI CThread::ThreadProc(LPVOID p)
{
	CThread * pTH = (CThread*)p;
	
	MSG msg;
	/** 调用 PeekMessage 准备好消息队列 */
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	pTH->m_bMsgQueueOK = true;

	if( !pTH->OnStartup() )
		return 0;

	pTH->m_bRunning = true;

	/** 形成消息队列，直到收到WM_QUIT退出 */
	while( GetMessage(&msg, NULL, 0, 0) )
	{
		pTH->OnMessage(msg);
	}

	pTH->OnCleanup();

	pTH->m_bMsgQueueOK = false;
	pTH->m_bRunning = false;

	return 0;
}
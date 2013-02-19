/**********************************************************************
 * ������:	DrvExam
 * �ļ���:	Thread.cpp
 * �汾��:	1.0
 * ����:	
 * ����:	tylor
 * ��������:	2012-03-31
 * ��Ȩ���� (C) 2011 ����±�Ƽ����޹�˾
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

	/** �ȴ�������߳���Ϣ�����Ƿ��Ѿ�׼���� */
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
 * ������: OnMessage
 * ����: �߳���Ϣִ�к���
 * @���� msg: 
 * @����ֵ: void
 *********************************************************************/
void CThread::OnMessage(MSG & msg)
{

}

/**********************************************************************
 * ������: OnStartup
 * ����: ���̴߳���ʱ�����̵߳���
 * @����ֵ: 
 *********************************************************************/
bool CThread::OnStartup()
{
	return true;
}

/**********************************************************************
 * ������: OnCleanup
 * ����: �߳��ڲ����ã����߳̽���ʱ��
 * @����ֵ: void
 *********************************************************************/
void CThread::OnCleanup()
{
}

/**********************************************************************
 * ������: PostMessage
 * ����: 
 * @���� uiMsg: 
 * @���� wParam: 
 * @���� lParam: 
 * @����ֵ: 
 *********************************************************************/
bool CThread::PostMessage(UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	return ( 0 != PostThreadMessage(m_iThreadID, uiMsg, wParam, lParam) );
}

/**********************************************************************
 * ������: PostMessage
 * ����: 
 * @���� msg: 
 * @����ֵ: 
 *********************************************************************/
bool CThread::PostMessage(MSG& msg)
{
	return ( 0 != PostThreadMessage(m_iThreadID, msg.message, msg.wParam, msg.lParam) );
}

/**********************************************************************
 * ������: WillQuit
 * ����: ����˳���Ϣ��
 * @����ֵ: true---�˳���
 *********************************************************************/
bool CThread::WillQuit()
{
	MSG msg;
	return TRUE == PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_NOREMOVE);
}

/**********************************************************************
 * ������: GetExitCode
 * ����: �����߳��˳���
 * @����ֵ: �߳��˳���
 *********************************************************************/
int  CThread::GetExitCode()
{
	MSG msg;
	
	if ( FALSE == PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_NOREMOVE) )
		return -1;

	return msg.wParam;
}

/**********************************************************************
 * ������: NotifyParent
 * ����: post��Ϣ�����ڻ��̡߳�
 * @���� uiMsg: 
 * @���� lParam: 
 * @���� lParam: 
 * @����ֵ: void
 *********************************************************************/
void CThread::NotifyParent(UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (PT_WINDOW == GetParentType() )
		::PostMessage((HWND) GetParent(), uiMsg, wParam, lParam);
	else
		PostThreadMessage(GetParent(), uiMsg, wParam, lParam);
}

/**********************************************************************
 * ������: ThreadProc
 * ����: �����̣߳�������Ϣ���У�������Ϣ���С�
 * @���� p: 
 * @����ֵ: 
 *********************************************************************/
DWORD WINAPI CThread::ThreadProc(LPVOID p)
{
	CThread * pTH = (CThread*)p;
	
	MSG msg;
	/** ���� PeekMessage ׼������Ϣ���� */
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	pTH->m_bMsgQueueOK = true;

	if( !pTH->OnStartup() )
		return 0;

	pTH->m_bRunning = true;

	/** �γ���Ϣ���У�ֱ���յ�WM_QUIT�˳� */
	while( GetMessage(&msg, NULL, 0, 0) )
	{
		pTH->OnMessage(msg);
	}

	pTH->OnCleanup();

	pTH->m_bMsgQueueOK = false;
	pTH->m_bRunning = false;

	return 0;
}
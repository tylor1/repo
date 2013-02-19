/***********************************************************************************
 * ������:	DrvExam
 * �ļ���:	Thread.h
 * �汾��:	1.0
 * ����:	�����̣߳������̣߳�������Ϣ���У�������Ϣ���С�
 * ����:	tylor
 * ��������:	2012-03-31
 * ��Ȩ���� (C) 2011 ����±�Ƽ����޹�˾
 **********************************************************************************/

#ifndef THREAD_H
#define THREAD_H

#define WM_CONNECT						WM_USER + 101
#define WM_ACCEPT						WM_USER + 102
#define WM_SEND							WM_USER + 103
#define WM_RECEIVE						WM_USER + 105
#define WM_DISCONNECT					WM_USER + 106

enum THREADPARENT {PT_WINDOW = 1, PT_THREAD};

class CThread
{
public:
	CThread(DWORD dwParent = 0, THREADPARENT eParent = PT_THREAD);
	virtual ~CThread();

	virtual void Startup();
	virtual void Cleanup();

	bool IsRunning() {return m_bRunning; };

	/** �߳���post��Ϣ���߳��ڲ� */
	bool PostMessage(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0);
	bool PostMessage(MSG& msg);

	/** �����߳�ID */
	DWORD GetThreadID(){return m_iThreadID;};

protected:

	virtual bool OnStartup();
	virtual void OnCleanup();

	/** ��Ϣִ�к��� */
	virtual void OnMessage(MSG & msg);

	virtual bool WillQuit();

	void SetQuitable(bool bQuitable) {m_bQuitable = bQuitable;};
	bool GetQuitable() {return m_bQuitable; }

	virtual int  GetExitCode();

	/** ���͸������� */
	DWORD GetParent() {return m_dwParent;};
	THREADPARENT GetParentType() {return m_eParent;};
	void NotifyParent(UINT uiMsg, WPARAM wParam, LPARAM lParam);

protected:

	DWORD	m_dwParent;

private:

	/** �߳̾�����߳�ID */
	HANDLE	m_hThread;
	DWORD	m_iThreadID;
	/** �߳���Ϣ����״̬ */
	bool	m_bMsgQueueOK;
	bool	m_bQuitable;
	bool	m_bRunning;

	THREADPARENT m_eParent;

	/** �̺߳��� */
	static DWORD WINAPI ThreadProc(LPVOID p);

};

#endif
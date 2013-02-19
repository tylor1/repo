/***********************************************************************************
 * 工程名:	DrvExam
 * 文件名:	Thread.h
 * 版本号:	1.0
 * 功能:	工作线程，创建线程，创建消息队列，进入消息队列。
 * 作者:	tylor
 * 创建日期:	2012-03-31
 * 版权所有 (C) 2011 重庆奥彬科技有限公司
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

	/** 线程外post消息到线程内部 */
	bool PostMessage(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0);
	bool PostMessage(MSG& msg);

	/** 返回线程ID */
	DWORD GetThreadID(){return m_iThreadID;};

protected:

	virtual bool OnStartup();
	virtual void OnCleanup();

	/** 消息执行函数 */
	virtual void OnMessage(MSG & msg);

	virtual bool WillQuit();

	void SetQuitable(bool bQuitable) {m_bQuitable = bQuitable;};
	bool GetQuitable() {return m_bQuitable; }

	virtual int  GetExitCode();

	/** 父和父的类型 */
	DWORD GetParent() {return m_dwParent;};
	THREADPARENT GetParentType() {return m_eParent;};
	void NotifyParent(UINT uiMsg, WPARAM wParam, LPARAM lParam);

protected:

	DWORD	m_dwParent;

private:

	/** 线程句柄，线程ID */
	HANDLE	m_hThread;
	DWORD	m_iThreadID;
	/** 线程消息队列状态 */
	bool	m_bMsgQueueOK;
	bool	m_bQuitable;
	bool	m_bRunning;

	THREADPARENT m_eParent;

	/** 线程函数 */
	static DWORD WINAPI ThreadProc(LPVOID p);

};

#endif
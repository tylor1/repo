// WFlowCntrToDB.h: interface for the CWFlowCntrToDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WFLOWCNTRTODB_H__D65DFCC9_B128_47A1_A7EB_43BC4620A969__INCLUDED_)
#define AFX_WFLOWCNTRTODB_H__D65DFCC9_B128_47A1_A7EB_43BC4620A969__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"

class CWFlowCntrToDB : public CThread  
{
public:
	CWFlowCntrToDB(DWORD dwParentId = 0, THREADPARENT eType = PT_THREAD);
	virtual ~CWFlowCntrToDB();

	virtual bool OnStartup();
	virtual void OnCleanup();
	virtual void OnConnect(WPARAM wParam, LPARAM lParam);
	virtual void OnSend(WPARAM wParam, LPARAM lParam);
	virtual void OnReceive(WPARAM wParam, LPARAM lParam);

	virtual void OnMessage(MSG & msg);

};

#endif // !defined(AFX_WFLOWCNTRTODB_H__D65DFCC9_B128_47A1_A7EB_43BC4620A969__INCLUDED_)

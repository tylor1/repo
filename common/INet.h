/**********************************************************************
 * 工程名:    DrvExam
 * 文件名:    INet.h
 * 版本号:    1.0
 * 功能:		
 * 作者:		
 * 创建日期:   2012-03-26
 * 版权所有 (C) 2011 重庆奥彬科技有限公司
 *********************************************************************/

#ifndef INET_H
#define INET_H

#include "common.h"
#include "Protocol.h"

/**********************************************************************
 * class: TContext
 * 说明 : 事件内容
 **********************************************************************/
class TContext
{
public:
	virtual ~TContext() {};
};

/**********************************************************************
 * class: TNetEvent
 * 说明 : 网络事件内容
 **********************************************************************/
class TNetEvent : public TContext
{
public:
	TNetEvent()
	{
		m_ene = ene_error;
		m_strIP = _T("127.0.0.1");
		m_nPort = 0;
	};
	virtual ~TNetEvent(){};


	int m_ene;
	CString m_strIP;
	int m_nPort;
};

/**********************************************************************
 * class: INetObserver
 * 说明 : 网络事件观察者基类
 **********************************************************************/
class INetObserver
{
public:
	virtual ~INetObserver() {};

	/**********************************************************************
	 * 函数名: OnNotify
	 * 功能 : 网络事件通知
	 * @参数	context:	事件内容 
	 * @返回值:	void 
	 **********************************************************************/
	IMPORT virtual void OnNotify(const TContext* context) = 0;
};

/**********************************************************************
 * class: INet
 * 说明 : 网络类的基类
 **********************************************************************/
class INet
{
public:
	INet() {m_netObserver = 0;}	
	
	IMPORT virtual ~INet() {}; 
	
	//interfaces	
	IMPORT virtual void  HookObserver(INetObserver* netObserver) { m_netObserver = netObserver; }
	IMPORT virtual INetObserver * Observer() { return m_netObserver; }

private:

	INetObserver* m_netObserver;
};

#endif


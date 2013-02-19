/**********************************************************************
 * ������:    DrvExam
 * �ļ���:    INet.h
 * �汾��:    1.0
 * ����:		
 * ����:		
 * ��������:   2012-03-26
 * ��Ȩ���� (C) 2011 ����±�Ƽ����޹�˾
 *********************************************************************/

#ifndef INET_H
#define INET_H

#include "common.h"
#include "Protocol.h"

/**********************************************************************
 * class: TContext
 * ˵�� : �¼�����
 **********************************************************************/
class TContext
{
public:
	virtual ~TContext() {};
};

/**********************************************************************
 * class: TNetEvent
 * ˵�� : �����¼�����
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
 * ˵�� : �����¼��۲��߻���
 **********************************************************************/
class INetObserver
{
public:
	virtual ~INetObserver() {};

	/**********************************************************************
	 * ������: OnNotify
	 * ���� : �����¼�֪ͨ
	 * @����	context:	�¼����� 
	 * @����ֵ:	void 
	 **********************************************************************/
	IMPORT virtual void OnNotify(const TContext* context) = 0;
};

/**********************************************************************
 * class: INet
 * ˵�� : ������Ļ���
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


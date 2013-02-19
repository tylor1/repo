/**********************************************************************
 * ������:    DrvExam
 * �ļ���:    INetCenter.h
 * �汾��:    1.0
 * ����:		
 * ����:		
 * ��������:   2012-03-30
 * ��Ȩ���� (C) 2011 ����±�Ƽ����޹�˾
 *********************************************************************/

#ifndef INETCENTER_H
#define INETCENTER_H

#include "INet.h"

/**********************************************************************
 * class: IObsNetCenter
 * ˵�� : �������Obs
 **********************************************************************/
class IObsNetCenter : public INetObserver
{
public:
	virtual ~IObsNetCenter() {};
	IMPORT virtual void OnPackArrive(const TNetPack* pack) = 0;
	IMPORT virtual void OnRetryNetFail() = 0;
};

/**********************************************************************
 * class: INetCenter
 * ˵�� : ��������ӿ�
 **********************************************************************/
class INetCenter : public INet
{
public:
	IMPORT virtual ~INetCenter() {};
	IMPORT virtual void SetDBServer(const TCHAR* szIP, const int nPort) = 0;
	IMPORT virtual void SetControlServer(const TCHAR* szIP, const int nPort) = 0;
	IMPORT virtual void ConnetDBServer() = 0;
	IMPORT virtual void ConnetCtrlServer() = 0;
	IMPORT virtual void GetName(CString& strName) = 0;
};


#endif	/** INETCENTER_H */
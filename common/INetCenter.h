/**********************************************************************
 * 工程名:    DrvExam
 * 文件名:    INetCenter.h
 * 版本号:    1.0
 * 功能:		
 * 作者:		
 * 创建日期:   2012-03-30
 * 版权所有 (C) 2011 重庆奥彬科技有限公司
 *********************************************************************/

#ifndef INETCENTER_H
#define INETCENTER_H

#include "INet.h"

/**********************************************************************
 * class: IObsNetCenter
 * 说明 : 中心软件Obs
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
 * 说明 : 中心软件接口
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
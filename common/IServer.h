/**********************************************************************
 * 工程名:    DrvExam
 * 文件名:    IServer.h
 * 版本号:    1.0
 * 功能:
 * 作者:
 * 创建日期:   2012-04-05
 * 版权所有 (C) 2011 重庆奥彬科技有限公司
 *********************************************************************/

#ifndef ISERVER_H
#define ISERVER_H

#include "INet.h"

/**********************************************************************
 * class: IObsServer
 * 说明 : 服务器Obs
 **********************************************************************/
class IObsServer : public INetObserver
{
public:
	IMPORT virtual ~IObsServer() {};

	IMPORT virtual void OnPackArrive(const TNetPack* pack) = 0;
};

class IServer;
typedef IServer* LPSVR;
typedef CList<LPSVR, LPSVR&> LstSvr;
/**********************************************************************
 * class: IServer
 * 说明 : 服务器接口
 **********************************************************************/
class IServer: public INet
{
public:
	IMPORT virtual ~IServer() {};

	/**********************************************************************
	 * 函数名:	StartServer
	 * 功能:	服务器开始监听
	 * @参数	nPort:	监听端口号 
	 * @返回值:	true : 成功;
	 *			false : 失败。
	 *********************************************************************/
	IMPORT virtual bool StartServer(const int nPort) = 0;
	IMPORT virtual int SendData(const void* lpBuf, int nBufLen, int nFlags = 0) = 0;

	/**********************************************************************
	 * 函数名:	SendPack
	 * 功能:	网络包发送
	 * @参数	pack:	网络包 
	 * @返回值:	0 : 上一个包未发送成功，等待或检查网络连接;
	 *			1 : 上一个包已发送成功，当前包正在投递中。　
	 *********************************************************************/
	IMPORT virtual int SendPack(TNetPack* pack, const TCHAR* szIP, const int nPort) = 0;
	IMPORT virtual void GetConnectList(LstSvr** pplst) = 0;
	IMPORT virtual void GetClient(TCHAR* wszBufIP, int& nBufSize, int& nPort) = 0;
};


#endif	/** ISERVER_H */
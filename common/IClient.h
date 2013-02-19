/**********************************************************************
 * 工程名:    DrvExam
 * 文件名:    IClient.h
 * 版本号:    1.0
 * 功能:		
 * 作者:		
 * 创建日期:   2012-04-05
 * 版权所有 (C) 2011 重庆奥彬科技有限公司
 *********************************************************************/

#ifndef ICLIENT_H
#define ICLIENT_H

#include "INet.h"

/**********************************************************************
 * class: IObsClient
 * 说明 : 客户端Obs
 **********************************************************************/
class IObsClient : public INetObserver
{
public:
	virtual ~IObsClient() {};

	IMPORT virtual void OnPackArrive(const TNetPack* pack) = 0;
};

/**********************************************************************
 * class: IClient
 * 说明 : 客户端接口
 **********************************************************************/
class IClient : public INet
{
public:
	IMPORT virtual ~IClient() {};

	/**********************************************************************
	 * 函数名:	ConnectServer
	 * 功能:	连接服务器
	 * @参数:	szIP : 服务器IP
	 *			nPort :	服务器端口号
	 * @返回值:	true : 成功;
	 *			false : 失败。
	 *********************************************************************/
	IMPORT virtual bool ConnectServer(const TCHAR* szIP, const int nPort) = 0;
	IMPORT virtual int SendData(const void* lpBuf, int nBufLen, int nFlags = 0) = 0;

	/**********************************************************************
	 * 函数名:	SendPack
	 * 功能:	网络包发送
	 * @参数	pack:	网络包 
	 * @返回值:	0 : 上一个包未发送成功，等待或检查网络连接;
	 *			1 : 上一个包已发送成功，当前包正在投递中。　
	 *********************************************************************/
	IMPORT virtual int SendPack(TNetPack* pack) = 0;
};


#endif	/** ICLIENT_H */
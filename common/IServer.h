/**********************************************************************
 * ������:    DrvExam
 * �ļ���:    IServer.h
 * �汾��:    1.0
 * ����:
 * ����:
 * ��������:   2012-04-05
 * ��Ȩ���� (C) 2011 ����±�Ƽ����޹�˾
 *********************************************************************/

#ifndef ISERVER_H
#define ISERVER_H

#include "INet.h"

/**********************************************************************
 * class: IObsServer
 * ˵�� : ������Obs
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
 * ˵�� : �������ӿ�
 **********************************************************************/
class IServer: public INet
{
public:
	IMPORT virtual ~IServer() {};

	/**********************************************************************
	 * ������:	StartServer
	 * ����:	��������ʼ����
	 * @����	nPort:	�����˿ں� 
	 * @����ֵ:	true : �ɹ�;
	 *			false : ʧ�ܡ�
	 *********************************************************************/
	IMPORT virtual bool StartServer(const int nPort) = 0;
	IMPORT virtual int SendData(const void* lpBuf, int nBufLen, int nFlags = 0) = 0;

	/**********************************************************************
	 * ������:	SendPack
	 * ����:	���������
	 * @����	pack:	����� 
	 * @����ֵ:	0 : ��һ����δ���ͳɹ����ȴ�������������;
	 *			1 : ��һ�����ѷ��ͳɹ�����ǰ������Ͷ���С���
	 *********************************************************************/
	IMPORT virtual int SendPack(TNetPack* pack, const TCHAR* szIP, const int nPort) = 0;
	IMPORT virtual void GetConnectList(LstSvr** pplst) = 0;
	IMPORT virtual void GetClient(TCHAR* wszBufIP, int& nBufSize, int& nPort) = 0;
};


#endif	/** ISERVER_H */
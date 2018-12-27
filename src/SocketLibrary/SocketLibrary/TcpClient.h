/*
* Copyright (C) 2005-2007 Zhang bao yuan(bolidezhang@gmail.com)
* All rights reserved.
* 
* �ļ����ƣ�TcpClient.h
* ժ    Ҫ��TcpClient
* ��    �ߣ��ű�Ԫ bolidezhang@gmail.com
* ������ڣ�2005/07/16
*
*/

#pragma once
#include <string>
#include "SocketSource.h"
#include "SocketSendPool.h"
#include "sync/threadmutex.h"
#include "sync/event.h"
#include "sync/thread.h"
#include <vector>
#include <utility>

namespace SL
{

class SOCKETLIBRARY_API CTcpClient : public CSocketSource
{
public:
	CTcpClient(void);
	virtual ~CTcpClient(void);

	void SetInterface(CAppLog *pAppLog, CSocketEvent *pSocketEvent, CSocketRunner *pSocketRunner);
	void SetBufferSize(int nRecvBufferSize, int nSendBufferSize);
	BOOL SetAutoConnect(BOOL bAutoConnect, int nCheckInterval=300000, int nReconnectSleep=1000);

	virtual BOOL DoOpen();
	BOOL AppendServerAddr(const char *szServerName, unsigned short nServerPort);
	BOOL RemoveServerAddr(int nPos);
	BOOL Open(const char *szServerName, unsigned short nServerPort, int nLocalPort=0);
	BOOL Close();

	BOOL IsConnected() const;
	int  Send(const char *szData, int nLen, int nOptval=0);

	SOCKET GetSocketHandle() const;
protected:
	BOOL PostRecv(SOCKET hSocket, void *p);
	BOOL PostSend(void *pPerIoData);

	BOOL Connect();
	BOOL Disconnect(SOCKET hSocket, BOOL bForce = FALSE);
	BOOL IsRealConnected();

protected:
	typedef std::pair<std::string,unsigned short> SERVER_ADDR;

	SOCKET	m_hSocket;
	//����״̬
	BOOL	m_bIsConnected;

	//�Զ�����
	BOOL				m_bAutoConnect;
	int					m_nCheckIntervalTime;	//������ӵ�״̬(ms)
	int					m_nReconnectSleepTime;  //���ӶϿ�ʱ��������ʱ����(ms)
	SYNC::CThread		m_threadAutoConnect;
	SYNC::CEvent		m_eventAutoConnect;

	SYNC::CThreadMutex	m_lock;

	//���ͻ����
	CSocketSendPool<SYNC::CThreadMutex>	m_sendPool;
	SOCKET_SESSION						m_SocketSession;

	//Զ�̷���������:������IP��ַ(218.1.65.74)������(www.cga.com.cn)
	std::vector<SERVER_ADDR>	m_vectServerAddr;
	unsigned short				m_nLocalPort;
	unsigned short				m_nVectorPos;

private:
	static unsigned WINAPI AutoConnect(LPVOID lParam);

};

};
 
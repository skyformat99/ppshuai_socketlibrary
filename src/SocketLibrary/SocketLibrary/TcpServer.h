/*
* Copyright (C) 2005-2007 Zhang bao yuan(bolidezhang@gmail.com)
* All rights reserved.
* 
* �ļ����ƣ�TcpServer.h
* ժ    Ҫ��TcpServer
* ��    �ߣ��ű�Ԫ bolidezhang@gmail.com
* ������ڣ�2005/07/16
*
*/

#pragma once

#ifndef USE_HASHMAP
	#include <map>
#else
	#include <hash_map>
#endif
#include <list>

#include "SocketSource.h"
#include "SocketSendPool.h"
#include "sync/Thread.h"
#include "sync/threadmutex.h"

namespace SL
{

class SOCKETLIBRARY_API CTcpServer : public CSocketSource
{
public:

#ifndef USE_HASHMAP
	typedef std::map<SOCKET,PSOCKET_SESSION> SocketSessionMap;
	typedef std::map<SOCKET,PSOCKET_SESSION>::iterator SocketSessionIterator;
#else
	typedef stdext::hash_map<SOCKET,PSOCKET_SESSION> SocketSessionMap;
	typedef stdext::hash_map<SOCKET,PSOCKET_SESSION>::iterator SocketSessionIterator;
#endif

public:
	CTcpServer(void);
	virtual ~CTcpServer(void);

	void SetConfig(int nMaxSocketNum, int nMaxFreePoolNum, int nDefaultFreePoolNum);
	void SetInterface(CAppLog *pAppLog, CSocketEvent *pSocketEvent, CSocketRunner *pSocketRunner);
	void SetBufferSize(int nRecvBufferSize, int nSendBufferSize);

	BOOL Open(const char *szLocalIP, unsigned short nPort, int nBacklog = 10);
	BOOL Close();

	BOOL IsConnected(SOCKET hClientSocket);
	BOOL Disconnect(SOCKET hClientSocket, bool bForce = false);
	int  Send(SOCKET hClientSocket, const char *szData, int nLen, int nOptval=0);

	//socket�ĸ�����Ϣָ��
	BOOL  SetAttachInfo(SOCKET hClientSocket, void *pAttachInfo);
	void* GetAttachInfo(SOCKET hClientSocket);

protected:
	BOOL PostRecv(SOCKET hClientSocket, void *p);
	BOOL PostSend(void *pPerIoData);

	static unsigned int WINAPI ListenProc(LPVOID lParam);

protected:

	SOCKET			m_hListenSocket;

	//�ٽ籣����
	SYNC::CThreadMutex			m_lock;

	//��ǰ���̶�
	HANDLE						m_hProcessHeap;
	//���ж����
	std::list<PSOCKET_SESSION>	m_lstFreePool;
	//���ͻ����
	CSocketSendPool<SYNC::CThreadMutex>	m_sendPool;

	//Socket���������
	int	m_nMaxSocketNum;
	//�����гص�����
	int m_nMaxFreePoolNum;
	//Ĭ�Ͽ��гص�����
	int m_nDefaultFreePoolNum;

	//listen�߳�
	SYNC::CThread m_threadListen;

	//��ǰ��������
	SocketSessionMap			m_mapSocketSession;
};

};

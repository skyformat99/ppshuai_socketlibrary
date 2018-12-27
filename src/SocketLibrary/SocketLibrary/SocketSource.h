/*
* Copyright (C) 2005-2007 Zhang bao yuan(bolidezhang@gmail.com)
* All rights reserved.
* 
* �ļ����ƣ�SocketSource.h
* ժ    Ҫ��SocketԴ�ӿ���
* ��    �ߣ��ű�Ԫ bolidezhang@gmail.com
* ������ڣ�2005/07/16
*
*/

#pragma once
#include "AppLog.h"
#include "SocketRunner.h"
#include "SocketLib.h"
#include <string>

namespace SL
{

class CSocketEvent;
class SOCKETLIBRARY_API CSocketSource
{
public:
	CSocketSource(void);
	virtual ~CSocketSource(void);

	virtual BOOL Open(const char *szServerName, unsigned short nPort, int nOption) = 0;
	virtual BOOL Close() = 0;
	virtual BOOL PostSend(void *pPerIoData) { return TRUE; };

	//TCPʱ�õ�
	virtual BOOL PostRecv(SOCKET hSocket, void *pPerIoData) { return TRUE; };
	virtual BOOL Disconnect(SOCKET hSocket, bool bForce=false) { return TRUE; };

	//���ýӿ�
	virtual void SetInterface(CAppLog *pAppLog, CSocketEvent *pSocketEvent, CSocketRunner *pSocketRunner){ return; };
	//���û�������С
	virtual void SetBufferSize(int nRecvBufferSize, int nSendBufferSize){ return; };
	//����socket�ĸ�����Ϣָ��
	virtual BOOL SetAttachInfo(SOCKET hSocket, void *pAttachInfo) { return TRUE; };

	//TCPServer
	virtual int  Send(SOCKET hSocket, const char *szData, int nLen, int nOptval=0) { return 0; };

	//TCPClient/UDP
	virtual int  Send(const char *szData, int nLen, int nOptval=0) { return 0; };

	//UDP�õ�
	virtual BOOL PostRecv(void *pPerIoRecv) { return TRUE; };
	virtual int  Send(const char *szData, int nLen, sockaddr *pTo, int nToLen, int nOptval=0) { return 0; };
	virtual int  Send(const char *szData, int nLen, const char *szServerIP, unsigned short nPort, int nOptval=0) { return 0; };

public:
	CAppLog		   *m_pAppLog;
	CSocketEvent   *m_pSocketEvent;
	CSocketRunner  *m_pSocketRunner; 

protected:
	//���ջ������Ĵ�С
	//(һ��Ϊ8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536)
	int				m_nRecvBufferSize;
	//���ͻ������Ĵ�С
	int				m_nSendBufferSize;

};

};

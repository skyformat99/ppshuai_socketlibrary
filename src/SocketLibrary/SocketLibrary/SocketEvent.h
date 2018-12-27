/*
* Copyright (C) 2005-2007 Zhang bao yuan(bolidezhang@gmail.com)
* All rights reserved.
* 
* �ļ����ƣ�SocketEvent.h
* ժ    Ҫ��Socket�¼��ӿ���
* ��ǰ�汾��1.0.0.716
* ��    �ߣ��ű�Ԫ bolidezhang@gmail.com
* ������ڣ�2005/07/16
*
*/

#pragma once
#include "SocketLib.h"
#include "SocketSource.h"

namespace SL
{

class SOCKETLIBRARY_API CSocketEvent
{
public:
	CSocketEvent(void);
	virtual ~CSocketEvent(void);

	virtual BOOL OnInitSocket(PSOCKET_SESSION pSocketSession) { return TRUE; };
	virtual BOOL OnUninitSocket(void *pAttachInfo) { return TRUE; };

	virtual BOOL OnAccept(CSocketSource *pSource, SOCKET hClientSocket) { return TRUE; };
	virtual BOOL OnDisconnect(CSocketSource *pSource, SOCKET hClientSocket, void *pAttachInfo) { return TRUE; };
	virtual int  OnRecv(CSocketSource *pSource, SOCKET hClientSocket, void *pAttachInfo, const char *szData, int nLen) { return 1; };

	//UDPʱ�õ�
	virtual int  OnRecv(CSocketSource *pSource, const char *szData, int nLen, sockaddr *pFrom, int nFromLen) { return 1; };

};

};

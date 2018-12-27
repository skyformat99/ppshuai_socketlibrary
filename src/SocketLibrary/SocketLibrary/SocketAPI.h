//**********************************************************************
//
// 
// All rights reserved.
//
// This copy of Socketlibrary is licensed to you under the terms described 
// in the LICENSE.txt file included in this distribution.
//
//**********************************************************************

#pragma once
#include "config.h"
namespace SL
{

class SOCKETLIBRARY_API CSocketAPI
{
private:
	CSocketAPI(void);
	~CSocketAPI(void);

public:
	//ͨ��Socketֵȡ��IP��ַ��Port�˿�
	static BOOL	GetSocketInfo(SOCKET hSocket, LPSTR szIPAddr, USHORT *nPort);

	static BOOL LoadSocketLib(int version_high, int version_low);
	static BOOL UnloadSocketLib();

	/*
	��windows2000��ʼ����һ���µ�I/O��������SIO_KEEPALIVE_VALS����ͨ��WSAIoctl()���
	�����׽��������Ƿ����ñ�����ơ�KeepAliveTime��KeepAliveInterval��
	Argument structure for SIO_KEEPALIVE_VALS
	struct tcp_keepalive {
		u_long  onoff;
		u_long  keepalivetime;
		u_long  keepaliveinterval;
	};
	*/
	static BOOL GetSocketKeepAlive(SOCKET hSocket);
	static BOOL SetSocketKeepAlive(SOCKET hSocket, BOOL bKeepAlive);
	static BOOL SetSocketKeepAliveValue(SOCKET hSocket, unsigned long nKeepAliveTime=7200000, unsigned long nKeepAliveInterval=1000);

	//SO_LINGER
	static BOOL SetSocketLinger(SOCKET hSocket, unsigned short nOnoff, unsigned short nLinger);

	//timeout and buffer
	static BOOL SetTimeOut(SOCKET hSocket,int nRecvTimeOut,int nSendTimeOut);
	static BOOL SetBufferSize(SOCKET hSocket,int nRecvBufferSize,int nSendBufferSize);

	//�����Ƿ�����Nagle�㷨
	//Set the nodelay TCP option for real-time games
	static BOOL SetTCPNODELAY(SOCKET hSocket,int nOpt);

	//�����Ƿ�Socket���������ʽģʽ
	static BOOL SetFIONBIO(SOCKET hSocket,int nOpt);
};

};

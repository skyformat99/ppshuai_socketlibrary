//**********************************************************************
//
// 
// All rights reserved.
//
// This copy of Socketlibrary is licensed to you under the terms described 
// in the LICENSE.txt file included in this distribution.
//
//**********************************************************************

#ifndef SLTCPSESSION_H
#define SLTCPSESSION_H
#pragma once
#include "socketlib.h"

namespace SL
{

/*	CTcpSession
	���ܣ����/����Ĵ���
	��Ϣ�Ĺ��:��Ϣ��ʼ��1��2��4���ֽڱ�ʾ��Ϣ��С
		message = messagehead + messagebody
		messagehead = size + command + option
	ע��:
		��������Сһ��Ҫ���ڵ������������Ϣ������
*/
class CSocketSource;
class SOCKETLIBRARY_API CSLTcpSession
{
public:
	CSLTcpSession(void);
	virtual ~CSLTcpSession(void);

	virtual bool Init(PSOCKET_SESSION pSocketSession, SOCKET hSocket, uint32 nBufferSize = 1024, uint8 nMsgSizeByte = 4);
	virtual bool Uninit();
	virtual bool Reset();
	virtual bool Clear();

	// ������Ϣ
	virtual int ProcessMessage(const char *szMsg, int nLen);
	// ��������
	virtual int Send(const char *szData, int nLen);
	// ��������
	virtual int OnRecv(const char *szData, int nLen);

	//�¼������������糤ʱ��û�յ�KeepAlive��Ϣ
	virtual int OnEvent(int nEventID);

	//ȡ���¼�ID
	//<0:��ʾ�ر�, 0:û�з����¼�, >0�������¼�
	virtual int GetEventID();


private:
	// ȡ����Ϣ��С
	uint32 GetMsgSize(const char *szData, int nLen);
	// ����Buffer
	bool MakeBuffer();
	// ���
	int SplitPacket(const char *szData, int nLen);

protected:
	CSocketSource	*m_pSocketSource;
	SOCKET			 m_hSocket;

	//���յ���Ϣ��Size>m_nBufferSizeʱ��Ч�����ϲ㸺����
	//��ʾ����Ҫ�յ���Ϣ����
	uint32  m_nNeedMsgSize;
	uint32  m_nLastMsgLeft;			//����յ���Ϣ�ĳ���
	uint8   m_nMsgSizeByte;			//��Ϣ��ʽ��Sizeռ�õ��ֽ���(1,2,4,8)

	uint32  m_nBufferSize;			//��������С
	char   *m_szBuffer;

};

};

#endif
/*
* Copyright (C) 2005-2007 Zhang bao yuan(bolidezhang@gmail.com)
* All rights reserved.
* 
* �ļ����ƣ�SocketRunner.h
* ժ    Ҫ��Socket��������ӿ���
* ��    �ߣ��ű�Ԫ bolidezhang@gmail.com
* ������ڣ�2005/07/16
*
*/

#pragma once
#include "sync/ThreadGroup.h"

namespace SL
{

// Socket�¼��ķ�����
class SOCKETLIBRARY_API CSocketRunner
{
public:
	CSocketRunner(void);
	virtual ~CSocketRunner(void);

	virtual BOOL  Open(unsigned long nConcurrencyThreadNum = 0, unsigned long nWorkThreadNum = 4 ) = 0;
	virtual BOOL  Close() = 0;
	virtual BOOL  AssociateSocket(SOCKET hSocket, void *pPerHandle);
	virtual DWORD GetWorkThreadNum();

protected:

	//��ɶ˿ھ��
	HANDLE	        m_hCompletionPort; 

	//�����߳���
	DWORD			m_dwConcurrencyThreadNum;
	//�����߳���
	DWORD			m_dwWorkThreadNum;

	//�����߳���
	SYNC::CThreadGroup m_threadGroup;

};

};

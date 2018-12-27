//**********************************************************************
//
// 
// All rights reserved.
//
// This copy of Socketlib is licensed to you under the terms described 
// in the LICENSE.txt file included in this distribution.
//
//**********************************************************************

#include ".\tcprunner.h"
#include "SocketLib.h"
#include "SocketSource.h"
#include "SocketEvent.h"
namespace SL
{

CTcpRunner::CTcpRunner(void)
{
}

CTcpRunner::~CTcpRunner(void)
{
	Close();
}

BOOL CTcpRunner::Close()
{
	if (NULL == m_hCompletionPort)
		return FALSE;

	//ʹ�����߳��˳�
	for (DWORD i=0; i<m_dwWorkThreadNum; i++)
	{
		//�����˳���Ϣ
		::PostQueuedCompletionStatus(m_hCompletionPort,-1,-1,NULL);
	}
	CloseHandle(m_hCompletionPort);
	m_hCompletionPort = NULL;
	m_threadGroup.Stop(WAIT_TIMEOUT);
	m_threadGroup.Kill();
	return TRUE;
}

BOOL CTcpRunner::Open(unsigned long nConcurrencyThreadNum, unsigned long nWorkThreadNum)
{
	Close();

	if (nWorkThreadNum > 0)
		m_dwWorkThreadNum = nWorkThreadNum;

	if ( nConcurrencyThreadNum <= nWorkThreadNum )
		m_dwConcurrencyThreadNum = nConcurrencyThreadNum;
	else
		m_dwConcurrencyThreadNum = 0;

	//������ɶ˿ھ��
	m_hCompletionPort = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,m_dwConcurrencyThreadNum);
	if (INVALID_HANDLE_VALUE == m_hCompletionPort)
	{
#ifdef SHOW_PRINTFINFO
		printf("Create iocompletionPort failure!\r\n");
#endif
		return FALSE;
	}

    //����Socket�����߳���
	m_threadGroup.Start(CTcpRunner::Run, this, m_dwWorkThreadNum);

	return TRUE;
}

unsigned __stdcall CTcpRunner::Run(LPVOID lParam)
{
	CTcpRunner *pRun		= (CTcpRunner*)lParam;
	HANDLE hCompletionPort	= pRun->m_hCompletionPort;

	int		nRet;
	DWORD	nByteTransferred;
	BOOL	bSuccess;
	PPER_HANDLE_DATA	   pPerHandle;
	PPER_IO_OPERATION_DATA pPerIoData;

	while (1)
	{
		pPerHandle = NULL;
		pPerIoData = NULL;
		nByteTransferred = -1;
		bSuccess = ::GetQueuedCompletionStatus(hCompletionPort,
											&nByteTransferred,
											(LPDWORD)&pPerHandle,
											(LPOVERLAPPED*)&pPerIoData,
											INFINITE);
		//�˳��źŵ���˳��߳�
		if (-1 == nByteTransferred)
		{
			return 1;
		}
		//�ͻ����Ѿ��Ͽ����ӻ������ӳ��ִ���
		if (0 == nByteTransferred)
		{
			if (pPerHandle != NULL)
				pPerHandle->pSocketSource->Disconnect(pPerHandle->hSocket);
			continue;
		}
		if ( (!bSuccess) || (NULL==pPerIoData) || (NULL==pPerHandle) ) //�����쳣���
			continue;

		if (pPerIoData->OperType == RECV_POSTED)
		{//���ݽ���

			//��Ϣ����
			nRet = pPerHandle->pSocketSource->m_pSocketEvent->OnRecv(pPerHandle->pSocketSource,
				pPerHandle->hSocket, pPerHandle->pAttachInfo, pPerIoData->szBuffer, nByteTransferred);
			if (nRet >= 0)  //С��0����ʾ�ڴ�Socket�ϲ��ٽ�������
				pPerHandle->pSocketSource->PostRecv(pPerHandle->hSocket, pPerIoData);

		}
		else if (pPerIoData->OperType == SEND_POSTED)
		{//���ݷ������
			pPerHandle->pSocketSource->PostSend(pPerIoData);
			continue;
		}
	}

	ExitThread(0);
	return 0;
}

}

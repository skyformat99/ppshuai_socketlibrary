#include "StdAfx.h"
#include ".\testtask.h"
#include ".\testserverapp.h"

CTestTask::CTestTask(void)
{
}

CTestTask::~CTestTask(void)
{
}

int CTestTask::ProcessMessage(CSLMessageQueueNode& oNode)
{
	printf("tcprecv Socket:%ld msg:(%s) len:%d\r\n", oNode.attachID, oNode.msg.data(), oNode.msg.size());

	//���յ�������ֱ�ӷ��ؿͻ�
	m_pApp->m_tcpServer.Send(oNode.attachID, oNode.msg.data(), oNode.msg.size());
	printf("Socket:%ld sendmsg:(%s) len:%d\r\n", oNode.attachID, oNode.msg.data(), oNode.msg.size());

	return 1;
}
#pragma once

#include "../../socketlibrary/sync/threadmutex.h"
#include "../../socketlibrary/sltask.h"

using namespace SL;
class CTestServerApp;
class CTestTask : public CSLTask<SYNC::CThreadMutex>
{
public:
	CTestTask(void);
	virtual ~CTestTask(void);

	//��Ϣ������
	int ProcessMessage(CSLMessageQueueNode& oNode);
public:
	CTestServerApp *m_pApp;
};

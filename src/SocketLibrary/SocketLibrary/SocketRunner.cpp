//**********************************************************************
//
// 
// All rights reserved.
//
// This copy of Socketlib is licensed to you under the terms described 
// in the LICENSE.txt file included in this distribution.
//
//**********************************************************************

#include ".\socketrunner.h"
#include "SocketLib.h"
namespace SL
{

CSocketRunner::CSocketRunner(void)
	: m_hCompletionPort(NULL)
	, m_dwConcurrencyThreadNum(0)
{
	//Ĭ��Socket�߳���ΪCPU����������*2+2
	SYSTEM_INFO sys_Info;
	GetSystemInfo(&sys_Info);
	m_dwWorkThreadNum = sys_Info.dwNumberOfProcessors * 2 + 2;
}

CSocketRunner::~CSocketRunner(void)
{
}

inline BOOL CSocketRunner::AssociateSocket(SOCKET hSocket, void *pPerHandle)
{
	//������Socket����ɶ˿ڣ���������ڴ�ʱ���󶨵���ɶ˿�
	return (CreateIoCompletionPort((HANDLE)hSocket, m_hCompletionPort, (ULONG_PTR)pPerHandle, m_dwConcurrencyThreadNum) != NULL);
}

inline DWORD CSocketRunner::GetWorkThreadNum()
{
	return m_dwWorkThreadNum;
}

}

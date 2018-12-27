#pragma once
#include "../../socketlibrary/appbase.h"
#include "../../socketlibrary/applog.h"
#include "../../socketlibrary/tcprunner.h"
#include "../../socketlibrary/tcpserver.h"
#include "../../socketlibrary/tcpclient.h"
#include "../../socketlibrary/udpsource.h"
#include "../../socketlibrary/udprunner.h"
#include "../../socketlibrary/slcommondef.h"
#include "TestSocketEvent.h"

using namespace SL;
class CTestClientApp : public CAppBase
{
public:
	CTestClientApp(void);
	~CTestClientApp(void);

	virtual void DoReadyWork(); //����ǰ��׼������(������NT��������)
	virtual BOOL DoRun();
	virtual BOOL DoStop();

private:
	CAppLog				m_appLog;
	CTcpRunner			m_tcpRunner;
	CTcpClient			m_tcpHttp;     //����web��վ
	CTcpClient			m_tcpTest;     //��ͨ����
	CTestSocketEvent	m_testSocketEvent;

	CUdpRunner			m_udpRunner;
	CUdpSource			m_udpClient;

};

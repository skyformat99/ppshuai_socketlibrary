/*
* Copyright (C) 2005-2007 Zhang bao yuan(bolidezhang@gmail.com)
* All rights reserved.
* 
* �ļ����ƣ�AppLog.h
* ժ    Ҫ��ϵͳ��־��
* ��ǰ�汾��1.0.0.1018
* ��    �ߣ��ű�Ԫ bolidezhang@gmail.com
* ������ڣ�2005/10/18
*
*/

#ifndef APPLOG_H
#define APPLOG_H

#pragma once
#include <string>
#include "config.h"

namespace SL
{

class SOCKETLIBRARY_API CAppLog
{
public:

	//log����
	enum LOG_LEVEL
	{
		LOG_LEVEL_0 = 0, //����¼log
		LOG_LEVEL_1,
		LOG_LEVEL_2,
		LOG_LEVEL_3,
		LOG_LEVEL_4,
		LOG_LEVEL_5,
		LOG_LEVEL_6,
		LOG_LEVEL_7,
		LOG_LEVEL_8,
		LOG_LEVEL_LAST  //��߼���
	};

	CAppLog(void);
	virtual ~CAppLog(void);

	//������־�ļ�
	virtual bool BuildFile();
	//��־��������
	virtual bool OpenLog(LPCSTR pszLogPath, LPCSTR pszLogFileNamePrefix, 
		LOG_LEVEL nLogLevel = LOG_LEVEL_0, USHORT nEverydayLogFileNum = 1);
	virtual bool CloseLog();

    //��¼Log(��ע������Ϊʱ�䵥λ������־�ļ�)
	virtual bool WriteLog(LPCSTR pszLog, LPCSTR pszFileName, int nLine, LOG_LEVEL nLevel, bool bLevelEqual = false);

	//��¼Log(��ע������Ϊʱ�䵥λ������־�ļ�)
	virtual bool WriteLog(LPCSTR pszLog, LOG_LEVEL nLevel, bool bLevelEqual = false);

protected:
	FILE			*m_pFile;                 //�ļ�ָ��
	std::string	    m_strLogPath;             //LogĿ¼
	std::string     m_strLogFileNamePrefix;   //Log�ļ���(�������ļ���չ��������)
	std::string     m_strLogLastFileName;     //���һ�μ�¼Logʱ���ļ���
	LOG_LEVEL		m_nLogLevel;              //Log����
	USHORT          m_nEverydayLogFileNum;    //ÿ�����Log�ļ���
};

};

#endif
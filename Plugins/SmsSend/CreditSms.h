// SmsSend.h : SmsSend DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSmsSendApp
// �йش���ʵ�ֵ���Ϣ������� SmsSend.cpp
//

class CSmsSendApp : public CWinApp
{
public:
	CSmsSendApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

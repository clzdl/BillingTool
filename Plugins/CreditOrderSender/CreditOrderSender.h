// CreditOrderSender.h : CreditOrderSender DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCreditOrderSenderApp
// �йش���ʵ�ֵ���Ϣ������� CreditOrderSender.cpp
//

class CCreditOrderSenderApp : public CWinApp
{
public:
	CCreditOrderSenderApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

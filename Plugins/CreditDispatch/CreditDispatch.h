// CreditDispatch.h : CreditDispatch DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCreditDispatchApp
// �йش���ʵ�ֵ���Ϣ������� CreditDispatch.cpp
//

class CCreditDispatchApp : public CWinApp
{
public:
	CCreditDispatchApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

// FirstPrice.h : FirstPrice DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFirstPriceApp
// �йش���ʵ�ֵ���Ϣ������� FirstPrice.cpp
//

class CFirstPriceApp : public CWinApp
{
public:
	CFirstPriceApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

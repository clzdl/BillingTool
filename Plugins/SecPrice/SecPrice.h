// SecPrice.h : SecPrice DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSecPriceApp
// �йش���ʵ�ֵ���Ϣ������� SecPrice.cpp
//

class CSecPriceApp : public CWinApp
{
public:
	CSecPriceApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

// SettSecPrice.h : SettSecPrice DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSettSecPriceApp
// �йش���ʵ�ֵ���Ϣ������� SettSecPrice.cpp
//

class CSettSecPriceApp : public CWinApp
{
public:
	CSettSecPriceApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

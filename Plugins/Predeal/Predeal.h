// Predeal.h : Predeal DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPredealApp
// �йش���ʵ�ֵ���Ϣ������� Predeal.cpp
//

class CPredealApp : public CWinApp
{
public:
	CPredealApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

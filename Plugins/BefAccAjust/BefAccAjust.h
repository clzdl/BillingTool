// BefAccAjust.h : BefAccAjust DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBefAccAjustApp
// �йش���ʵ�ֵ���Ϣ������� BefAccAjust.cpp
//

class CBefAccAjustApp : public CWinApp
{
public:
	CBefAccAjustApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

// AftAcctAdjust.h : AftAcctAdjust DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAftAcctAdjustApp
// �йش���ʵ�ֵ���Ϣ������� AftAcctAdjust.cpp
//

class CAftAcctAdjustApp : public CWinApp
{
public:
	CAftAcctAdjustApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

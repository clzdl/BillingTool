// AggBill.h : AggBill DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAggBillApp
// �йش���ʵ�ֵ���Ϣ������� AggBill.cpp
//

class CAggBillApp : public CWinApp
{
public:
	CAggBillApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

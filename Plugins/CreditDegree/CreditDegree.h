// CreditDegree.h : CreditDegree DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCreditDegreeApp
// �йش���ʵ�ֵ���Ϣ������� CreditDegree.cpp
//

class CCreditDegreeApp : public CWinApp
{
public:
	CCreditDegreeApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

// PrefeeRestore.h : PrefeeRestore DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPrefeeRestoreApp
// �йش���ʵ�ֵ���Ϣ������� PrefeeRestore.cpp
//

class CPrefeeRestoreApp : public CWinApp
{
public:
	CPrefeeRestoreApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

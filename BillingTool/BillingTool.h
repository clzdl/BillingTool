
// BillingTool.h : BillingTool Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "ModuleContext.h"

// CBillingToolApp:
// �йش����ʵ�֣������ BillingTool.cpp
//

class CBillingToolApp : public CWinAppEx
{
public:
	CBillingToolApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL m_menuViewModule;
	BOOL m_menuViewProperty;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	void WriteString2StatusBar(CString str);

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBillingToolApp theApp;
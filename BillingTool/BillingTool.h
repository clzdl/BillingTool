
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

#define  MSG_WRITE_MSG2_STATUSBAR		WM_USER+1000
#define  MSG_WRITE_MSG2_LISTVIEW		WM_USER+1001


class ListViewData
{
public:
	ListViewData(CString phone, CString sence)
		:m_phone(phone),
		m_sence(sence)
	{
	}
	~ListViewData()
	{
	}
	CString m_phone;
	CString m_sence;
	CString m_result;
};

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

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern CBillingToolApp theApp;

// BillingTool.h : BillingTool 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "ModuleContext.h"

// CBillingToolApp:
// 有关此类的实现，请参阅 BillingTool.cpp
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


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
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
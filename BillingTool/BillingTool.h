
// BillingTool.h : BillingTool 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "ModuleContext.h"
#include "database/otlv4.h"

// CBillingToolApp:
// 有关此类的实现，请参阅 BillingTool.cpp
//
#include <vector>
/*
 自定义消息
*/
#define  MSG_WRITE_MSG2_STATUSBAR		WM_USER+1000
#define  MSG_WRITE_MSG2_LISTVIEW		WM_USER+1001
#define  MSG_PROPERY_REFRESH			WM_USER+1002


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
	void PushMsg(CString msg)
	{
		m_result.push_back(msg);
	}
	CString m_phone;
	CString m_sence;
	std::vector<CString> m_result;
};

class CBillingToolApp : public CWinAppEx
{
public:
	CBillingToolApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	CString GetExePath(void);
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
extern  otl_connect gDbConn;

#define  _mod_type_map(x)		\
	x( _common, _TEXT("公共"))	\
	x( _credit_dispatch, _TEXT("信控分发") )	\
	x( _bef_adjust, _TEXT("帐前调账") )	\
	x( _aft_adjust, _TEXT("账后调账") )	\
	x(_prefee_restore, _TEXT("预存返还") )	\
	x(_credit_degree, _TEXT("信用度评估"))	\
	x( _predeal, _TEXT("预处理") )	\
	x( _credit_sms, _TEXT("短信发送") )	\
	x( _sec_price, _TEXT("二次批价") )	\
	x( _sett_sec_price, _TEXT("结算二次批价"))	\
	x( _agg_bill, _TEXT("结算二次批价"))	\
	x( _first_price, _TEXT("标批"))	\
	x( _credit_sender, _TEXT("信控指令"))	\



#define   _gen_mod_type(e, c)	e,
enum ModuleType
{
	_mod_type_map(_gen_mod_type)
};

#undef _gen_mod_type

CString GetModuleNameByModuleType(ModuleType type);

// BillingTool.h : BillingTool Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "ModuleContext.h"
#include "database/otlv4.h"

// CBillingToolApp:
// �йش����ʵ�֣������ BillingTool.cpp
//
#include <vector>
/*
 �Զ�����Ϣ
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


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	CString GetExePath(void);
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
extern  otl_connect gDbConn;

#define  _mod_type_map(x)		\
	x( _common, _TEXT("����"))	\
	x( _credit_dispatch, _TEXT("�ſطַ�") )	\
	x( _bef_adjust, _TEXT("��ǰ����") )	\
	x( _aft_adjust, _TEXT("�˺����") )	\
	x(_prefee_restore, _TEXT("Ԥ�淵��") )	\
	x(_credit_degree, _TEXT("���ö�����"))	\
	x( _predeal, _TEXT("Ԥ����") )	\
	x( _credit_sms, _TEXT("���ŷ���") )	\
	x( _sec_price, _TEXT("��������") )	\
	x( _sett_sec_price, _TEXT("�����������"))	\
	x( _agg_bill, _TEXT("�����������"))	\
	x( _first_price, _TEXT("����"))	\
	x( _credit_sender, _TEXT("�ſ�ָ��"))	\



#define   _gen_mod_type(e, c)	e,
enum ModuleType
{
	_mod_type_map(_gen_mod_type)
};

#undef _gen_mod_type

CString GetModuleNameByModuleType(ModuleType type);
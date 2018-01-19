#include "stdafx.h"
#include "ModuleContext.h"
#include "otlv4.h"
#include "BillingTool.h"
#include "BillingToolView.h"
#include "MainFrm.h"
#include "PubFunc.h"

ModuleContext::ModuleContext(CBillingToolApp *app)
:m_dbConn(new otl_connect()),
 m_theApp(app),
 m_funcCString2String(CStringToString),
 m_funcString2CString(StringToCString),
 m_funcGetProperty(GetProperty)
{
	m_funcWriteString2StatusBar = &CBillingToolApp::WriteString2StatusBar;
	m_funcAddResult2List = &CBillingToolView::AddResult2ListCtrl;
}
ModuleContext::~ModuleContext()
{
	try
	{
		m_dbConn->rollback();
		m_dbConn->logoff();
	}
	catch (otl_exception &e) 
	{
		CString text;
		text.Format(_TEXT("code:%d,msg:%s,var_info:%s,stm_text:%s\n"), e.code, e.msg, e.var_info, e.stm_text);
	}
	
}


int ModuleContext::ConnectDb(std::string dbString)
{
	if (m_dbConn->connected)
		return SUCCESS;

	try
	{ 
		m_dbConn->rlogon(dbString.c_str(), false);
	}
	catch (otl_exception &e)
	{
		CString text;
		char errMsg[4096] = { 0 };
		sprintf_s(errMsg , "code:%d,msg:%s,var_info:%s,stm_text:%s", e.code, e.msg, e.var_info, e.stm_text);
		theApp.WriteString2StatusBar(StringToCString(errMsg,CP_ACP));
		return FAILURE;
	}

	return SUCCESS;
}

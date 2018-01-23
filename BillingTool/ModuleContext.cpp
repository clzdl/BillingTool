#include "stdafx.h"
#include "ModuleContext.h"
#include "BillingTool.h"
#include "BillingToolView.h"
#include "MainFrm.h"
#include "PubFunc.h"
#include "SshCmddExecutor.h"


ModuleContext::ModuleContext(CBillingToolApp *app)
	:m_dbConn(new otl_connect()),
	m_theApp(app),
	m_funcCString2String(CStringToString),
	m_funcString2CString(StringToCString),
	m_funcGetProperty(GetProperty),
	m_objSshCmdExecutor(new SshCmdExecutor())
{
	m_funcSshConnectAndInit = &SshCmdExecutor::ConnectAndInit;
	m_funcSshExecuteCmd = &SshCmdExecutor::ExecuteCmd;
	m_funcSshDisconnectAndFree = &SshCmdExecutor::DisconnectAndFree;
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
		char errMsg[4096] = { 0 };
		sprintf_s(errMsg, "code:%d,msg:%s,var_info:%s,stm_text:%s", e.code, e.msg, e.var_info, e.stm_text);
		CString text = StringToCString(errMsg, CP_ACP);
		theApp.GetMainWnd()->SendMessage(MSG_WRITE_MSG2_STATUSBAR, 0, (LPARAM)text.GetBuffer());
		text.ReleaseBuffer();

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
		char errMsg[4096] = { 0 };
		sprintf_s(errMsg , "code:%d,msg:%s,var_info:%s,stm_text:%s", e.code, e.msg, e.var_info, e.stm_text);
		CString text = StringToCString(errMsg, CP_ACP);
		theApp.GetMainWnd()->SendMessage(MSG_WRITE_MSG2_STATUSBAR, 0, (LPARAM)text.GetBuffer());
		text.ReleaseBuffer();

		return FAILURE;
	}

	return SUCCESS;
}

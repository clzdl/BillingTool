#include "stdafx.h"
#include "BusiFunc.h"
#include "../../BillingTool/ModuleContext.h"
#include "../../BillingTool/BillingTool.h"
#include "../../BillingTool/MainFrm.h"
#include "../../BillingTool/BillingToolView.h"
#include <string>

#include "Poco/Dynamic/Var.h"
#include "Poco/Dynamic/Pair.h"
#include "Poco/Dynamic/VarIterator.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/NetException.h"
#include "Poco/StreamCopier.h"

#define FAILURE		-1
#define SUCCESS		0

static CString GetSysTIme()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d%02d%02d%02d%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return result;
}


static std::string CStringToString(const CString& src, UINT codepage)
{
	std::string dst;
	if (src.IsEmpty())
	{
		dst.clear();
		return "";
	}

	int length = ::WideCharToMultiByte(codepage, 0, src, src.GetLength(), NULL, 0, NULL, NULL);
	dst.resize(length);
	::WideCharToMultiByte(codepage, 0, src, src.GetLength(), &dst[0], (int)dst.size(), NULL, NULL);

	return dst;
}

static CString StringToCString(const std::string& src, UINT codepage)
{
	CString dst;
	if (src.empty())
	{
		return  dst;
	}
	int length = ::MultiByteToWideChar(codepage, 0, src.data(), (int)src.size(), NULL, 0);
	WCHAR* pBuffer = dst.GetBufferSetLength(length);
	::MultiByteToWideChar(codepage, 0, src.data(), (int)src.size(), pBuffer, length);

	return dst;
}


void BusiFunc::TriggerStartUp(ModuleContext *ctx,void *ptr)
{
	CBillingToolView *pView = dynamic_cast<CBillingToolView*>(dynamic_cast<CMainFrame*>(ctx->m_theApp->GetMainWnd())->GetActiveView());
	try{
		std::string sql = "insert into ACC_JFTOCREDIT(acc_id, "
			"	user_id, "
			"	trade_type_code, "
			"	trade_id, "
			"	real_fee, "
			"	real_leave_fee, "
			"	recaver_tag, "
			"	cancel_tag, "
			"	deal_tag, "
			"	deal_info, "
			"	update_staff_id, "
			"	update_time, "
			"	remark) values(:v1<char[20]>,:v2<char[20]>,1100,:v3<char[20]>,0,0,0,0,0,'','jf-test',sysdate,'')";



		otl_stream otlStm;
		otlStm.open(1, sql.c_str(), *(ctx->m_dbConn));
		otlStm.set_commit(0);
		
		otlStm << ctx->m_funcCString2String(ctx->m_funcGetProperty(0, _TEXT("账户ID")), CP_ACP).c_str()
			<< ctx->m_funcCString2String(ctx->m_funcGetProperty(0, _TEXT("用户ID")), CP_ACP).c_str()
		    << ctx->m_funcCString2String(GetSysTIme(), CP_ACP).c_str();

		ctx->m_dbConn->commit();
	}
	catch (otl_exception &e)
	{
		char strExp[4096] = { 0 };
		sprintf_s(strExp,"code:%d,msg:%s,var_info:%s,stm_text:%s\n", e.code, e.msg, e.var_info, e.stm_text);
		CString exp = ctx->m_funcString2CString(strExp , CP_ACP);

		(ctx->m_theApp->*(ctx->m_funcWriteString2StatusBar))(exp);
		(pView->*(ctx->m_funcAddResult2List))(_TEXT("XXXXXXXXXXXXXXXXX"), _TEXT("触发信控开机"), _TEXT("触发失败."));
		return;
	}
	 
	(pView->*(ctx->m_funcAddResult2List))(_TEXT("XXXXXXXXXXXXXXXXX"),_TEXT("触发信控开机"),_TEXT("触发成功."));

}


static std::string CreateCreditJsonData(CString acctId , CString userId,CString fee)
{
	std::string result = "{";
	result += "\"ACCT_ID\":" + CStringToString(acctId, CP_UTF8) + ",";
	result += "\"UESR_ID\":" + CStringToString(userId, CP_UTF8) + ",";
	result += "\"ADD_ID\":" + CStringToString(GetSysTIme(), CP_UTF8) + ",";
	result += "\"TRADE_TYPE\":8001,";
	result += "\"THIS_FEE\":" + CStringToString(fee, CP_UTF8) + ",";
	result += "\"IN_TYPE\":\"1\"";
	result += "}";
	return result;
}


static int SendCreditPkg(ModuleContext *ctx,std::string srvIp , UINT port , std::string service, std::string pkg)
{
	try
	{
		Poco::Net::HTTPClientSession session(srvIp, port);
		session.setTimeout(Poco::Timespan(5, 0));
		Poco::Net::HTTPRequest httpReq(Poco::Net::HTTPRequest::HTTP_POST, service, Poco::Net::HTTPMessage::HTTP_1_1);
		httpReq.setContentType("application/json;charset=UTF-8");
		httpReq.set("User-Agent", "BillingTool");
		httpReq.setContentLength((int)pkg.length());
		session.sendRequest(httpReq) << pkg;

		Poco::Net::HTTPResponse response;
		std::istream& rs = session.receiveResponse(response);
		if (200 != response.getStatus())
			return FAILURE;

		std::stringstream ostr;
		Poco::StreamCopier::copyStream(rs, ostr);

		Poco::JSON::Parser parser;
		Poco::Dynamic::Var result = parser.parse(ostr.str());

		Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();
		Poco::Dynamic::Var retCode = object->get("RETURNCODE");

		if (retCode != SUCCESS)
		{
			Poco::Dynamic::Var errMsg = object->get("ERRORMSG");
			CString errMsg1 = ctx->m_funcString2CString(errMsg.toString(), CP_UTF8);
			(ctx->m_theApp->*(ctx->m_funcWriteString2StatusBar))(errMsg1);
			return FAILURE;
		}
	}

	catch (Poco::Exception &e)
	{
		(ctx->m_theApp->*(ctx->m_funcWriteString2StatusBar))(StringToCString(e.message(), CP_ACP));
		return FAILURE;
	}

	
	return SUCCESS;
}

void BusiFunc::TriggerStop(ModuleContext *ctx, void *ptr)
{
	CBillingToolView *pView = dynamic_cast<CBillingToolView*>(dynamic_cast<CMainFrame*>(ctx->m_theApp->GetMainWnd())->GetActiveView());

	std::string jsonString = CreateCreditJsonData(ctx->m_funcGetProperty(0, _TEXT("账户ID")) ,
												ctx->m_funcGetProperty(0, _TEXT("用户ID")),
												ctx->m_funcGetProperty(1, _TEXT("话单费用")));
	
	TRACE(ctx->m_funcString2CString(jsonString, CP_ACP));
	
	int result = SendCreditPkg(ctx, ctx->m_funcCString2String(ctx->m_funcGetProperty(0, _TEXT("IP地址")),CP_ACP),
					   _wtoi(ctx->m_funcGetProperty(0, _TEXT("端口号"))),
					   ctx->m_funcCString2String(ctx->m_funcGetProperty(1, _TEXT("触发停机服务地址")), CP_ACP), jsonString);

	if (SUCCESS != result)
	{
		(pView->*(ctx->m_funcAddResult2List))(_TEXT("XXXXXXXXXXXXXXXXX"), _TEXT("触发信控停机"), _TEXT("触发失败."));
		return;
	}

	(pView->*(ctx->m_funcAddResult2List))(_TEXT("XXXXXXXXXXXXXXXXX"), _TEXT("触发信控停机"), _TEXT("触发成功."));

}
#include "stdafx.h"
#include "BusiFunc.h"
#include "../../BillingTool/ModuleContext.h"
#include "../../BillingTool/BillingTool.h"
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
static CString GetSysUtcTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d%02d%02d%02d%02d%3d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond,st.wMilliseconds);
	return result;
}

static CString GetSysTIme()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d%02d%02d%02d%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return result;
}

static CString GetSysYMDTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d%02d"), st.wYear, st.wMonth, st.wDay);
	return result;
}

static CString GetSerialNo() 
{
	CString csSerial;
	SYSTEMTIME st;
	GetLocalTime(&st);
	csSerial.Format(_TEXT("%02d%02d%02d"), st.wHour,st.wMinute,st.wSecond);

	return csSerial;
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
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("测试号码")), _TEXT("触发信控开机"));
	resultViewData.m_result = _TEXT("触发成功.");
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
		ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_STATUSBAR, 0, (LPARAM)exp.GetBuffer());
		exp.ReleaseBuffer();
		
		resultViewData.m_result = _TEXT("触发失败.");
	}
	 
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

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
			CString text = StringToCString(errMsg.toString(), CP_UTF8);
			ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_STATUSBAR, 0, (LPARAM)text.GetBuffer());
			text.ReleaseBuffer();
			return FAILURE;
		}
	}

	catch (Poco::Exception &e)
	{
		CString text = StringToCString(e.message(), CP_ACP);
		ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_STATUSBAR, 0, (LPARAM)text.GetBuffer());
		return FAILURE;
	}

	
	return SUCCESS;
}

void BusiFunc::TriggerStopByNet(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("触发信控停机【NET】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string jsonString = CreateCreditJsonData(ctx->m_funcGetProperty(_common, _TEXT("账户ID")) ,
												ctx->m_funcGetProperty(_common, _TEXT("用户ID")),
												ctx->m_funcGetProperty(_credit_dispatch, _TEXT("话单费用")));
	
	TRACE(ctx->m_funcString2CString(jsonString, CP_ACP));
	
	int result = SendCreditPkg(ctx, ctx->m_funcCString2String(ctx->m_funcGetProperty(_common, _TEXT("IP地址")),CP_ACP),
					   _wtoi(ctx->m_funcGetProperty(_common, _TEXT("端口号"))),
					   ctx->m_funcCString2String(ctx->m_funcGetProperty(_credit_dispatch, _TEXT("触发停机服务地址")), CP_ACP), jsonString);

	if (SUCCESS != result)
	{
		resultViewData.m_result = _TEXT("触发失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}

static std::vector<std::string> BuildCreditFileContents(std::string acctId, std::string userId)
{
	std::vector<std::string> vec;
	std::string result;

	result += acctId;
	result += ",";

	result += userId;
	result += ",";

	result += "0,,";
	
	result += CStringToString(GetSysTIme() , CP_ACP);
	result += ",";

	result += CStringToString(GetSysUtcTime(), CP_ACP);
	result += ",";

	result += "8003,10,100,1000,1,1100,";

	result += CStringToString(GetSysYMDTime().Left(6), CP_ACP);
	result += ",";

	result += CStringToString(GetSysTIme(), CP_ACP);

	vec.push_back(result);
	return vec;

}
void BusiFunc::TriggerStopByFile(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("触发信控停机【FILE】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpCreditInFile = CStringToString(ctx->m_funcGetProperty(_credit_dispatch, _TEXT("信控分发文件入口")), CP_ACP) + "/tempCreditFile.dat";
	CString csCreditInFile = ctx->m_funcGetProperty(_credit_dispatch, _TEXT("信控分发文件入口"))
								+ _TEXT("/FX_BILL_") + GetSysYMDTime()+_TEXT("_") + GetSerialNo() + _TEXT("_.CCCC") + testNumber.Left(7) + _TEXT(".bill00.bilcredit");

	std::string creditInFile = CStringToString(csCreditInFile, CP_ACP);

	UINT port = 22;

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("触发失败.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpCreditInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("触发失败.");
			break;
		}

		std::vector<std::string> creditContent = BuildCreditFileContents(
						CStringToString(ctx->m_funcGetProperty(_common, _TEXT("账户ID")), CP_ACP),
						CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户ID")), CP_ACP));

		

		for(auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpCreditInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("触发失败.");
				break;
			}
		}
		
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpCreditInFile + " " + creditInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("触发失败.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}


static std::vector<std::string> BuildRemindFileContents(std::string acctId, std::string userId , std::string curVolume, std::string totalVolume, std::string baseVolume)
{
	std::vector<std::string> vec;
	//320150625837255,120150105193264,0,,20171109120138,20171109120138884948,8003,240,132110,110,1,10240,201711,20171031232505
	std::string result;
	result += acctId;
	result += ",";

	result += userId;
	result += ",";

	result += "0,,";

	result += CStringToString(GetSysTIme(), CP_ACP);
	result += ",";

	result += CStringToString(GetSysUtcTime(), CP_ACP);
	result += ",";

	result += "8003,";

	result += curVolume;
	result += ",";

	result += totalVolume;
	result += ",";

	//费用
	result += "0,";
	//触发类型
	result += "2,";

	result += baseVolume;
	result += ",";

	result += CStringToString(GetSysYMDTime().Left(6), CP_ACP);
	result += ",";

	result += CStringToString(GetSysTIme(), CP_ACP);

	vec.push_back(result);
	return vec;

}

void BusiFunc::TriggerRemindByFile(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("触发信控停机【FILE】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpCreditInFile = CStringToString(ctx->m_funcGetProperty(_credit_dispatch, _TEXT("信控分发文件入口")), CP_ACP) + "/tempCreditFile.dat";
	CString csCreditInFile = ctx->m_funcGetProperty(_credit_dispatch, _TEXT("信控分发文件入口"))
		+ _TEXT("/FX_BILL_") + GetSysYMDTime() + _TEXT("_") + GetSerialNo() + _TEXT("_.CCCC") + testNumber.Left(7) + _TEXT(".bill00.bilcredit");

	std::string creditInFile = CStringToString(csCreditInFile, CP_ACP);

	UINT port = 22;

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("触发失败.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpCreditInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("触发失败.");
			break;
		}

		std::vector<std::string> creditContent = BuildRemindFileContents(
			CStringToString(ctx->m_funcGetProperty(_common, _TEXT("账户ID")), CP_ACP),
			CStringToString(ctx->m_funcGetProperty(-_common, _TEXT("用户ID")), CP_ACP),
			CStringToString(ctx->m_funcGetProperty(_credit_dispatch, _TEXT("话单使用量")), CP_ACP),
			CStringToString(ctx->m_funcGetProperty(_credit_dispatch, _TEXT("截止本条话单前的总是用量")), CP_ACP),
			CStringToString(ctx->m_funcGetProperty(_credit_dispatch, _TEXT("用户总的基础量")), CP_ACP) );



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpCreditInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("触发失败.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpCreditInFile + " " + creditInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("触发失败.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
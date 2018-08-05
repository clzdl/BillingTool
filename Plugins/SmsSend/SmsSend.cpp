// SmsSend.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "SmsSend.h"
#include "../../BillingTool/PluginInterface.h"
#include "../../BillingTool/ViewTree.h"
#include "../../BillingTool/ModuleContext.h"
#include "../../BillingTool/BillingTool.h"
#include <vector>
#include "../UtilDll/UtilDll.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CSmsSendApp

BEGIN_MESSAGE_MAP(CSmsSendApp, CWinApp)
END_MESSAGE_MAP()


// CSmsSendApp 构造

CSmsSendApp::CSmsSendApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CSmsSendApp 对象

//CSmsSendApp theApp;


// CSmsSendApp 初始化

BOOL CSmsSendApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


static std::map<CString, PropertyGrid> modulePropertys = {
	{ _TEXT("文件入口"),
		{ _TEXT("/home/chengl/src/soPeriodSmsProcess/data/in"),nullptr , FALSE , }
	},
	{ _TEXT("HASTEN_POLICY_ID"),
		{ _TEXT("40000036"),nullptr , FALSE , }
	},
	{ _TEXT("LEAVE_REAL_FEE"),
		{ _TEXT("1000"),nullptr , FALSE , }
	},
	{ _TEXT("REAL_FEE"),
		{ _TEXT("2000"),nullptr , FALSE , }
	},
	{ _TEXT("CREDIT_VALUE"),
		{ _TEXT("3000"),nullptr , FALSE , }
	}
};


void PropertyInitilize(std::map<int, std::map<CString, PropertyGrid> > &gProperty)
{
	gProperty.insert(std::make_pair(_credit_sms, modulePropertys));
}

/*
#define BILL_URGING_PAY    7001 //催费提醒(余额阀值)
#define TRAFFIC_REMIND     7002 //流量提醒->单阀值(套餐内)/比例值(套餐内)/单阀值(套餐外)/单阀值(使用总量)
#define CONSUMPTION_REMIND 7003 //消费提醒-->话费相关不进行逻辑判断，直接插短信表
#define DOUBLE_STOP        3110 //信控停机 -->目前由分发处理
#define SINGLE_STOP        3120 //信控半停机 -->有处理
#define TRAFFIC_CAP        3111 //流量封顶 -->目前由chengl分发逻辑处理，由本程序发送短信
#define LAST_PAY_HASTEN    3200 //后付费催费-->后付费进入延期处理时
*/
void TriggerSmsSendFile(ModuleContext *ctx, void *ptr);
void TriggerOneWayStopMsg(ModuleContext *ctx, void *ptr);
void TriggerDoubleStopMsg(ModuleContext *ctx, void *ptr);
void TriggerNotEnoughBalanceMsg(ModuleContext *ctx, void *ptr);
void TriggerDataRemindMsg(ModuleContext *ctx, void *ptr);
void TriggerDataTopMsg(ModuleContext *ctx, void *ptr);
void TriggerPostPaypMsg(ModuleContext *ctx, void *ptr);


static _ItemCallBackDef moduleCallBackDef[] = {
	{ _credit_sms, TriggerSmsSendFile },
	{ _credit_sms, TriggerOneWayStopMsg },
	{ _credit_sms, TriggerDoubleStopMsg },
	{ _credit_sms, TriggerNotEnoughBalanceMsg },
	{ _credit_sms, TriggerDataRemindMsg },
	{ _credit_sms, TriggerDataTopMsg },
	{ _credit_sms, TriggerPostPaypMsg }};

void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("短信提醒"), 0, 0);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("生成短信文件"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[0])));

	tmpItem = viewTree->InsertItem(_T("触发单停短信"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[1])));

	tmpItem = viewTree->InsertItem(_T("触发双停短信"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[2])));

	tmpItem = viewTree->InsertItem(_T("触发余额不足短信"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[3])));
	
	tmpItem = viewTree->InsertItem(_T("触发流量使用短信"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[4])));

	tmpItem = viewTree->InsertItem(_T("触发流量封顶短信"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[5])));

	tmpItem = viewTree->InsertItem(_T("触发后付费用户催费短信"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[6])));
}

std::vector<std::string> BuildSmsContents(CString serialNumber, CString userId)
{
	/*
	17001810501|120150105227073|1|";"=>"\n"|尊敬的分享通信客户，您好！;您2016年9月账单129.00元（总消费129.00元，优惠及减免0.00元），其中：;套餐及固定费：129.00元;-基本套餐费：129.00元;缴费请访问10039.cc
	*/
	std::vector<std::string> result;
	std::string content = CommonUtil::CStringToString(serialNumber, CP_ACP);
	content += "|";
	content += CommonUtil::CStringToString(serialNumber, CP_ACP);
	content += "|";
	content += CommonUtil::CStringToString(_TEXT("1|\"; \"=>\"\\n\"|尊敬的分享通信客户，您好！;您2016年9月账单129.00元（总消费129.00元，优惠及减免0.00元），其中：;套餐及固定费：129.00元;-基本套餐费：129.00元;缴费请访问10039.cc"), CP_UTF8);
	result.push_back(content);
	return result;

}

std::vector<std::string> GetFiles(ModuleContext *ctx)
{
	std::vector<std::string> result;
	result.push_back(CommonUtil::CStringToString(ctx->m_funcGetProperty(_credit_sms, _TEXT("文件入口")), CP_ACP) + "/../tmp_smsSendFile");

	CString csInFile = ctx->m_funcGetProperty(_credit_sms, _TEXT("文件入口"))
		+ _TEXT("/smsSendFile") + CommonUtil::GetSysYMDTime() + _TEXT(".dat");

	result.push_back(CommonUtil::CStringToString(csInFile, CP_ACP));
	return result;
}

void TriggerSmsSendFile(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("生成短信文件"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files =  GetFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("触发失败.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("触发失败.");
			break;
		}

		std::vector<std::string> contents = BuildSmsContents(testNumber, ctx->m_funcGetProperty(_common, _TEXT("用户ID")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("触发失败.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("触发失败.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}

bool BuildHastenNotice(ModuleContext *ctx, CString userId, CString tradeTypeCode, CString policyId, 
									CString leaveRealFee,CString realFee,CString creditValue)
{
	try {
		std::string sql = "insert into CDT_HASTEN_NOTICE(trade_type_code, "
			"	user_id, "
			"	trade_id, "
			"	main_tag, "
			"	product_id, "
			"	leave_real_fee, "
			"	real_fee, "
			"	credit_value, "
			"	hasten_policy_id, "
			"	in_time, "
			"	hasten_times, "
			"	already_hasten, "
			"	exec_time,  "
			"	last_exec_time, "
			"	deal_tag, "
			"	region_id, "
			"	remark, "
			"	over_owe) "
			"	values(:v1<char[20]>, "
			"		:v2<char[20]>, "
			"		:v3<char[20]>, "
			"		0,999999,"
			"		:v4<char[20]>,:v5<char[20]>,:v6<char[20]>,:v7<char[20]>,"
			"		sysdate,0,0,sysdate,sysdate,0,'test','',0)";



		otl_stream otlStm;
		otlStm.open(1, sql.c_str(), *(ctx->m_dbConn));
		otlStm.set_commit(0);

		otlStm << CommonUtil::CStringToString(tradeTypeCode, CP_ACP).c_str()
			<< CommonUtil::CStringToString(userId, CP_ACP).c_str()
			<< CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP).c_str()
			<< CommonUtil::CStringToString(leaveRealFee, CP_ACP).c_str()
			<< CommonUtil::CStringToString(realFee, CP_ACP).c_str()
			<< CommonUtil::CStringToString(creditValue, CP_ACP).c_str()
			<< CommonUtil::CStringToString(policyId, CP_ACP).c_str();

		ctx->m_dbConn->commit();
	}
	catch (otl_exception &e)
	{
		char strExp[4096] = { 0 };
		sprintf_s(strExp, "code:%d,msg:%s,var_info:%s,stm_text:%s\n", e.code, e.msg, e.var_info, e.stm_text);
		CString exp = CommonUtil::StringToCString(strExp, CP_ACP);
		ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_STATUSBAR, 0, (LPARAM)exp.GetBuffer());
		exp.ReleaseBuffer();
		return false;
	}

	return true;
}


void TriggerOneWayStopMsg(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("触发单停短信"));
	resultViewData.m_result = _TEXT("触发成功.");

	if (!BuildHastenNotice(ctx, ctx->m_funcGetProperty(_common, _TEXT("用户ID")),
		_TEXT("3120"),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("HASTEN_POLICY_ID")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("LEAVE_REAL_FEE")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("REAL_FEE")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("CREDIT_VALUE"))))
	{
		resultViewData.m_result = _TEXT("触发失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerDoubleStopMsg(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("触发双停短信"));
	resultViewData.m_result = _TEXT("触发成功.");

	
	if (!BuildHastenNotice(ctx, ctx->m_funcGetProperty(0, _TEXT("用户ID")),
		_TEXT("3110"),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("HASTEN_POLICY_ID")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("LEAVE_REAL_FEE")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("REAL_FEE")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("CREDIT_VALUE"))))
	{
		resultViewData.m_result = _TEXT("触发失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}

void TriggerNotEnoughBalanceMsg(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("触发余额不足短信"));
	resultViewData.m_result = _TEXT("触发成功.");

	if (!BuildHastenNotice(ctx, ctx->m_funcGetProperty(0, _TEXT("用户ID")),
		_TEXT("7001"),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("HASTEN_POLICY_ID")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("LEAVE_REAL_FEE")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("REAL_FEE")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("CREDIT_VALUE"))))
	{
		resultViewData.m_result = _TEXT("触发失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}

void TriggerDataRemindMsg(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("触发流量使用短信"));
	resultViewData.m_result = _TEXT("触发成功.");

	/*
	ModuleContext *ctx, CString userId, CString tradeTypeCode, CString policyId,
	CString leaveRealFee,CString realFee,CString creditValue
	*/
	if (!BuildHastenNotice(ctx, ctx->m_funcGetProperty(0, _TEXT("用户ID")),
		_TEXT("7002"),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("HASTEN_POLICY_ID")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("LEAVE_REAL_FEE")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("REAL_FEE")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("CREDIT_VALUE"))))
	{
		resultViewData.m_result = _TEXT("触发失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
	
}
void TriggerDataTopMsg(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("触发流量封顶短信"));
	resultViewData.m_result = _TEXT("触发成功.");


	if (!BuildHastenNotice(ctx, ctx->m_funcGetProperty(0, _TEXT("用户ID")),
		_TEXT("3111"),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("HASTEN_POLICY_ID")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("LEAVE_REAL_FEE")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("REAL_FEE")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("CREDIT_VALUE"))))
	{
		resultViewData.m_result = _TEXT("触发失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void TriggerPostPaypMsg(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("触发后付费用户催费短信"));
	resultViewData.m_result = _TEXT("触发成功.");


	if (!BuildHastenNotice(ctx, ctx->m_funcGetProperty(0, _TEXT("用户ID")),
		_TEXT("3200"),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("HASTEN_POLICY_ID")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("LEAVE_REAL_FEE")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("REAL_FEE")),
		ctx->m_funcGetProperty(_credit_sms, _TEXT("CREDIT_VALUE"))))
	{
		resultViewData.m_result = _TEXT("触发失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
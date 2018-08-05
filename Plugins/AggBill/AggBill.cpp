// AggBill.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "AggBill.h"
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

// CAggBillApp

BEGIN_MESSAGE_MAP(CAggBillApp, CWinApp)
END_MESSAGE_MAP()


// CAggBillApp 构造

CAggBillApp::CAggBillApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CAggBillApp 对象

//CAggBillApp theApp;


// CAggBillApp 初始化

BOOL CAggBillApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}



void AggVc(ModuleContext *ctx, void *ptr);
void AggSms(ModuleContext *ctx, void *ptr);
void AggData(ModuleContext *ctx, void *ptr);


static _ItemCallBackDef moduleCallBackDef[] = {
	{ _agg_bill, AggVc },
	{ _agg_bill, AggSms },
	{ _agg_bill, AggData }};

void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("累账"), 0, 0);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("语音"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[0])));

	tmpItem = viewTree->InsertItem(_T("短信"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[1])));

	tmpItem = viewTree->InsertItem(_T("数据"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[2])));

}




std::vector<std::string> BuildCdrContent(CString cdrTag, CString callType, CString serialNumber, CString providerCode,
	CString peerNumber, CString duration, CString downVolume, CString upVolume, CString roamType, CString longType,
	BOOL ipCall, CString imsi, CString imei,CString userId, CString acctId, CString usageId,CString mainDisnctId)
{
	std::vector<std::string> result;
	std::string content;
	////
	content = "THEAD,";
	content += CommonUtil::CStringToString(CommonUtil::GetSysYMTime(), CP_ACP);
	content += ",v1,STDBILL_CDR";
	result.push_back(content);

	///
	content = CommonUtil::CStringToString(CommonUtil::GetSysUtcTime(), CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(cdrTag, CP_ACP);
	content += ",";

	content += "FX_XXXXXXXXXXXXXX.cdr";
	content += ",";

	content += CommonUtil::CStringToString(CommonUtil::GetSysYMTime(), CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(providerCode, CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(serialNumber, CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(peerNumber, CP_ACP);
	content += ",";

	content += "311,311,";

	content += CommonUtil::CStringToString(callType, CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(longType, CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(roamType, CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(downVolume, CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(upVolume, CP_ACP);
	content += ",";

	__int64 totalVolume = _wtoi64(downVolume) + _wtoi64(upVolume);
	TCHAR strTotalVolume[60];
	_i64tow_s(totalVolume, strTotalVolume, 60, 10);

	content += CommonUtil::CStringToString(CString(strTotalVolume), CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(duration, CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP);
	content += ",";

	if (TRUE == ipCall)
	{
		content += "IPCALL";
	}
	content += ",";
	

	content += CommonUtil::CStringToString(userId, CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(acctId, CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(usageId, CP_ACP);
	content += ",-1,0,100,10,90,100,10,90,311,0:3:100|1:1:50|1:0:2,100,,,0,10,";

	content += CommonUtil::CStringToString(mainDisnctId, CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP);
	content += ",,,,,";

	content += CommonUtil::CStringToString(CommonUtil::GetSysUtcTime(), CP_ACP);
	content += ",,,";

	content += CommonUtil::CStringToString(imsi, CP_ACP);
	content += ",";


	content += CommonUtil::CStringToString(imei, CP_ACP);
	content += ",";

	content += "FX_XXXXXXXXXXXXXXXXX.cdr,USA";

	result.push_back(content);

	///
	////
	content = "TEND,1,0,0,0,";
	result.push_back(content);

	return result;
}

std::vector<std::string> GetFiles(ModuleContext *ctx,CString testNumber , CString providerCode)
{
	std::vector<std::string> result;
	CString inPath = ctx->m_funcGetProperty(_agg_bill, _TEXT("文件入口"));
	///临时文件  0
	result.push_back(CommonUtil::CStringToString(inPath, CP_ACP) + "/../tmpFX_BILL.dat");

	CString csInFile = inPath + _TEXT("/FX_BILL_") + CommonUtil::GetSysYMDTime() + _TEXT("_") + CommonUtil::GetSerial() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	///正式文件  1
	result.push_back(CommonUtil::CStringToString(csInFile, CP_ACP));

	return result;
}

void AggVc(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	UINT port = 22;
	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("累账-语音"));
	resultViewData.m_result = _TEXT("触发成功.");

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

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_agg_bill, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("时长")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("上行流量")),
			_TEXT("R_LOCAL"), _TEXT("T_BT_PROVINCE"), FALSE,
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户ID")),
			ctx->m_funcGetProperty(_common, _TEXT("账户ID")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("费率ID")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("主资费ID"))
		);

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
void AggSms(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	UINT port = 22;
	
	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);
	

	ListViewData resultViewData(testNumber, _TEXT("累账-短信"));
	resultViewData.m_result = _TEXT("触发成功.");

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

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_agg_bill, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("时长")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("上行流量")),
			_TEXT("R_LOCAL"), _TEXT("T_BT_PROVINCE"), FALSE,
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户ID")),
			ctx->m_funcGetProperty(_common, _TEXT("账户ID")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("费率ID")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("主资费ID"))
		);

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
void AggData(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("累账-流量"));
	resultViewData.m_result = _TEXT("触发成功.");

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

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_NET"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_agg_bill, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("时长")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("上行流量")),
			_TEXT("R_LOCAL"), _TEXT("T_BT_PROVINCE"), FALSE,
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户ID")),
			ctx->m_funcGetProperty(_common, _TEXT("账户ID")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("费率ID")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("主资费ID"))
		);

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
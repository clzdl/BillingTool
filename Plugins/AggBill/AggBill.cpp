// AggBill.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "AggBill.h"
#include "../../BillingTool/PluginInterface.h"
#include "../../BillingTool/ViewTree.h"
#include "../../BillingTool/ModuleContext.h"
#include "../../BillingTool/BillingTool.h"
#include <vector>

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




static CString GetSysTIme()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d%02d%02d%02d%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return result;
}

static CString GetSysYMTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d"), st.wYear, st.wMonth);
	return result;
}

static CString GetSerial()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%02d%02d%02d"), st.wHour, st.wMinute, st.wSecond);
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


static CString GetSysUtcTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d%02d%02d%02d%02d%3d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	return result;
}

static CString GetSysTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d%02d%02d%02d%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return result;
}


void AggVc(ModuleContext *ctx, void *ptr);
void AggSms(ModuleContext *ctx, void *ptr);
void AggData(ModuleContext *ctx, void *ptr);




void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("累账"), 0, 0);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("语音"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(AggVc));

	tmpItem = viewTree->InsertItem(_T("短信"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(AggSms));

	tmpItem = viewTree->InsertItem(_T("数据"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(AggData));

}




std::vector<std::string> BuildCdrContent(CString cdrTag, CString callType, CString serialNumber, CString providerCode,
	CString peerNumber, CString duration, CString downVolume, CString upVolume, CString roamType, CString longType,
	BOOL ipCall, CString imsi, CString imei,CString userId, CString acctId, CString usageId,CString mainDisnctId)
{
	std::vector<std::string> result;
	std::string content;
	////
	content = "THEAD,";
	content += CStringToString(GetSysYMTime(), CP_ACP);
	content += ",v1,STDBILL_CDR";
	result.push_back(content);

	///
	content = CStringToString(GetSysUtcTime(), CP_ACP);
	content += ",";

	content += CStringToString(cdrTag, CP_ACP);
	content += ",";

	content += "FX_XXXXXXXXXXXXXX.cdr";
	content += ",";

	content += CStringToString(GetSysYMTime(), CP_ACP);
	content += ",";

	content += CStringToString(providerCode, CP_ACP);	
	content += ",";

	content += CStringToString(serialNumber, CP_ACP);
	content += ",";

	content += CStringToString(peerNumber, CP_ACP);
	content += ",";

	content += "311,311,";

	content += CStringToString(callType, CP_ACP);
	content += ",";

	content += CStringToString(longType, CP_ACP);
	content += ",";

	content += CStringToString(roamType, CP_ACP);
	content += ",";

	content += CStringToString(GetSysTime(), CP_ACP);
	content += ",";

	content += CStringToString(GetSysTime(), CP_ACP);
	content += ",";

	content += CStringToString(downVolume, CP_ACP);
	content += ",";

	content += CStringToString(upVolume, CP_ACP);
	content += ",";

	__int64 totalVolume = _wtoi64(downVolume) + _wtoi64(upVolume);
	TCHAR strTotalVolume[60];
	_i64tow_s(totalVolume, strTotalVolume, 60, 10);

	content += CStringToString(CString(strTotalVolume), CP_ACP);
	content += ",";

	content += CStringToString(duration, CP_ACP);
	content += ",";

	content += CStringToString(GetSysTime(), CP_ACP);
	content += ",";

	if (TRUE == ipCall)
	{
		content += "IPCALL";
	}
	content += ",";
	

	content += CStringToString(userId, CP_ACP);
	content += ",";

	content += CStringToString(acctId, CP_ACP);
	content += ",";

	content += CStringToString(usageId, CP_ACP);
	content += ",-1,0,100,10,90,100,10,90,311,0:3:100|1:1:50|1:0:2,100,,,0,10,";

	content += CStringToString(mainDisnctId, CP_ACP);
	content += ",";

	content += CStringToString(GetSysTime(), CP_ACP);
	content += ",,,,,";

	content += CStringToString(GetSysUtcTime(), CP_ACP);
	content += ",,,";

	content += CStringToString(imsi, CP_ACP);
	content += ",";


	content += CStringToString(imei, CP_ACP);
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
	result.push_back(CStringToString(inPath, CP_ACP) + "/../tmpFX_BILL.dat");

	CString csInFile = inPath + _TEXT("/FX_BILL_") + GetSysYMDTime() + _TEXT("_") + GetSerial() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	///正式文件  1
	result.push_back(CStringToString(csInFile, CP_ACP));

	return result;
}

void AggVc(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
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
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
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
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
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
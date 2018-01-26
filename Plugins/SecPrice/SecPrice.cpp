// SecPrice.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "SecPrice.h"
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

// CSecPriceApp

BEGIN_MESSAGE_MAP(CSecPriceApp, CWinApp)
END_MESSAGE_MAP()


// CSecPriceApp 构造

CSecPriceApp::CSecPriceApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CSecPriceApp 对象

//CSecPriceApp theApp;


// CSecPriceApp 初始化

BOOL CSecPriceApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
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

static CString GetSysYMDTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d%02d"), st.wYear, st.wMonth, st.wDay);
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

void TriggerVcLocalCdr(ModuleContext *ctx, void *ptr);
void TriggerVcLongCdr(ModuleContext *ctx, void *ptr);
void TriggerVcRoamInProviceCdr(ModuleContext *ctx, void *ptr);
void TriggerVcRoamProviceCdr(ModuleContext *ctx, void *ptr);
void TriggerVcLongInterCdr(ModuleContext *ctx, void *ptr);
void TriggerVcRoamInterCdr(ModuleContext *ctx, void *ptr);
void TriggerVcIpCallCdr(ModuleContext *ctx, void *ptr);
void TriggerVcDivertCdr(ModuleContext *ctx, void *ptr);
void TriggerVcCalledCdr(ModuleContext *ctx, void *ptr);


void TriggerSmsChnCdr(ModuleContext *ctx, void *ptr);
void TriggerSmsInterCdr(ModuleContext *ctx, void *ptr);
void TriggerSmsRoamCdr(ModuleContext *ctx, void *ptr);
void TriggerSmsCalledCdr(ModuleContext *ctx, void *ptr);



void TriggerDataInProvinceCdr(ModuleContext *ctx, void *ptr);
void TriggerDataProvinceCdr(ModuleContext *ctx, void *ptr);
void TriggerDataInterCdr(ModuleContext *ctx, void *ptr);

void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("二次批价"), 0, 0);

	HTREEITEM secItem = viewTree->InsertItem(_T("语音"), 0, 0, hRoot);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("市话"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcLocalCdr));

	tmpItem = viewTree->InsertItem(_T("长途"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcLongCdr));

	tmpItem = viewTree->InsertItem(_T("省内漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcRoamInProviceCdr));

	tmpItem = viewTree->InsertItem(_T("省际漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcRoamProviceCdr));

	tmpItem = viewTree->InsertItem(_T("国际长途"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcLongInterCdr));

	tmpItem = viewTree->InsertItem(_T("国际漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcRoamInterCdr));

	tmpItem = viewTree->InsertItem(_T("IP通话"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcIpCallCdr));

	tmpItem = viewTree->InsertItem(_T("呼转通话"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcDivertCdr));

	tmpItem = viewTree->InsertItem(_T("国内被叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcCalledCdr));

	secItem = viewTree->InsertItem(_T("短信"), 0, 0, hRoot);

	tmpItem = viewTree->InsertItem(_T("国内短信"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerSmsChnCdr));

	tmpItem = viewTree->InsertItem(_T("国际短信"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerSmsInterCdr));

	tmpItem = viewTree->InsertItem(_T("国际漫游短信"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerSmsRoamCdr));

	tmpItem = viewTree->InsertItem(_T("短信被叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerSmsCalledCdr));


	secItem = viewTree->InsertItem(_T("流量"), 0, 0, hRoot);

	tmpItem = viewTree->InsertItem(_T("省内流量"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerDataInProvinceCdr));

	tmpItem = viewTree->InsertItem(_T("省际流量"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerDataProvinceCdr));

	tmpItem = viewTree->InsertItem(_T("国际流量"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerDataInterCdr));

}





std::vector<std::string> BuildCdrContent(CString cdrTag,CString callType,CString serialNumber,CString providerCode,
	CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType, 
	BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei ,CString phoneRegion)
{
	std::vector<std::string> result;
	std::string content;
	////
	content = "THEAD,";
	content += CStringToString(GetSysYMTime(), CP_ACP);
	content += ",v1,STDBILL_CDR";
	result.push_back(content);

	///
	content = CStringToString(GetSysUtcTime(),CP_ACP);
	content += ",";

	content += CStringToString(cdrTag , CP_ACP);
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

	content += CStringToString(callType, CP_ACP);
	content += ",";

	content += ",,,,";

	content += CStringToString(GetSysTime(), CP_ACP);
	content += ",";

	content += ",";

	content += CStringToString(downVolume, CP_ACP);
	content += ",";

	content += CStringToString(upVolume, CP_ACP);
	content += ",";

	__int64 totalVolume = _wtoi64(downVolume) + _wtoi64(upVolume);
	TCHAR strTotalVolume[60];
	_i64tow_s(totalVolume, strTotalVolume , 60 , 10);
	
	content += CStringToString(CString(strTotalVolume), CP_ACP);
	content += ",";
		 
	content += CStringToString(duration, CP_ACP);
	content += ",";

	content += CStringToString(GetSysTime(), CP_ACP);
	content += ",";

	content += ",,,,,";

	content += CStringToString(roamType, CP_ACP);
	content += ",";

	content += CStringToString(roamNation, CP_ACP);
	content += ",";

	content += CStringToString(longType, CP_ACP);
	content += ",";

	if (TRUE == ipCall) 
	{
		content += "IPCALL";
	}
	content += ",,,,,";

	content += CStringToString(firstPriceFee, CP_ACP);
	content += ",,,,,0,6000001,0,";

	content += CStringToString(GetSysTime(), CP_ACP);
	content += ",";

	content += ",,,,";

	content += CStringToString(imsi, CP_ACP);
	content += ",";


	content += CStringToString(imei, CP_ACP);
	content += ",";

	content += "FX_XXXXXXXXXXXXXXXXX.cdr";
	
	result.push_back(content);

	///
	////
	content = "TEND,1,0,0,0,";
	result.push_back(content);

	return result;
}






void TriggerVcLocalCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath+ _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
												+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-本地市话"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
	CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType, 
	BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
								testNumber, providerCode,
								ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
								ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
								ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
								ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
								_TEXT("R_LOCAL"),_TEXT("T_LOCAL"),FALSE,_TEXT("CHN"),_TEXT("40"),
								ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
								ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
								ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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
void TriggerVcLongCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-国内长途"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_LOCAL"), _TEXT("T_BT_PROVINCE"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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
void TriggerVcRoamInProviceCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-省内漫游"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_IN_PROVINCE"), _TEXT("T_BT_PROVINCE"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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
void TriggerVcRoamProviceCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-省际漫游"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_PROVINCE"), _TEXT("T_BT_PROVINCE"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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
void TriggerVcLongInterCdr(ModuleContext *ctx, void *ptr) 
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-国际长途"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_LOCAL"), _TEXT("T_INTERNATIONAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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
void TriggerVcRoamInterCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-国际漫游"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_OUT_INTERNATIONAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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
void TriggerVcIpCallCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-IP通话"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), TRUE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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
void TriggerVcDivertCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-呼转通话"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("DIVERTING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), TRUE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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

void TriggerVcCalledCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-国内被叫"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLED"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), TRUE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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

void TriggerSmsChnCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-国内短信"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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
void TriggerSmsInterCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-国际短信"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_LOCAL"), _TEXT("T_INTERNATIONAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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

void TriggerSmsRoamCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-国际漫游短信"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_OUT_INTERNATIONAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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

void TriggerSmsCalledCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-国内被叫短信"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLED"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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

void TriggerDataInProvinceCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-省内流量"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_NET"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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
void TriggerDataProvinceCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-省际流量"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_NET"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_PROVINCE"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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
void TriggerDataInterCdr(ModuleContext *ctx, void *ptr)
{

	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("归属运营商"));
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("文件入口"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat";
	CString csInFile = inPath + _TEXT("/FX_ONE_") + GetSysYMDTime() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

	ListViewData resultViewData(testNumber, _TEXT("二批-国际漫游流量"));
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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_NET"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("时长")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("下行流量")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("上行流量")),
			_TEXT("R_OUT_INTERNATIONAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地"))
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

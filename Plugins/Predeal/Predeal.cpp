// Predeal.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "Predeal.h"
#include "../../BillingTool/PluginInterface.h"
#include "../../BillingTool/ViewTree.h"
#include "../../BillingTool/ModuleContext.h"
#include "../../BillingTool/BillingTool.h"
#include <vector>
#include <string>


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

// CPredealApp

BEGIN_MESSAGE_MAP(CPredealApp, CWinApp)
END_MESSAGE_MAP()


// CPredealApp 构造

CPredealApp::CPredealApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CPredealApp 对象

//CPredealApp theApp;


// CPredealApp 初始化

BOOL CPredealApp::InitInstance()
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


static CString GetSysYMDate()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d"), st.wYear, st.wMonth);
	return result;

}

static CString GetSysYMDDate()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d%02d"), st.wYear, st.wMonth,st.wDay);
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

/////
void CtccVcCHNCalling(ModuleContext *ctx, void *ptr);
void CtccVcCHNCalled(ModuleContext *ctx, void *ptr);
void CtccVcInterCalling(ModuleContext *ctx, void *ptr);
void CtccVcInterRoam(ModuleContext *ctx, void *ptr);

void CtccSmsCHNCalling(ModuleContext *ctx, void *ptr);
void CtccSmsCHNCalled(ModuleContext *ctx, void *ptr);
void CtccSmsInterCalling(ModuleContext *ctx, void *ptr);
void CtccSmsInterRoam(ModuleContext *ctx, void *ptr);

void CtccDataCHNCalling(ModuleContext *ctx, void *ptr);
void CtccDataInterCalling(ModuleContext *ctx, void *ptr);

////
void CmccVcCHNCalling(ModuleContext *ctx, void *ptr);
void CmccVcCHNCalled(ModuleContext *ctx, void *ptr);
void CmccVcInterCalling(ModuleContext *ctx, void *ptr);
void CmccVcInterRoam(ModuleContext *ctx, void *ptr);

void CmccSmsCHNCalling(ModuleContext *ctx, void *ptr);
void CmccSmsCHNCalled(ModuleContext *ctx, void *ptr);
void CmccSmsInterCalling(ModuleContext *ctx, void *ptr);
void CmccSmsInterRoam(ModuleContext *ctx, void *ptr);

void CmccDataCHNCalling(ModuleContext *ctx, void *ptr);
void CmccDataInterCalling(ModuleContext *ctx, void *ptr);

////
void CuccVcCHNCalling(ModuleContext *ctx, void *ptr);
void CuccVcCHNCalled(ModuleContext *ctx, void *ptr);
void CuccVcInterCalling(ModuleContext *ctx, void *ptr);
void CuccVcInterRoam(ModuleContext *ctx, void *ptr);

void CuccSmsCHNCalling(ModuleContext *ctx, void *ptr);
void CuccSmsCHNCalled(ModuleContext *ctx, void *ptr);
void CuccSmsInterCalling(ModuleContext *ctx, void *ptr);
void CuccSmsInterRoam(ModuleContext *ctx, void *ptr);

void CuccDataCHNCalling(ModuleContext *ctx, void *ptr);
void CuccDataInterCalling(ModuleContext *ctx, void *ptr);


void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("预处理功能"), 0, 0);
	viewTree->SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM secItem = viewTree->InsertItem(_T("电信"), 0, 0 , hRoot);
	///电信
	HTREEITEM tmpItem = viewTree->InsertItem(_T("语音-国内主叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccVcCHNCalling));

	tmpItem = viewTree->InsertItem(_T("语音-国内被叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccVcCHNCalled));

	tmpItem = viewTree->InsertItem(_T("语音-国级长途"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccVcInterCalling));

	tmpItem = viewTree->InsertItem(_T("语音-国级漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccVcInterRoam));

	tmpItem = viewTree->InsertItem(_T("短信-国内主叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccSmsCHNCalling));

	tmpItem = viewTree->InsertItem(_T("短信-国内被叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccSmsCHNCalled));

	tmpItem = viewTree->InsertItem(_T("短信-国际长途"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccSmsInterCalling));

	tmpItem = viewTree->InsertItem(_T("短信-国际漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccSmsInterRoam));

	tmpItem = viewTree->InsertItem(_T("流量-国内"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccDataCHNCalling));

	tmpItem = viewTree->InsertItem(_T("流量-国际"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccDataInterCalling));


	////
	secItem = viewTree->InsertItem(_T("移动"), 0, 0, hRoot);
	tmpItem = viewTree->InsertItem(_T("语音-国内主叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccVcCHNCalling));

	tmpItem = viewTree->InsertItem(_T("语音-国内被叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccVcCHNCalled));

	tmpItem = viewTree->InsertItem(_T("语音-国级长途"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccVcInterCalling));

	tmpItem = viewTree->InsertItem(_T("语音-国级漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccVcInterRoam));

	tmpItem = viewTree->InsertItem(_T("短信-国内主叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccSmsCHNCalling));

	tmpItem = viewTree->InsertItem(_T("短信-国内被叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccSmsCHNCalled));

	tmpItem = viewTree->InsertItem(_T("短信-国际长途"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccSmsInterCalling));

	tmpItem = viewTree->InsertItem(_T("短信-国际漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccSmsInterRoam));

	tmpItem = viewTree->InsertItem(_T("流量-国内"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccDataCHNCalling));

	tmpItem = viewTree->InsertItem(_T("流量-国际"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccDataInterCalling));

	///
	secItem = viewTree->InsertItem(_T("联通"), 0, 0, hRoot);

	tmpItem = viewTree->InsertItem(_T("语音-国内主叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccVcCHNCalling));

	tmpItem = viewTree->InsertItem(_T("语音-国内被叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccVcCHNCalled));

	tmpItem = viewTree->InsertItem(_T("语音-国级长途"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccVcInterCalling));

	tmpItem = viewTree->InsertItem(_T("语音-国级漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccVcInterRoam));

	tmpItem = viewTree->InsertItem(_T("短信-国内主叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccSmsCHNCalling));

	tmpItem = viewTree->InsertItem(_T("短信-国内被叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccSmsCHNCalled));

	tmpItem = viewTree->InsertItem(_T("短信-国际长途"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccSmsInterCalling));

	tmpItem = viewTree->InsertItem(_T("短信-国际漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccSmsInterRoam));

	tmpItem = viewTree->InsertItem(_T("流量-国内"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccDataCHNCalling));

	tmpItem = viewTree->InsertItem(_T("流量-国际"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccDataInterCalling));

}

std::vector<std::string> BuildCtccTCGPCdr(CString cdrType,CString sessionId , CString imsi,
											CString serialNumber,CString nationCode)
{

	std::vector<std::string> result;
	std::string content = "TBAT;CHN01;FX034;00200;";
	content += GetSysTIme() + ";";
	content += GetSysTIme() + ";";
	content += GetSysTIme() + ";";
	content += "3;11;TACC;RMB;CNY;0;01;0000000;100000;5;0;3;TNET;1;3;0;";
	result.push_back(content);
	///
	

	content = "TCGP;";
	content += "0;";
	content += "0;";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "32;";
	content += CStringToString(GetSysYMDate(), CP_ACP) + ";";
	content += CStringToString(cdrType, CP_ACP) + ";";
	content += CStringToString(sessionId, CP_ACP) + ";";
	content += CStringToString(sessionId, CP_ACP) + ";";
	content += CStringToString(sessionId, CP_ACP) + ";";
	content += "0;0;1;1;0;0;0;0;0;0;0;";
	content += imsi + ";";
	content += serialNumber + ";";
	content += "27.149.88.225;0;ctnet@mycdma.cn;";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "600;1;1;2;";
	content += CStringToString(nationCode, CP_ACP) + ";";
	content += "311;";
	content += ";;0;0;X;59;0;0;";
	content += "01:0:02:0;";
	content += "0;";
		
	

	result.push_back(content);


	///
	content = "TAUD;";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "0;0;0;1";
	result.push_back(content);
	return result;
}


std::vector<std::string> BuildCtccTCMOCdr(CString busiType, CString imsi, 
				CString serialNumber ,CString peerNumber,CString sessionId, CString nationCode,
				CString phoneLocation,CString imei)
{

	std::vector<std::string> result;
	std::string content = "TBAT;CHN01;FX034;00200;";
	content += GetSysTIme() + ";";
	content += GetSysTIme() + ";";
	content += GetSysTIme() + ";";
	content += "3;11;TACC;RMB;CNY;0;01;0000000;100000;5;0;3;TNET;1;3;0;";
	result.push_back(content);
	///

	 /*
	 TCMO;0;0;2018012431004091_118;31;201801;0;0;0;13922232551;0;0;0;0;0;0;0;0;0;0;0;
	 460037450872425;17008875555;13922232551;0;;;;20180124100622;17;30;CHN;755;12804855977;12804855977;11;
	 D;01:0:02:0:03:0;0:0;;
	 */
	content = "TCMO;";
	content += "0;";
	content += "0;";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "32;";
	content += CStringToString(GetSysYMDate(), CP_ACP) + ";";
	content += "0;";
	content += CStringToString(sessionId, CP_ACP) + ";";
	content += CStringToString(sessionId, CP_ACP) + ";";
	content += CStringToString(peerNumber, CP_ACP) + ";";
	content += "0;0;1;1;0;0;0;0;0;0;0;";
	content += imsi + ";";
	content += serialNumber + ";";
	content += peerNumber + ";";
	content += "18731173110;311;311;;";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "600;8613448728;";
	content += CStringToString(nationCode, CP_ACP) + ";";
	content += "311;";
	content += CStringToString(phoneLocation, CP_ACP) + ";";
	content += CStringToString(imei, CP_ACP) + ";";
	content += ";11;";
	if (_TEXT("VC") == busiType)
	{
		content += "D;";
	}
	else if(_TEXT("SMS") == busiType)
	{
		content += "E;";
	}

	content += "01:0:02:0:03:0;0:0;";
	result.push_back(content);


	///
	content = "TAUD;";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "0;0;0;1";
	result.push_back(content);
	return result;
}



std::vector<std::string> BuildCtccTCMTCdr(CString busiType, CString imsi,
	CString serialNumber, CString peerNumber, CString sessionId, CString nationCode,
	CString phoneLocation, CString imei)
{

	std::vector<std::string> result;
	std::string content = "TBAT;CHN01;FX034;00200;";
	content += GetSysTIme() + ";";
	content += GetSysTIme() + ";";
	content += GetSysTIme() + ";";
	content += "3;11;TACC;RMB;CNY;0;01;0000000;100000;5;0;3;TNET;1;3;0;";
	result.push_back(content);
	///

	/*
	TCMT;0;0;2018012431004091_50;31;201801;0;0;0;13824365878;0;0;0;0;0;0;0;0;0;0;0;
	460037411818321;17003632727;13824365878;20180124094921;1021;28;CHN;755;
	12813836481;12813836481;11;D;01:0:02:0:03:0;0:0;
	*/
	content = "TCMT;";
	content += "0;";
	content += "0;";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "32;";
	content += CStringToString(GetSysYMDate(), CP_ACP) + ";";
	content += "123123123123;";
	content += CStringToString(sessionId, CP_ACP) + ";";
	content += CStringToString(sessionId, CP_ACP) + ";";
	content += CStringToString(peerNumber, CP_ACP) + ";";
	content += "0;0;1;1;0;0;0;0;0;0;0;";
	content += imsi + ";";
	content += serialNumber + ";";
	content += peerNumber + ";";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "600;8613448728;";
	content += CStringToString(nationCode, CP_ACP) + ";";
	content += "311;";
	content += CStringToString(imei, CP_ACP) + ";";
	content += ";11;";
	if (_TEXT("VC") == busiType)
	{
		content += "D;";
	}
	else if (_TEXT("SMS") == busiType)
	{
		content += "E;";
	}

	content += "01:0:02:0:03:0;0:0;";
	result.push_back(content);


	///
	content = "TAUD;";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "0;0;0;1";
	result.push_back(content);
	return result;
}


void CtccVcCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国内主叫【电信】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125" +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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

		std::vector<std::string> creditContent = BuildCtccTCMOCdr( _TEXT("VC"),
										ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
										testNumber,
										ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
										ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
										_TEXT("CHN"),
										ctx->m_funcGetProperty(_common, _TEXT("用户归属地")),
										ctx->m_funcGetProperty(_common, _TEXT("用户IMEI"))	);



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CtccVcCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国内被叫【电信】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125"; +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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

		std::vector<std::string> creditContent = BuildCtccTCMTCdr(_TEXT("VC"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			_TEXT("CHN"),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CtccVcInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国际长途【电信】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125"; +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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

		std::vector<std::string> creditContent = BuildCtccTCMOCdr(_TEXT("VC"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			testNumber,
			_TEXT("00") + ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			_TEXT("CHN"),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CtccVcInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国际漫游【电信】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125"; +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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

		std::vector<std::string> creditContent = BuildCtccTCMOCdr(_TEXT("VC"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			_TEXT("USA"),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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

void CtccSmsCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国内主叫【电信】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125"; +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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

		std::vector<std::string> creditContent = BuildCtccTCMOCdr(_TEXT("SMS"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			_TEXT("CHN"),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CtccSmsCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国内主叫【电信】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125"; +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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

		std::vector<std::string> creditContent = BuildCtccTCMTCdr(_TEXT("SMS"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			_TEXT("CHN"),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CtccSmsInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际长途【电信】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125"; +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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

		std::vector<std::string> creditContent = BuildCtccTCMOCdr(_TEXT("SMS"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			testNumber,
			_TEXT("00") + ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			_TEXT("CHN"),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CtccSmsInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际漫游【电信】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125"; +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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

		std::vector<std::string> creditContent = BuildCtccTCMOCdr(_TEXT("SMS"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			_TEXT("USA"),
			ctx->m_funcGetProperty(_common, _TEXT("用户归属地")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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

void CtccDataCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际漫游【电信】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125"; +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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

		std::vector<std::string> creditContent = BuildCtccTCGPCdr(	
								ctx->m_funcGetProperty(_predeal, _TEXT("流量话单类型")),
								ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
								ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
								testNumber,	_TEXT("CHN") );



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CtccDataInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际漫游【电信】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125"; + _TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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

		std::vector<std::string> creditContent = BuildCtccTCGPCdr(
			ctx->m_funcGetProperty(_predeal, _TEXT("流量话单类型")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			testNumber, _TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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





////////////////
std::vector<std::string> BuildCmccTCGPCdr( CString imsi,CString imei,
	CString serialNumber, CString nationCode)
{

	std::vector<std::string> result;
	std::string content = "TBAT;CHN01;FX034;00200;";
	content += GetSysTIme() + ";";
	content += GetSysTIme() + ";";
	content += GetSysTIme() + ";";
	content += "3;11;TACC;RMB;CNY;0;01;0000000;100000;5;0;3;TNET;1;3;0;";
	result.push_back(content);
	///

	/*
	TCGP;240;;;;;;;;;460070539310756;17053931119;;CMNET;;20180124145000;1800;2308792663;DDB11893;DDB11899;
	;;8602730354780778;8602730354780778;21819;81881;X;10;0;1;00:0;;
	*/

	content = "TCGP;";
	if (_TEXT("CHN") == nationCode)
	{
		content += "311;";
	}
	else
	{
		content += "USACG;";
	}
	
	content += ";;;;;;;;";
	content += imsi + ";";
	content += serialNumber + ";";
	content += ";CMNET;;";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "600;0;0;DDB1ADFC;;;";
	content += CStringToString(imei, CP_ACP) + ";";
	content += "102400;102400;X;10;0;1;00:0;;";
	


	result.push_back(content);


	///
	content = "TAUD;";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "0;0;0;1";
	result.push_back(content);
	return result;
}


std::vector<std::string> BuildCmccTCMOCdr(CString busiType, CString imsi,
					CString serialNumber, CString peerNumber, CString nationCode)
{

	std::vector<std::string> result;
	std::string content = "TBAT;CHN01;FX034;00200;";
	content += GetSysTIme() + ";";
	content += GetSysTIme() + ";";
	content += GetSysTIme() + ";";
	content += "3;11;TACC;RMB;CNY;0;01;0000000;100000;5;0;3;TNET;1;3;0;";
	result.push_back(content);
	///

	/*
	TCMO;898;;;;;;;;;460070651109978;17065119777;15103697734;
	;;;;20180122185159;16;8613440983;;;866351036723560;866351036723560;11;D;00:0;;;1;0;0;
	*/
	content = "TCMO;";
	if (_TEXT("CHN") == nationCode)
	{
		content += "311;";
	}
	else
	{
		content += "USACG;";
	}

	content += ";;;;;;;;";

	content += imsi + ";";
	content += serialNumber + ";";
	content += peerNumber + ";";
	content += ";;;;";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "600;8613448728;";
	content += ";;866351036723560;866351036723560;11;";
	if (_TEXT("VC") == busiType)
	{
		content += "D;";
	}
	else if (_TEXT("SMS") == busiType)
	{
		content += "E;";
	}

	content += "00:0;;;1;0;0;";
	result.push_back(content);


	///
	content = "TAUD;";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "0;0;0;1";
	result.push_back(content);
	return result;
}



std::vector<std::string> BuildCmccTCMTCdr(CString busiType, CString imsi,
						CString serialNumber, CString peerNumber, CString nationCode)
{

	std::vector<std::string> result;
	std::string content = "TBAT;CHN01;FX034;00200;";
	content += GetSysTIme() + ";";
	content += GetSysTIme() + ";";
	content += GetSysTIme() + ";";
	content += "3;11;TACC;RMB;CNY;0;01;0000000;100000;5;0;3;TNET;1;3;0;";
	result.push_back(content);
	///

	/*
	TCMT;898;;;;;;;;;460070654908078;17065494045;13016286876;20180122183848;37;8613440981;
	;;013468002698720;013468002698720;11;D;00:0;;1;0;0;
	*/
	content = "TCMT;";
	if (_TEXT("CHN") == nationCode)
	{
		content += "311;";
	}
	else
	{
		content += "USACG;";
	}

	content += ";;;;;;;;";

	content += imsi + ";";
	content += serialNumber + ";";
	content += peerNumber + ";";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "600;8613448728;";
	content += ";;866351036723560;866351036723560;11;";
	if (_TEXT("VC") == busiType)
	{
		content += "D;";
	}
	else if (_TEXT("SMS") == busiType)
	{
		content += "E;";
	}

	content += "00:0;;1;0;0;";
	result.push_back(content);

	///
	content = "TAUD;";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += CStringToString(GetSysTIme(), CP_ACP) + ";";
	content += "0;0;0;1";
	result.push_back(content);
	return result;
}


void CmccVcCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国内主叫【移动】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125.CMCC" +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		
		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("VC"),
				ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
				testNumber,
				ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
				_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CmccVcCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国内被叫【移动】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125.CMCC" +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		CString busiType, CString imsi,
						CString serialNumber, CString peerNumber, CString nationCode
		*/
		std::vector<std::string> creditContent = BuildCmccTCMTCdr(_TEXT("VC"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CmccVcInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国际长途【移动】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125.CMCC" +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		CString busiType, CString imsi,
		CString serialNumber, CString peerNumber, CString nationCode
		*/
		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("VC"),
						ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
						testNumber,
						_TEXT("00") + ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
						_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CmccVcInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国际漫游【移动】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125.CMCC" +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		CString busiType, CString imsi,
		CString serialNumber, CString peerNumber, CString nationCode
		*/
		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("VC"),
												ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
												testNumber,
												ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
												_TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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

void CmccSmsCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国内主叫【移动】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125.CMCC" +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		CString busiType, CString imsi,
		CString serialNumber, CString peerNumber, CString nationCode
		*/
		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("SMS"),
								ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
								testNumber,
								ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
								_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CmccSmsCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国内主叫【移动】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125.CMCC" +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		CString busiType, CString imsi,
						CString serialNumber, CString peerNumber, CString nationCode
		*/
		std::vector<std::string> creditContent = BuildCmccTCMTCdr(_TEXT("SMS"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CmccSmsInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际长途【移动】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125.CMCC" +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		CString busiType, CString imsi,
		CString serialNumber, CString peerNumber, CString nationCode
		*/
		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("SMS"),
									ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
									testNumber,
									_TEXT("00") + ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
									_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CmccSmsInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际漫游【移动】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125.CMCC" +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		CString busiType, CString imsi,
		CString serialNumber, CString peerNumber, CString nationCode
		*/
		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("SMS"),
									ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
									testNumber,
									ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
									_TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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

void CmccDataCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际漫游【移动】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125.CMCC" +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		 CString imsi,CString imei,
	CString serialNumber, CString nationCode
		*/
		std::vector<std::string> creditContent = BuildCmccTCGPCdr(
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber, _TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CmccDataInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际漫游【移动】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempDCHN01FX03400125";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125.CMCC" +_TEXT(".") + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		CString imsi,CString imei,
		CString serialNumber, CString nationCode
		*/
		std::vector<std::string> creditContent = BuildCmccTCGPCdr(
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber, _TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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








////////////////
std::vector<std::string> BuildCuccTCGPCdr(CString imsi, CString imei,
	CString serialNumber, CString nationCode)
{

	std::vector<std::string> result;
	std::string content = "2003,11,1,";
	content += CStringToString(serialNumber, CP_ACP) + ",";
	content += CStringToString(GetSysTIme(), CP_ACP) + ",";
	content += CStringToString(GetSysTIme(), CP_ACP) + ",";
	content += "102400,102400,";
	content += CStringToString(imsi, CP_ACP) + ";";
	content += CStringToString(imei, CP_ACP) + ";";
	content += "311,10,0,,3GNET,46001,";
	if (_TEXT("CHN") == nationCode)
	{
		content += "1,";
	}
	else
	{
		content += "2,";
	}
	content += ",,,,,";
	result.push_back(content);

	return result;
}


std::vector<std::string> BuildCuccVcdr(CString callType, CString imsi,CString imei,
	CString serialNumber, CString peerNumber, CString roamType , CString longType)
{
	std::vector<std::string> result;
	std::string content = "2001,0,";
	

	if (_TEXT("CALLING") == callType)
	{
		content += "00,";
	}
	else
	{
		content += "01,";
	}
	content += "311,";

	if (_TEXT("CALLING") == callType)
	{
		content += CStringToString(serialNumber, CP_ACP) + ",10,";
		content += CStringToString(peerNumber, CP_ACP) + ",";
	}
	else
	{
		content += CStringToString(peerNumber, CP_ACP) + ",10,";
		content += CStringToString(serialNumber, CP_ACP) + ",";
	}
	content += "8617001200291,";
	content += CStringToString(GetSysTIme(), CP_ACP) + ",";
	content += "120,";
	content += CStringToString(imsi, CP_ACP) + ",";
	content += CStringToString(imei, CP_ACP) + ",";
	content += "10,cuc,";
	if (_TEXT("CHN") == roamType)
	{
		content += "2,10,";
	}
	else
	{
		content += "3,10,";
	}
	if (_TEXT("CHN") == longType)
	{
		content += "2,";
	}
	else 
	{
		content += "3,";
	}
	content += "0,,,,,,";

	result.push_back(content);
	return result;
}



std::vector<std::string> BuildCuccSmsCdr(CString callType, CString imsi,CString imei,
	CString serialNumber, CString peerNumber,CString roamType, CString longType)
{

	std::vector<std::string> result;
	std::string content = "2002,0,";


	if (_TEXT("CALLING") == callType)
	{
		if(roamType == _TEXT("CHN"))
		{
			content += "10,";
		}
		else
		{
			content += "18,";
		}
	}
	else
	{
		if (roamType == _TEXT("CHN"))
		{
			content += "11,";
		}
		else
		{
			content += "19,";
		}
	}

	if (_TEXT("CALLING") == callType)
	{
		content += CStringToString(serialNumber, CP_ACP) + ",";
		content += CStringToString(peerNumber, CP_ACP) + ",";
	}
	else
	{
		content += CStringToString(peerNumber, CP_ACP) + ",";
		content += CStringToString(serialNumber, CP_ACP) + ",";
	}
	content += CStringToString(GetSysTIme(), CP_ACP) + ",";
	content += CStringToString(imsi, CP_ACP) + ",";
	content += CStringToString(imei, CP_ACP) + ",";
	content += "10,";
	
	if (_TEXT("CHN") == longType)
	{
		content += "0,";
	}
	else
	{
		content += "1,";
	}
	content += "60,X451,861346523,X901,,,,,,";

	result.push_back(content);
	return result;
}


void CuccVcCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国内主叫【联通】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempSOSH0100000SJ";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/SOSH0100000SJ" + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		CString callType, CString imsi,CString imei,
	CString serialNumber, CString peerNumber, CString nationCode
		*/
		std::vector<std::string> creditContent = BuildCuccVcdr(_TEXT("CALLING"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			_TEXT("CHN"), _TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CuccVcCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国内被叫【联通】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempSOSH0100000SJ";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/SOSH0100000SJ" + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		std::vector<std::string> creditContent = BuildCuccVcdr(_TEXT("CALLED"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			_TEXT("CHN"), _TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CuccVcInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国际长途【联通】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempSOSH0100000SJ";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/SOSH0100000SJ" + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		std::vector<std::string> creditContent = BuildCuccVcdr(_TEXT("CALLED"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber,
			_TEXT("00") + ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			_TEXT("CHN"), _TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CuccVcInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国际漫游【联通】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempSOSH0100000SJ";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/SOSH0100000SJ" + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		std::vector<std::string> creditContent = BuildCuccVcdr(_TEXT("CALLED"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber,
			_TEXT("00") + ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			_TEXT("USA"), _TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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

void CuccSmsCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国内主叫【联通】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempSOSH0100000SJ";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/SOSH0100000SJ" + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		std::vector<std::string> creditContent = BuildCuccSmsCdr(_TEXT("CALLING"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			_TEXT("CHN"),_TEXT("CHN"));


		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CuccSmsCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国内主叫【联通】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempSOSH0100000SJ";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/SOSH0100000SJ" + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		CString callType, CString imsi,CString imei,
	CString serialNumber, CString peerNumber, CString longType
		*/
		std::vector<std::string> creditContent = BuildCuccSmsCdr(_TEXT("CALLED"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			_TEXT("CHN"),_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CuccSmsInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际长途【联通】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempSOSH0100000SJ";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/SOSH0100000SJ" + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		std::vector<std::string> creditContent = BuildCuccSmsCdr(_TEXT("CALLING"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			_TEXT("CHN"),_TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CuccSmsInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际漫游【联通】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempSOSH0100000SJ";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/SOSH0100000SJ" + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		std::vector<std::string> creditContent = BuildCuccSmsCdr(_TEXT("CALLING"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			_TEXT("USA"),_TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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

void CuccDataCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际漫游【移动】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempSOSH0100000SJ";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/SOSH0100000SJ" + GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		CString imsi, CString imei,
	CString serialNumber, CString nationCode
		*/
		std::vector<std::string> creditContent = BuildCuccTCGPCdr(
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber, _TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CuccDataInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际漫游【移动】"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/tempSOSH0100000SJ";
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/SOSH0100000SJ" +  GetSysYMDDate() + ".dat";
	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

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
		CString imsi,CString imei,
		CString serialNumber, CString nationCode
		*/
		std::vector<std::string> creditContent = BuildCuccTCGPCdr(
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber, _TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
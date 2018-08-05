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
#include "../UtilDll/UtilDll.h"
#include "../UtilDll/SshCmdExecutor.h"


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


static std::map<CString, PropertyGrid> modulePropertys = {
	{ _TEXT("对端号码"),
		{ _TEXT("18731173110"),nullptr , FALSE , }
	},
	{ _TEXT("SESSIONID"),
		{ _TEXT("Eadfkjla234"),nullptr , FALSE , }
	},
	{ _TEXT("文件入口"),
		{ _TEXT("/home/chengl/src/soPredealBin/data/in"),nullptr , FALSE , }
	},

	{ _TEXT("流量话单类型"),
		{ _TEXT("首单"),nullptr , TRUE ,{
				{ _TEXT("首单"),_TEXT("0") },
				{ _TEXT("中间单"),_TEXT("1") },
				{ _TEXT("尾单"),_TEXT("-1") },
			}
		}
	}
};

void PropertyInitilize(std::map<int, std::map<CString, PropertyGrid> > &gProperty)
{
	gProperty.insert(std::make_pair(_predeal, modulePropertys));
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



static _ItemCallBackDef moduleCallBackDef[] = {
	{ _predeal, CtccVcCHNCalling },
	{ _predeal, CtccVcCHNCalled },
	{ _predeal, CtccVcInterCalling },
	{ _predeal, CtccVcInterRoam },
	{ _predeal, CtccSmsCHNCalling },
	{ _predeal, CtccSmsCHNCalled },
	{ _predeal, CtccSmsInterCalling },
	{ _predeal, CtccSmsInterRoam },
	{ _predeal, CtccDataCHNCalling },
	{ _predeal, CtccDataInterCalling },
	{ _predeal, CmccVcCHNCalling },
	{ _predeal, CmccVcCHNCalled },
	{ _predeal, CmccVcInterCalling },
	{ _predeal, CmccVcInterRoam },
	{ _predeal, CmccSmsCHNCalling },
	{ _predeal, CmccSmsCHNCalled },
	{ _predeal, CmccSmsInterCalling },
	{ _predeal, CmccSmsInterRoam },
	{ _predeal, CmccDataCHNCalling },
	{ _predeal, CmccDataInterCalling },
	{ _predeal, CuccVcCHNCalling },
	{ _predeal, CuccVcCHNCalled },
	{ _predeal, CuccVcInterCalling },
	{ _predeal, CuccVcInterRoam },
	{ _predeal, CuccSmsCHNCalling },
	{ _predeal, CuccSmsCHNCalled },
	{ _predeal, CuccSmsInterCalling },
	{ _predeal, CuccSmsInterRoam },
	{ _predeal, CuccDataCHNCalling } ,
	{ _predeal, CuccDataInterCalling } 
};



void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("预处理"), 0, 0);

	HTREEITEM secItem = viewTree->InsertItem(_T("电信"), 0, 0 , hRoot);
	///电信
	HTREEITEM tmpItem = viewTree->InsertItem(_T("语音-国内主叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[0])));

	tmpItem = viewTree->InsertItem(_T("语音-国内被叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[1])));

	tmpItem = viewTree->InsertItem(_T("语音-国级长途"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[2])));

	tmpItem = viewTree->InsertItem(_T("语音-国级漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[3])));

	tmpItem = viewTree->InsertItem(_T("短信-国内主叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[4])));

	tmpItem = viewTree->InsertItem(_T("短信-国内被叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[5])));

	tmpItem = viewTree->InsertItem(_T("短信-国际长途"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[6])));

	tmpItem = viewTree->InsertItem(_T("短信-国际漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[7])));

	tmpItem = viewTree->InsertItem(_T("流量-国内"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[8])));

	tmpItem = viewTree->InsertItem(_T("流量-国际"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[9])));


	////
	secItem = viewTree->InsertItem(_T("移动"), 0, 0, hRoot);
	tmpItem = viewTree->InsertItem(_T("语音-国内主叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[10])));

	tmpItem = viewTree->InsertItem(_T("语音-国内被叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[11])));

	tmpItem = viewTree->InsertItem(_T("语音-国级长途"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[12])));

	tmpItem = viewTree->InsertItem(_T("语音-国级漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[13])));

	tmpItem = viewTree->InsertItem(_T("短信-国内主叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[14])));

	tmpItem = viewTree->InsertItem(_T("短信-国内被叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[15])));

	tmpItem = viewTree->InsertItem(_T("短信-国际长途"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[16])));

	tmpItem = viewTree->InsertItem(_T("短信-国际漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[17])));

	tmpItem = viewTree->InsertItem(_T("流量-国内"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[18])));

	tmpItem = viewTree->InsertItem(_T("流量-国际"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[19])));

	///
	secItem = viewTree->InsertItem(_T("联通"), 0, 0, hRoot);

	tmpItem = viewTree->InsertItem(_T("语音-国内主叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[20])));

	tmpItem = viewTree->InsertItem(_T("语音-国内被叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[21])));

	tmpItem = viewTree->InsertItem(_T("语音-国级长途"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[22])));

	tmpItem = viewTree->InsertItem(_T("语音-国级漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[23])));

	tmpItem = viewTree->InsertItem(_T("短信-国内主叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[24])));

	tmpItem = viewTree->InsertItem(_T("短信-国内被叫"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[25])));

	tmpItem = viewTree->InsertItem(_T("短信-国际长途"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[26])));

	tmpItem = viewTree->InsertItem(_T("短信-国际漫游"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[27])));

	tmpItem = viewTree->InsertItem(_T("流量-国内"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[28])));

	tmpItem = viewTree->InsertItem(_T("流量-国际"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[29])));

}

std::vector<std::string> BuildCtccTCGPCdr(CString cdrType,CString sessionId , CString imsi,
											CString serialNumber,CString nationCode)
{

	std::vector<std::string> result;
	std::string content = "TBAT;CHN01;FX034;00200;";
	content += CommonUtil::GetSysTime() + ";";
	content += CommonUtil::GetSysTime() + ";";
	content += CommonUtil::GetSysTime() + ";";
	content += "3;11;TACC;RMB;CNY;0;01;0000000;100000;5;0;3;TNET;1;3;0;";
	result.push_back(content);
	///
	

	content = "TCGP;";
	content += "0;";
	content += "0;";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += "32;";
	content += CommonUtil::CStringToString(CommonUtil::GetSysYMTime(), CP_ACP) + ";";
	content += CommonUtil::CStringToString(cdrType, CP_ACP) + ";";
	content += CommonUtil::CStringToString(sessionId, CP_ACP) + ";";
	content += CommonUtil::CStringToString(sessionId, CP_ACP) + ";";
	content += CommonUtil::CStringToString(sessionId, CP_ACP) + ";";
	content += "0;0;1;1;0;0;0;0;0;0;0;";
	content += imsi + ";";
	content += serialNumber + ";";
	content += "27.149.88.225;0;ctnet@mycdma.cn;";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += "600;1;1;2;";
	content += CommonUtil::CStringToString(nationCode, CP_ACP) + ";";
	content += "311;";
	content += ";;0;0;X;59;0;0;";
	content += "01:0:02:0;";
	content += "0;";
		
	

	result.push_back(content);


	///
	content = "TAUD;";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
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
	content += CommonUtil::GetSysTime() + ";";
	content += CommonUtil::GetSysTime() + ";";
	content += CommonUtil::GetSysTime() + ";";
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
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += "32;";
	content += CommonUtil::CStringToString(CommonUtil::GetSysYMTime(), CP_ACP) + ";";
	content += "0;";
	content += CommonUtil::CStringToString(sessionId, CP_ACP) + ";";
	content += CommonUtil::CStringToString(sessionId, CP_ACP) + ";";
	content += CommonUtil::CStringToString(peerNumber, CP_ACP) + ";";
	content += "0;0;1;1;0;0;0;0;0;0;0;";
	content += imsi + ";";
	content += serialNumber + ";";
	content += peerNumber + ";";
	content += "18731173110;311;311;;";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += "600;8613448728;";
	content += CommonUtil::CStringToString(nationCode, CP_ACP) + ";";
	content += "311;";
	content += CommonUtil::CStringToString(phoneLocation, CP_ACP) + ";";
	content += CommonUtil::CStringToString(imei, CP_ACP) + ";";
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
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
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
	content += CommonUtil::GetSysTime() + ";";
	content += CommonUtil::GetSysTime() + ";";
	content += CommonUtil::GetSysTime() + ";";
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
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += "32;";
	content += CommonUtil::CStringToString(CommonUtil::GetSysYMTime(), CP_ACP) + ";";
	content += "123123123123;";
	content += CommonUtil::CStringToString(sessionId, CP_ACP) + ";";
	content += CommonUtil::CStringToString(sessionId, CP_ACP) + ";";
	content += CommonUtil::CStringToString(peerNumber, CP_ACP) + ";";
	content += "0;0;1;1;0;0;0;0;0;0;0;";
	content += imsi + ";";
	content += serialNumber + ";";
	content += peerNumber + ";";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += "600;8613448728;";
	content += CommonUtil::CStringToString(nationCode, CP_ACP) + ";";
	content += "311;";
	content += CommonUtil::CStringToString(imei, CP_ACP) + ";";
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
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += "0;0;0;1";
	result.push_back(content);
	return result;
}

std::vector<std::string> GetCtccFiles(ModuleContext *ctx)
{
	std::vector<std::string> result;
	result.push_back(CommonUtil::CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/../tempDCHN01FX03400125");

	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125" + _TEXT(".") + CommonUtil::GetSysYMTime() + ".dat";
	result.push_back(CommonUtil::CStringToString(csInFile, CP_ACP));

	return result;
}

void CtccVcCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国内主叫【电信】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);
	

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor ->GetErrMsg());
			resultViewData.PushMsg( _TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
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
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}


		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CtccVcCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国内被叫【电信】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
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
			if (!result)
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CtccVcInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国际长途【电信】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
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
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CtccVcInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国际漫游【电信】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
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
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}

void CtccSmsCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国内主叫【电信】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
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
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CtccSmsCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国内主叫【电信】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
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
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);


}
void CtccSmsInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际长途【电信】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
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
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CtccSmsInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际漫游【电信】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
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
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}

void CtccDataCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("流量-国内【电信】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		std::vector<std::string> creditContent = BuildCtccTCGPCdr(	
								ctx->m_funcGetProperty(_predeal, _TEXT("流量话单类型")),
								ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
								ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
								testNumber,	_TEXT("CHN") );



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CtccDataInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("流量-国际【电信】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		std::vector<std::string> creditContent = BuildCtccTCGPCdr(
			ctx->m_funcGetProperty(_predeal, _TEXT("流量话单类型")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			testNumber, _TEXT("USA"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}





////////////////
std::vector<std::string> BuildCmccTCGPCdr( CString imsi,CString imei,
	CString serialNumber, CString nationCode)
{

	std::vector<std::string> result;
	std::string content = "TBAT;CHN01;FX034;00200;";
	content += CommonUtil::GetSysTime() + ";";
	content += CommonUtil::GetSysTime() + ";";
	content += CommonUtil::GetSysTime() + ";";
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
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += "600;0;0;DDB1ADFC;;;";
	content += CommonUtil::CStringToString(imei, CP_ACP) + ";";
	content += "102400;102400;X;10;0;1;00:0;;";
	


	result.push_back(content);


	///
	content = "TAUD;";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += "0;0;0;1";
	result.push_back(content);
	return result;
}


std::vector<std::string> BuildCmccTCMOCdr(CString busiType, CString imsi,
					CString serialNumber, CString peerNumber, CString nationCode)
{

	std::vector<std::string> result;
	std::string content = "TBAT;CHN01;FX034;00200;";
	content += CommonUtil::GetSysTime() + ";";
	content += CommonUtil::GetSysTime() + ";";
	content += CommonUtil::GetSysTime() + ";";
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
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
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
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += "0;0;0;1";
	result.push_back(content);
	return result;
}



std::vector<std::string> BuildCmccTCMTCdr(CString busiType, CString imsi,
						CString serialNumber, CString peerNumber, CString nationCode)
{

	std::vector<std::string> result;
	std::string content = "TBAT;CHN01;FX034;00200;";
	content += CommonUtil::GetSysTime() + ";";
	content += CommonUtil::GetSysTime() + ";";
	content += CommonUtil::GetSysTime() + ";";
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
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
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
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ";";
	content += "0;0;0;1";
	result.push_back(content);
	return result;
}

std::vector<std::string> GetCmccFiles(ModuleContext *ctx)
{
	std::vector<std::string> result;
	result.push_back(CommonUtil::CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/../tempDCHN01FX03400125");
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/CDCHN01FX03400125.CMCC" + _TEXT(".") + CommonUtil::GetSysYMTime() + ".dat";
	result.push_back(CommonUtil::CStringToString(csInFile, CP_ACP));
	return result;
}

void CmccVcCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国内主叫【移动】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		
		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("VC"),
				ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
				testNumber,
				ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
				_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CmccVcCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国内被叫【移动】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		std::vector<std::string> creditContent = BuildCmccTCMTCdr(_TEXT("VC"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CmccVcInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国际长途【移动】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("VC"),
						ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
						testNumber,
						_TEXT("00") + ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
						_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CmccVcInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国际漫游【移动】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("VC"),
												ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
												testNumber,
												ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
												_TEXT("USA"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}

void CmccSmsCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国内主叫【移动】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("SMS"),
								ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
								testNumber,
								ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
								_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CmccSmsCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国内主叫【移动】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		std::vector<std::string> creditContent = BuildCmccTCMTCdr(_TEXT("SMS"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);


}
void CmccSmsInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际长途【移动】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
	
		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("SMS"),
									ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
									testNumber,
									_TEXT("00") + ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
									_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CmccSmsInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际漫游【移动】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("SMS"),
									ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
									testNumber,
									ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
									_TEXT("USA"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}

void CmccDataCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("流量-国内【移动】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		std::vector<std::string> creditContent = BuildCmccTCGPCdr(
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber, _TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CmccDataInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("流量-国际【移动】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		
		std::vector<std::string> creditContent = BuildCmccTCGPCdr(
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber, _TEXT("USA"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}



////////////////
std::vector<std::string> BuildCuccTCGPCdr(CString imsi, CString imei,
	CString serialNumber, CString nationCode)
{

	std::vector<std::string> result;
	std::string content = "2003,11,1,";
	content += CommonUtil::CStringToString(serialNumber, CP_ACP) + ",";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ",";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ",";
	content += "102400,102400,";
	content += CommonUtil::CStringToString(imsi, CP_ACP) + ";";
	content += CommonUtil::CStringToString(imei, CP_ACP) + ";";
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
		content += CommonUtil::CStringToString(serialNumber, CP_ACP) + ",10,";
		content += CommonUtil::CStringToString(peerNumber, CP_ACP) + ",";
	}
	else
	{
		content += CommonUtil::CStringToString(peerNumber, CP_ACP) + ",10,";
		content += CommonUtil::CStringToString(serialNumber, CP_ACP) + ",";
	}
	content += "8617001200291,";
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ",";
	content += "120,";
	content += CommonUtil::CStringToString(imsi, CP_ACP) + ",";
	content += CommonUtil::CStringToString(imei, CP_ACP) + ",";
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
		content += CommonUtil::CStringToString(serialNumber, CP_ACP) + ",";
		content += CommonUtil::CStringToString(peerNumber, CP_ACP) + ",";
	}
	else
	{
		content += CommonUtil::CStringToString(peerNumber, CP_ACP) + ",";
		content += CommonUtil::CStringToString(serialNumber, CP_ACP) + ",";
	}
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP) + ",";
	content += CommonUtil::CStringToString(imsi, CP_ACP) + ",";
	content += CommonUtil::CStringToString(imei, CP_ACP) + ",";
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

std::vector<std::string> GetCuccFiles(ModuleContext *ctx)
{
	std::vector<std::string> result;
	result.push_back(CommonUtil::CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")), CP_ACP) + "/../tempSOSH0100000SJ");
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("文件入口")) + "/SOSH0100000SJ" + CommonUtil::GetSysYMDTime() + ".dat";
	result.push_back(CommonUtil::CStringToString(csInFile, CP_ACP));
	return result;
}

void CuccVcCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国内主叫【联通】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		
		std::vector<std::string> creditContent = BuildCuccVcdr(_TEXT("CALLING"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			_TEXT("CHN"), _TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CuccVcCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国内被叫【联通】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
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
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CuccVcInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国际长途【联通】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
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
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CuccVcInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("语音-国际漫游【联通】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
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
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}

void CuccSmsCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国内主叫【联通】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
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
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CuccSmsCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国内主叫【联通】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		std::vector<std::string> creditContent = BuildCuccSmsCdr(_TEXT("CALLED"),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("对端号码")),
			_TEXT("CHN"),_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);


}
void CuccSmsInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际长途【联通】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
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
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CuccSmsInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("短信-国际漫游【联通】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
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
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}

void CuccDataCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("流量-国内【联通】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}


		std::vector<std::string> creditContent = BuildCuccTCGPCdr(
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber, _TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void CuccDataInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("流量-国际【联通】"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP地址")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("测试号码"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		std::vector<std::string> creditContent = BuildCuccTCGPCdr(
			ctx->m_funcGetProperty(_common, _TEXT("用户IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("用户IMEI")),
			testNumber, _TEXT("USA"));



		for (auto it : creditContent)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo \"" + it + "\" >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("触发失败."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("触发失败."));
			break;
		}

		resultViewData.PushMsg(_TEXT("触发成功."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
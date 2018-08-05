// SecPrice.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "SecPrice.h"
#include "../../BillingTool/PluginInterface.h"
#include "../../BillingTool/ViewTree.h"
#include "../../BillingTool/ModuleContext.h"
#include "../../BillingTool/BillingTool.h"
#include <vector>
#include "../UtilDll/UtilDll.h"
#include "../UtilDll/SshCmdExecutor.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CSecPriceApp

BEGIN_MESSAGE_MAP(CSecPriceApp, CWinApp)
END_MESSAGE_MAP()


// CSecPriceApp ����

CSecPriceApp::CSecPriceApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CSecPriceApp ����

//CSecPriceApp theApp;


// CSecPriceApp ��ʼ��

BOOL CSecPriceApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


static std::map<CString, PropertyGrid> modulePropertys = {
	{ _TEXT("�ļ����"),
		{ _TEXT("/home/chengl/src/BillRate/data/in"),nullptr , FALSE , }
	},
	{ _TEXT("�Զ˺���"),
		{ _TEXT("18645005420"),nullptr , FALSE , }
	},
	{ _TEXT("ʱ��"),
		{ _TEXT("1000"),nullptr , FALSE , }
	},
	{ _TEXT("��������"),
		{ _TEXT("102400"),nullptr , FALSE , }
	},
	{ _TEXT("��������"),
		{ _TEXT("102400"),nullptr , FALSE , }
	}
};


void PropertyInitilize(std::map<int, std::map<CString, PropertyGrid> > &gProperty)
{
	gProperty.insert(std::make_pair(_sec_price, modulePropertys));
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



static _ItemCallBackDef moduleCallBackDef[] = {
	{ _sec_price, TriggerVcLocalCdr },
	{ _sec_price, TriggerVcLongCdr },
	{ _sec_price, TriggerVcRoamInProviceCdr },
	{ _sec_price, TriggerVcRoamProviceCdr },
	{ _sec_price, TriggerVcLongInterCdr },
	{ _sec_price, TriggerVcRoamInterCdr },
	{ _sec_price, TriggerVcIpCallCdr },
	{ _sec_price, TriggerVcDivertCdr },
	{ _sec_price, TriggerVcCalledCdr },
	{ _sec_price, TriggerSmsChnCdr },
	{ _sec_price, TriggerSmsInterCdr },
	{ _sec_price, TriggerSmsRoamCdr },
	{ _sec_price, TriggerSmsCalledCdr },
	{ _sec_price, TriggerDataInProvinceCdr },
	{ _sec_price, TriggerDataProvinceCdr },
	{ _sec_price, TriggerDataInterCdr }};

void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("��������"), 0, 0);

	HTREEITEM secItem = viewTree->InsertItem(_T("����"), 0, 0, hRoot);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("�л�"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[0])));

	tmpItem = viewTree->InsertItem(_T("��;"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[1])));

	tmpItem = viewTree->InsertItem(_T("ʡ������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[2])));

	tmpItem = viewTree->InsertItem(_T("ʡ������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[3])));

	tmpItem = viewTree->InsertItem(_T("���ʳ�;"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[4])));

	tmpItem = viewTree->InsertItem(_T("��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[5])));

	tmpItem = viewTree->InsertItem(_T("IPͨ��"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[6])));

	tmpItem = viewTree->InsertItem(_T("��תͨ��"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[7])));

	tmpItem = viewTree->InsertItem(_T("���ڱ���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[8])));

	secItem = viewTree->InsertItem(_T("����"), 0, 0, hRoot);

	tmpItem = viewTree->InsertItem(_T("���ڶ���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[9])));

	tmpItem = viewTree->InsertItem(_T("���ʶ���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[10])));

	tmpItem = viewTree->InsertItem(_T("�������ζ���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[11])));

	tmpItem = viewTree->InsertItem(_T("���ű���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[12])));


	secItem = viewTree->InsertItem(_T("����"), 0, 0, hRoot);

	tmpItem = viewTree->InsertItem(_T("ʡ������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[13])));

	tmpItem = viewTree->InsertItem(_T("ʡ������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[14])));

	tmpItem = viewTree->InsertItem(_T("��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[15])));

}





std::vector<std::string> BuildCdrContent(CString cdrTag,CString callType,CString serialNumber,CString providerCode,
	CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType, 
	BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei ,CString phoneRegion)
{
	std::vector<std::string> result;
	std::string content;
	////
	content = "THEAD,";
	content += CommonUtil::CStringToString(CommonUtil::GetSysYMTime(), CP_ACP);
	content += ",v1,STDBILL_CDR";
	result.push_back(content);

	///
	content = CommonUtil::CStringToString(CommonUtil::GetSysUtcTime(),CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(cdrTag , CP_ACP);
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

	content += CommonUtil::CStringToString(callType, CP_ACP);
	content += ",";

	content += ",,,,";

	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP);
	content += ",";

	content += ",";

	content += CommonUtil::CStringToString(downVolume, CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(upVolume, CP_ACP);
	content += ",";

	__int64 totalVolume = _wtoi64(downVolume) + _wtoi64(upVolume);
	TCHAR strTotalVolume[60];
	_i64tow_s(totalVolume, strTotalVolume , 60 , 10);
	
	content += CommonUtil::CStringToString(CString(strTotalVolume), CP_ACP);
	content += ",";
		 
	content += CommonUtil::CStringToString(duration, CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP);
	content += ",";

	content += ",,,,,";

	content += CommonUtil::CStringToString(roamType, CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(roamNation, CP_ACP);
	content += ",";

	content += CommonUtil::CStringToString(longType, CP_ACP);
	content += ",";

	if (TRUE == ipCall) 
	{
		content += "IPCALL";
	}
	content += ",,,,,";

	content += CommonUtil::CStringToString(firstPriceFee, CP_ACP);
	content += ",,,,,0,6000001,0,";

	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP);
	content += ",";

	content += ",,,,";

	content += CommonUtil::CStringToString(imsi, CP_ACP);
	content += ",";


	content += CommonUtil::CStringToString(imei, CP_ACP);
	content += ",";

	content += "FX_XXXXXXXXXXXXXXXXX.cdr";
	
	result.push_back(content);

	///
	////
	content = "TEND,1,0,0,0,";
	result.push_back(content);

	return result;
}


std::vector<std::string> GetFiles(ModuleContext *ctx,CString testNumber,CString providerCode)
{
	std::vector<std::string> result;
	CString inPath = ctx->m_funcGetProperty(_sec_price, _TEXT("�ļ����"));
	result.push_back(CommonUtil::CStringToString(inPath, CP_ACP) + "/../tmpFX_ONE.dat");
	CString csInFile = inPath + _TEXT("/FX_ONE_") + CommonUtil::GetSysYMDTime() + _TEXT("_") + CommonUtil::GetSerial() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	result.push_back(CommonUtil::CStringToString(csInFile, CP_ACP));

	return result;
}



void TriggerVcLocalCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-�����л�"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg( _TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
								testNumber, providerCode,
								ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
								ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
								ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
								ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
								_TEXT("R_LOCAL"),_TEXT("T_LOCAL"),FALSE,_TEXT("CHN"),_TEXT("40"),
								ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
								ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
								ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
			);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerVcLongCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-���ڳ�;"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_BT_PROVINCE"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerVcRoamInProviceCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-ʡ������"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_IN_PROVINCE"), _TEXT("T_BT_PROVINCE"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerVcRoamProviceCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-ʡ������"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_PROVINCE"), _TEXT("T_BT_PROVINCE"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerVcLongInterCdr(ModuleContext *ctx, void *ptr) 
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-���ʳ�;"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_INTERNATIONAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerVcRoamInterCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-��������"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_OUT_INTERNATIONAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerVcIpCallCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-IPͨ��"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), TRUE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerVcDivertCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-��תͨ��"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("DIVERTING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), TRUE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		resultViewData.PushMsg(_TEXT("����ʧ��."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}

void TriggerVcCalledCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-���ڱ���"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
	
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLED"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), TRUE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}

void TriggerSmsChnCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-���ڶ���"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerSmsInterCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-���ʶ���"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_INTERNATIONAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}


		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}

void TriggerSmsRoamCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-�������ζ���"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
	
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_OUT_INTERNATIONAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}

void TriggerSmsCalledCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-���ڱ��ж���"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLED"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}

void TriggerDataInProvinceCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-ʡ������"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_NET"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerDataProvinceCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-ʡ������"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
	
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_NET"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_PROVINCE"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}

		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerDataInterCdr(ModuleContext *ctx, void *ptr)
{

	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	UINT port = 22;

	std::vector<std::string> files = GetFiles(ctx, testNumber, providerCode);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

	ListViewData resultViewData(testNumber, _TEXT("����-������������"));

	bool result = true;
	do {
		result = ctx->m_objSshCmdExecutor->ConnectAndInit(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		result = ctx->m_objSshCmdExecutor->ExecuteCmd("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}
		
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_NET"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sec_price, _TEXT("��������")),
			_TEXT("R_OUT_INTERNATIONAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
		);

		for (auto it : contents)
		{
			result = ctx->m_objSshCmdExecutor->ExecuteCmd("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
				resultViewData.PushMsg(_TEXT("����ʧ��."));
				break;
			}
		}

		result = ctx->m_objSshCmdExecutor->ExecuteCmd("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.PushMsg(ctx->m_objSshCmdExecutor->GetErrMsg());
			resultViewData.PushMsg(_TEXT("����ʧ��."));
			break;
		}


		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	} while (false);
	ctx->m_objSshCmdExecutor->DisconnectAndFree();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}

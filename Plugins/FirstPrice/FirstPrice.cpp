// FirstPrice.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "FirstPrice.h"
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

// CFirstPriceApp

BEGIN_MESSAGE_MAP(CFirstPriceApp, CWinApp)
END_MESSAGE_MAP()


// CFirstPriceApp ����

CFirstPriceApp::CFirstPriceApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CFirstPriceApp ����

//CFirstPriceApp theApp;


// CFirstPriceApp ��ʼ��

BOOL CFirstPriceApp::InitInstance()
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
	},
	{ _TEXT("�Զ˺��������"),
		{ _TEXT("010"),nullptr , FALSE , }
	},
	{ _TEXT("�ƷѺ������ε�"),
		{ _TEXT("010"),nullptr , FALSE , }
	},
	{ _TEXT("�Զ˺������ε�"),
		{ _TEXT("010"),nullptr , FALSE , }
	},
	{ _TEXT("��Ԫ�豸���"),
		{ _TEXT("861864500"),nullptr , FALSE , }
	},
	{ _TEXT("���ι���"),
		{ _TEXT("861864500"),nullptr , FALSE , }
	}
};

void PropertyInitilize(std::map<int, std::map<CString, PropertyGrid> > &gProperty)
{
	gProperty.insert(std::make_pair(_first_price, modulePropertys));
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
	{ _first_price, TriggerVcLocalCdr },
	{ _first_price, TriggerVcLongCdr },
	{ _first_price, TriggerVcRoamInProviceCdr },
	{ _first_price, TriggerVcRoamProviceCdr },
	{ _first_price, TriggerVcLongInterCdr },
	{ _first_price, TriggerVcRoamInterCdr },
	{ _first_price, TriggerVcIpCallCdr },
	{ _first_price, TriggerVcDivertCdr },
	{ _first_price, TriggerVcCalledCdr },
	{ _first_price, TriggerSmsChnCdr },
	{ _first_price, TriggerSmsInterCdr },
	{ _first_price, TriggerSmsRoamCdr },
	{ _first_price, TriggerSmsCalledCdr },
	{ _first_price, TriggerDataInProvinceCdr },
	{ _first_price, TriggerDataProvinceCdr },
	{ _first_price, TriggerDataInterCdr } };


void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("��׼����"), 0, 0);

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




std::vector<std::string> BuildCdrContent(CString cdrTag, CString callType, CString serialNumber, CString providerCode,
	CString peerNumber, CString duration, CString downVolume, CString upVolume, CString roamType, CString longType,
	BOOL ipCall, CString roamNation, CString imsi, CString imei, CString phoneRegion,CString peerRegion, CString phoneLocation,
	CString peerLocation,CString entityCode)
{
	std::vector<std::string> result;
	std::string content;
	////
	content = "THEAD,";
	content += CommonUtil::CStringToString(CommonUtil::GetSysYMTime(), CP_ACP);
	content += ",v1,STDBILL_CDR";
	result.push_back(content);

	///CDR_KEY
	content = CommonUtil::CStringToString(CommonUtil::GetSysUtcTime(), CP_ACP);
	content += ",";
	
	///TAG
	content += CommonUtil::CStringToString(cdrTag, CP_ACP);
	content += ",";
	
	//cdr_file_name
	content += "FX_XXXXXXXXXXXXXX.cdr";
	content += ",";
	
	//bill_month
	content += CommonUtil::CStringToString(CommonUtil::GetSysYMTime(), CP_ACP);
	content += ",";

	///PROVIDER
	content += CommonUtil::CStringToString(providerCode, CP_ACP);
	content += ",";

	///phone_num
	content += CommonUtil::CStringToString(serialNumber, CP_ACP);
	content += ",";


	///peer_number
	content += CommonUtil::CStringToString(peerNumber, CP_ACP);
	content += ",";

	///call_type
	content += CommonUtil::CStringToString(callType, CP_ACP);
	content += ",";

	//PHONE_REGION
	content += CommonUtil::CStringToString(phoneRegion, CP_ACP);
	content += ",";
	
	///PEER_REGION
	content += CommonUtil::CStringToString(peerRegion, CP_ACP);
	content += ",";

	///PHONE_LOCATION
	content += CommonUtil::CStringToString(phoneLocation, CP_ACP);
	content += ",";

	//PEER_LOCATION
	content += CommonUtil::CStringToString(peerLocation, CP_ACP);
	content += ",";

	///Start_date_time
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP);
	content += ",";

	///PROVIDOR_FEE
	content += "10,";

	///download_amount
	content += CommonUtil::CStringToString(downVolume, CP_ACP);
	content += ",";
	
	///upload_amount
	content += CommonUtil::CStringToString(upVolume, CP_ACP);
	content += ",";

	///total_amount
	__int64 totalVolume = _wtoi64(downVolume) + _wtoi64(upVolume);
	TCHAR strTotalVolume[60];
	_i64tow_s(totalVolume, strTotalVolume, 60, 10);

	content += CommonUtil::CStringToString(CString(strTotalVolume), CP_ACP);
	content += ",";

	///duration
	content += CommonUtil::CStringToString(duration, CP_ACP);
	content += ",";


	///create_date_time
	content += CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP);
	content += ",";

	///Other_party
	content += ",";

	//Third_party
	content += ",";

	///SP_CODE
	content += ",";

	///Service_type
	content += ",";

	///Service_code
	content += ",";

	///Roam_type
	content += CommonUtil::CStringToString(roamType, CP_ACP);
	content += ",";

	///ROAM_NATION
	content += CommonUtil::CStringToString(roamNation, CP_ACP);
	content += ",";

	///TOLL_TYPE
	content += CommonUtil::CStringToString(longType, CP_ACP);
	content += ",";

	///APN
	content += ",";

	///USAGE_TAG
	content += ",";

	///site_tag
	content += ",";

	///TOLL_NATION
	content += ",";

	///EXT_FLAG
	content += ",";

	///EXT_FEE
	content += ",";

	///EXT_REL_ID
	content += ",";

	///ENTITY_CODE
	content += CommonUtil::CStringToString(entityCode, CP_ACP);
	content += ",";

	///PROVIDOR_TOTAL_FEE
	content += "10,";

	///Third_party_region
	content += ",";

	///DIVERTING_TYPE
	content += "0,";


	///PRODUCT_ID
	content += ",";

	///MESS_ID
	content += ",";

	///VAC_ID
	content += ",";

	///BILL_TYPE
	content += ",";

	///RATING_GROUP
	content += ",";


	///IMSI_ID
	content += CommonUtil::CStringToString(imsi, CP_ACP);
	content += ",";

	///IMEI_ID
	content += CommonUtil::CStringToString(imei, CP_ACP);
	content += ",";
	

	///FX_FILE_NAME
	content += "FX_XXXXXXXXXXXXXXXXX.cdr";

	result.push_back(content);

	///
	////
	content = "TEND,1,0,0,0,";
	result.push_back(content);

	return result;
}


std::vector<std::string> GetFiles(ModuleContext *ctx, CString testNumber, CString providerCode)
{
	std::vector<std::string> result;
	CString inPath = ctx->m_funcGetProperty(_first_price, _TEXT("�ļ����"));
	result.push_back(CommonUtil::CStringToString(inPath, CP_ACP) + "/../tmpFX_CDR.dat");
	CString csInFile = inPath + _TEXT("/FX_CDR_") + CommonUtil::GetSysYMDTime() + _TEXT("_") + CommonUtil::GetSerial() + _TEXT(".") + providerCode
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), FALSE,
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_BT_PROVINCE"), FALSE, 
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));


		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_IN_PROVINCE"), _TEXT("T_BT_PROVINCE"), FALSE, ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_PROVINCE"), _TEXT("T_BT_PROVINCE"), FALSE,
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_INTERNATIONAL"), FALSE,
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_OUT_INTERNATIONAL"), _TEXT("T_LOCAL"), FALSE,
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), TRUE,
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("DIVERTING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), TRUE, 
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLED"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), TRUE, 
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), FALSE,
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_INTERNATIONAL"), FALSE,
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_OUT_INTERNATIONAL"), _TEXT("T_LOCAL"), FALSE,
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLED"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), FALSE, 
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_NET"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), FALSE, 
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_NET"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_PROVINCE"), _TEXT("T_LOCAL"), FALSE, 
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
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
	resultViewData.m_result = _TEXT("�����ɹ�.");

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_NET"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_first_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��������")),
			_TEXT("R_OUT_INTERNATIONAL"), _TEXT("T_LOCAL"), FALSE,
			ctx->m_funcGetProperty(_first_price, _TEXT("���ι���")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺��������")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�ƷѺ������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("�Զ˺������ε�")),
			ctx->m_funcGetProperty(_first_price, _TEXT("��Ԫ�豸���")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}

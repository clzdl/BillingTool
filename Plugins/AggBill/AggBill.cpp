// AggBill.cpp : ���� DLL �ĳ�ʼ�����̡�
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

// CAggBillApp

BEGIN_MESSAGE_MAP(CAggBillApp, CWinApp)
END_MESSAGE_MAP()


// CAggBillApp ����

CAggBillApp::CAggBillApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CAggBillApp ����

//CAggBillApp theApp;


// CAggBillApp ��ʼ��

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


	HTREEITEM hRoot = viewTree->InsertItem(_T("����"), 0, 0);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("����"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[0])));

	tmpItem = viewTree->InsertItem(_T("����"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[1])));

	tmpItem = viewTree->InsertItem(_T("����"), 1, 2, hRoot);
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
	CString inPath = ctx->m_funcGetProperty(_agg_bill, _TEXT("�ļ����"));
	///��ʱ�ļ�  0
	result.push_back(CommonUtil::CStringToString(inPath, CP_ACP) + "/../tmpFX_BILL.dat");

	CString csInFile = inPath + _TEXT("/FX_BILL_") + CommonUtil::GetSysYMDTime() + _TEXT("_") + CommonUtil::GetSerial() + _TEXT(".") + providerCode
		+ _TEXT(".") + testNumber.Left(7) + _TEXT(".dat");
	///��ʽ�ļ�  1
	result.push_back(CommonUtil::CStringToString(csInFile, CP_ACP));

	return result;
}

void AggVc(ModuleContext *ctx, void *ptr)
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

	ListViewData resultViewData(testNumber, _TEXT("����-����"));
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
			ctx->m_funcGetProperty(_agg_bill, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("��������")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_BT_PROVINCE"), FALSE,
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
			ctx->m_funcGetProperty(_common, _TEXT("�˻�ID")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("����ID")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("���ʷ�ID"))
		);

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
void AggSms(ModuleContext *ctx, void *ptr)
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
	

	ListViewData resultViewData(testNumber, _TEXT("����-����"));
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
			ctx->m_funcGetProperty(_agg_bill, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("��������")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_BT_PROVINCE"), FALSE,
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
			ctx->m_funcGetProperty(_common, _TEXT("�˻�ID")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("����ID")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("���ʷ�ID"))
		);

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
void AggData(ModuleContext *ctx, void *ptr)
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

	ListViewData resultViewData(testNumber, _TEXT("����-����"));
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
			ctx->m_funcGetProperty(_agg_bill, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("��������")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_BT_PROVINCE"), FALSE,
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
			ctx->m_funcGetProperty(_common, _TEXT("�˻�ID")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("����ID")),
			ctx->m_funcGetProperty(_agg_bill, _TEXT("���ʷ�ID"))
		);

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
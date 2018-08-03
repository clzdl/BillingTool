// Predeal.cpp : ���� DLL �ĳ�ʼ�����̡�
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

// CPredealApp

BEGIN_MESSAGE_MAP(CPredealApp, CWinApp)
END_MESSAGE_MAP()


// CPredealApp ����

CPredealApp::CPredealApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CPredealApp ����

//CPredealApp theApp;


// CPredealApp ��ʼ��

BOOL CPredealApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
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


	HTREEITEM hRoot = viewTree->InsertItem(_T("Ԥ����"), 0, 0);

	HTREEITEM secItem = viewTree->InsertItem(_T("����"), 0, 0 , hRoot);
	///����
	HTREEITEM tmpItem = viewTree->InsertItem(_T("����-��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccVcCHNCalling));

	tmpItem = viewTree->InsertItem(_T("����-���ڱ���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccVcCHNCalled));

	tmpItem = viewTree->InsertItem(_T("����-������;"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccVcInterCalling));

	tmpItem = viewTree->InsertItem(_T("����-��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccVcInterRoam));

	tmpItem = viewTree->InsertItem(_T("����-��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccSmsCHNCalling));

	tmpItem = viewTree->InsertItem(_T("����-���ڱ���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccSmsCHNCalled));

	tmpItem = viewTree->InsertItem(_T("����-���ʳ�;"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccSmsInterCalling));

	tmpItem = viewTree->InsertItem(_T("����-��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccSmsInterRoam));

	tmpItem = viewTree->InsertItem(_T("����-����"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccDataCHNCalling));

	tmpItem = viewTree->InsertItem(_T("����-����"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CtccDataInterCalling));


	////
	secItem = viewTree->InsertItem(_T("�ƶ�"), 0, 0, hRoot);
	tmpItem = viewTree->InsertItem(_T("����-��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccVcCHNCalling));

	tmpItem = viewTree->InsertItem(_T("����-���ڱ���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccVcCHNCalled));

	tmpItem = viewTree->InsertItem(_T("����-������;"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccVcInterCalling));

	tmpItem = viewTree->InsertItem(_T("����-��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccVcInterRoam));

	tmpItem = viewTree->InsertItem(_T("����-��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccSmsCHNCalling));

	tmpItem = viewTree->InsertItem(_T("����-���ڱ���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccSmsCHNCalled));

	tmpItem = viewTree->InsertItem(_T("����-���ʳ�;"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccSmsInterCalling));

	tmpItem = viewTree->InsertItem(_T("����-��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccSmsInterRoam));

	tmpItem = viewTree->InsertItem(_T("����-����"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccDataCHNCalling));

	tmpItem = viewTree->InsertItem(_T("����-����"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CmccDataInterCalling));

	///
	secItem = viewTree->InsertItem(_T("��ͨ"), 0, 0, hRoot);

	tmpItem = viewTree->InsertItem(_T("����-��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccVcCHNCalling));

	tmpItem = viewTree->InsertItem(_T("����-���ڱ���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccVcCHNCalled));

	tmpItem = viewTree->InsertItem(_T("����-������;"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccVcInterCalling));

	tmpItem = viewTree->InsertItem(_T("����-��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccVcInterRoam));

	tmpItem = viewTree->InsertItem(_T("����-��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccSmsCHNCalling));

	tmpItem = viewTree->InsertItem(_T("����-���ڱ���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccSmsCHNCalled));

	tmpItem = viewTree->InsertItem(_T("����-���ʳ�;"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccSmsInterCalling));

	tmpItem = viewTree->InsertItem(_T("����-��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccSmsInterRoam));

	tmpItem = viewTree->InsertItem(_T("����-����"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccDataCHNCalling));

	tmpItem = viewTree->InsertItem(_T("����-����"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CuccDataInterCalling));

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
	result.push_back(CommonUtil::CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("�ļ����")), CP_ACP) + "/../tempDCHN01FX03400125");

	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("�ļ����")) + "/CDCHN01FX03400125" + _TEXT(".") + CommonUtil::GetSysYMTime() + ".dat";
	result.push_back(CommonUtil::CStringToString(csInFile, CP_ACP));

	return result;
}

void CtccVcCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������С����š�"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);
	

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

		std::vector<std::string> creditContent = BuildCtccTCMOCdr( _TEXT("VC"),
										ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
										testNumber,
										ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
										ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
										_TEXT("CHN"),
										ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
										ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI"))	);



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CtccVcCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ڱ��С����š�"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCtccTCMTCdr(_TEXT("VC"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			_TEXT("CHN"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CtccVcInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ʳ�;�����š�"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCtccTCMOCdr(_TEXT("VC"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			testNumber,
			_TEXT("00") + ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			_TEXT("CHN"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CtccVcInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������Ρ����š�"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCtccTCMOCdr(_TEXT("VC"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			_TEXT("USA"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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

void CtccSmsCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������С����š�"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCtccTCMOCdr(_TEXT("SMS"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			_TEXT("CHN"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CtccSmsCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������С����š�"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCtccTCMTCdr(_TEXT("SMS"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			_TEXT("CHN"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CtccSmsInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ʳ�;�����š�"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCtccTCMOCdr(_TEXT("SMS"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			testNumber,
			_TEXT("00") + ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			_TEXT("CHN"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CtccSmsInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������Ρ����š�"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCtccTCMOCdr(_TEXT("SMS"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			_TEXT("USA"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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

void CtccDataCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ڡ����š�"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCtccTCGPCdr(	
								ctx->m_funcGetProperty(_predeal, _TEXT("������������")),
								ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
								ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
								testNumber,	_TEXT("CHN") );



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CtccDataInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ʡ����š�"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCtccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCtccTCGPCdr(
			ctx->m_funcGetProperty(_predeal, _TEXT("������������")),
			ctx->m_funcGetProperty(_predeal, _TEXT("SESSIONID")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			testNumber, _TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
	result.push_back(CommonUtil::CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("�ļ����")), CP_ACP) + "/../tempDCHN01FX03400125");
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("�ļ����")) + "/CDCHN01FX03400125.CMCC" + _TEXT(".") + CommonUtil::GetSysYMTime() + ".dat";
	result.push_back(CommonUtil::CStringToString(csInFile, CP_ACP));
	return result;
}

void CmccVcCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������С��ƶ���"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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
		
		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("VC"),
				ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
				testNumber,
				ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
				_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CmccVcCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ڱ��С��ƶ���"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCmccTCMTCdr(_TEXT("VC"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CmccVcInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ʳ�;���ƶ���"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("VC"),
						ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
						testNumber,
						_TEXT("00") + ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
						_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CmccVcInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������Ρ��ƶ���"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("VC"),
												ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
												testNumber,
												ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
												_TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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

void CmccSmsCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������С��ƶ���"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("SMS"),
								ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
								testNumber,
								ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
								_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CmccSmsCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������С��ƶ���"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCmccTCMTCdr(_TEXT("SMS"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CmccSmsInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ʳ�;���ƶ���"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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
	
		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("SMS"),
									ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
									testNumber,
									_TEXT("00") + ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
									_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CmccSmsInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������Ρ��ƶ���"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCmccTCMOCdr(_TEXT("SMS"),
									ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
									testNumber,
									ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
									_TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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

void CmccDataCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ڡ��ƶ���"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCmccTCGPCdr(
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			testNumber, _TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CmccDataInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ʡ��ƶ���"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCmccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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
		
		std::vector<std::string> creditContent = BuildCmccTCGPCdr(
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			testNumber, _TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
	result.push_back(CommonUtil::CStringToString(ctx->m_funcGetProperty(_predeal, _TEXT("�ļ����")), CP_ACP) + "/../tempSOSH0100000SJ");
	CString csInFile = ctx->m_funcGetProperty(_predeal, _TEXT("�ļ����")) + "/SOSH0100000SJ" + CommonUtil::GetSysYMDTime() + ".dat";
	result.push_back(CommonUtil::CStringToString(csInFile, CP_ACP));
	return result;
}

void CuccVcCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������С���ͨ��"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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
		
		std::vector<std::string> creditContent = BuildCuccVcdr(_TEXT("CALLING"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			_TEXT("CHN"), _TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CuccVcCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ڱ��С���ͨ��"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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
		std::vector<std::string> creditContent = BuildCuccVcdr(_TEXT("CALLED"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			_TEXT("CHN"), _TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CuccVcInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ʳ�;����ͨ��"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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
		std::vector<std::string> creditContent = BuildCuccVcdr(_TEXT("CALLED"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			testNumber,
			_TEXT("00") + ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			_TEXT("CHN"), _TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CuccVcInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������Ρ���ͨ��"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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
		std::vector<std::string> creditContent = BuildCuccVcdr(_TEXT("CALLED"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			testNumber,
			_TEXT("00") + ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			_TEXT("USA"), _TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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

void CuccSmsCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������С���ͨ��"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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
		std::vector<std::string> creditContent = BuildCuccSmsCdr(_TEXT("CALLING"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			_TEXT("CHN"),_TEXT("CHN"));


		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CuccSmsCHNCalled(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������С���ͨ��"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCuccSmsCdr(_TEXT("CALLED"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			_TEXT("CHN"),_TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CuccSmsInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ʳ�;����ͨ��"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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
		std::vector<std::string> creditContent = BuildCuccSmsCdr(_TEXT("CALLING"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			_TEXT("CHN"),_TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CuccSmsInterRoam(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-�������Ρ���ͨ��"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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
		std::vector<std::string> creditContent = BuildCuccSmsCdr(_TEXT("CALLING"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			testNumber,
			ctx->m_funcGetProperty(_predeal, _TEXT("�Զ˺���")),
			_TEXT("USA"),_TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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

void CuccDataCHNCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ڡ���ͨ��"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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


		std::vector<std::string> creditContent = BuildCuccTCGPCdr(
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			testNumber, _TEXT("CHN"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
void CuccDataInterCalling(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����-���ʡ���ͨ��"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	UINT port = 22;

	std::vector<std::string> files = GetCuccFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> creditContent = BuildCuccTCGPCdr(
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			testNumber, _TEXT("USA"));



		for (auto it : creditContent)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo \"" + it + "\" >>" + tmpInFile);
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
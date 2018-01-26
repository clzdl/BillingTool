// SettSecPrice.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "SettSecPrice.h"
#include "../../BillingTool/PluginInterface.h"
#include "../../BillingTool/ViewTree.h"
#include "../../BillingTool/ModuleContext.h"
#include "../../BillingTool/BillingTool.h"
#include <vector>


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

// CSettSecPriceApp

BEGIN_MESSAGE_MAP(CSettSecPriceApp, CWinApp)
END_MESSAGE_MAP()


// CSettSecPriceApp ����

CSettSecPriceApp::CSettSecPriceApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CSettSecPriceApp ����

//CSettSecPriceApp theApp;


// CSettSecPriceApp ��ʼ��

BOOL CSettSecPriceApp::InitInstance()
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


	HTREEITEM hRoot = viewTree->InsertItem(_T("��������(����)"), 0, 0);

	HTREEITEM secItem = viewTree->InsertItem(_T("����"), 0, 0, hRoot);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("�л�"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcLocalCdr));

	tmpItem = viewTree->InsertItem(_T("��;"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcLongCdr));

	tmpItem = viewTree->InsertItem(_T("ʡ������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcRoamInProviceCdr));

	tmpItem = viewTree->InsertItem(_T("ʡ������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcRoamProviceCdr));

	tmpItem = viewTree->InsertItem(_T("���ʳ�;"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcLongInterCdr));

	tmpItem = viewTree->InsertItem(_T("��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcRoamInterCdr));

	tmpItem = viewTree->InsertItem(_T("IPͨ��"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcIpCallCdr));

	tmpItem = viewTree->InsertItem(_T("��תͨ��"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcDivertCdr));

	tmpItem = viewTree->InsertItem(_T("���ڱ���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerVcCalledCdr));

	secItem = viewTree->InsertItem(_T("����"), 0, 0, hRoot);

	tmpItem = viewTree->InsertItem(_T("���ڶ���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerSmsChnCdr));

	tmpItem = viewTree->InsertItem(_T("���ʶ���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerSmsInterCdr));

	tmpItem = viewTree->InsertItem(_T("�������ζ���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerSmsRoamCdr));

	tmpItem = viewTree->InsertItem(_T("���ű���"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerSmsCalledCdr));


	secItem = viewTree->InsertItem(_T("����"), 0, 0, hRoot);

	tmpItem = viewTree->InsertItem(_T("ʡ������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerDataInProvinceCdr));

	tmpItem = viewTree->InsertItem(_T("ʡ������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerDataProvinceCdr));

	tmpItem = viewTree->InsertItem(_T("��������"), 1, 2, secItem);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerDataInterCdr));

}





std::vector<std::string> BuildCdrContent(CString cdrTag, CString callType, CString serialNumber, CString providerCode,
	CString peerNumber, CString duration, CString downVolume, CString upVolume, CString roamType, CString longType,
	BOOL ipCall, CString roamNation, CString firstPriceFee, CString imsi, CString imei, CString phoneRegion)
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
	content += ",,,";

	content += CStringToString(peerNumber, CP_ACP);
	content += ",,,,,";

	content += CStringToString(callType, CP_ACP);
	content += ",0,";

	content += CStringToString(longType, CP_ACP);
	content += ",USA,";
	
	content += CStringToString(roamType, CP_ACP);
	content += ",USA,";

	content += CStringToString(GetSysTime(), CP_ACP);
	content += ",";

	content += CStringToString(GetSysTime(), CP_ACP);
	content += ",";

	content += CStringToString(duration, CP_ACP);
	content += ",";

	content += ",,,";

	if (TRUE == ipCall)
	{
		content += "IPCALL";
	}
	content += ",,,,";

	content += CStringToString(upVolume, CP_ACP);
	content += ",";

	content += CStringToString(downVolume, CP_ACP);
	content += ",";



	__int64 totalVolume = _wtoi64(downVolume) + _wtoi64(upVolume);
	TCHAR strTotalVolume[60];
	_i64tow_s(totalVolume, strTotalVolume, 60, 10);

	content += CStringToString(CString(strTotalVolume), CP_ACP);
	content += ",";

	content += "0:1000,1000,";

	content += CStringToString(GetSysTime(), CP_ACP);
	content += ",";

	content += ",,,,0,,,,,60000001,,,,,,,,,";


	result.push_back(content);

	///
	////
	content = "TEND,1,0,0,0,";
	result.push_back(content);

	return result;
}






void TriggerVcLocalCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) +"_" + providerCode
		+ _TEXT("_") +  GetSysYMTime() +  + _TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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
void TriggerVcLongCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_BT_PROVINCE"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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
void TriggerVcRoamInProviceCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_IN_PROVINCE"), _TEXT("T_BT_PROVINCE"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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
void TriggerVcRoamProviceCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_PROVINCE"), _TEXT("T_BT_PROVINCE"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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
void TriggerVcLongInterCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_INTERNATIONAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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
void TriggerVcRoamInterCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_OUT_INTERNATIONAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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
void TriggerVcIpCallCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), TRUE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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
void TriggerVcDivertCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("DIVERTING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), TRUE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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

void TriggerVcCalledCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_CALL"), _TEXT("CALLED"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), TRUE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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

void TriggerSmsChnCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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
void TriggerSmsInterCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_INTERNATIONAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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

void TriggerSmsRoamCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_OUT_INTERNATIONAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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

void TriggerSmsCalledCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_SMS"), _TEXT("CALLED"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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

void TriggerDataInProvinceCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_NET"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_LOCAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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
void TriggerDataProvinceCdr(ModuleContext *ctx, void *ptr)
{
	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_NET"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_PROVINCE"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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
void TriggerDataInterCdr(ModuleContext *ctx, void *ptr)
{

	CString testNumber = ctx->m_funcGetProperty(_common, _TEXT("���Ժ���"));
	std::string hostName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(_common, _TEXT("����")), CP_ACP);
	CString providerCode = ctx->m_funcGetProperty(_common, _TEXT("������Ӫ��"));
	CString inPath = ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�ļ����"));
	std::string tmpInFile = CStringToString(inPath, CP_ACP) + "/../tmpSET_STAND_CDR_.dat";
	CString csInFile = inPath + _TEXT("/SET_STAND_CDR_") + GetSysYMDTime() + _TEXT("_") + testNumber.Left(7) + "_" + providerCode
		+ _TEXT("_") + GetSysYMTime() + +_TEXT(".dat");
	std::string inFile = CStringToString(csInFile, CP_ACP);
	UINT port = 22;

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
		/*
		CString cdrTag,CString callType,CString serialNumber,CString providerCode,
		CString peerNumber,CString duration,CString downVolume,CString upVolume,CString roamType,CString longType,
		BOOL ipCall, CString roamNation,CString firstPriceFee,CString imsi,CString imei,phoneRegion
		*/
		std::vector<std::string> contents = BuildCdrContent(_TEXT("CDR_NET"), _TEXT("CALLING"),
			testNumber, providerCode,
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("�Զ˺���")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("ʱ��")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			ctx->m_funcGetProperty(_sett_sec_price, _TEXT("��������")),
			_TEXT("R_OUT_INTERNATIONAL"), _TEXT("T_LOCAL"), FALSE, _TEXT("CHN"), _TEXT("40"),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMSI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�IMEI")),
			ctx->m_funcGetProperty(_common, _TEXT("�û�������"))
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

// SmsSend.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "CreditSms.h"
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

// CSmsSendApp

BEGIN_MESSAGE_MAP(CSmsSendApp, CWinApp)
END_MESSAGE_MAP()


// CSmsSendApp ����

CSmsSendApp::CSmsSendApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CSmsSendApp ����

//CSmsSendApp theApp;


// CSmsSendApp ��ʼ��

BOOL CSmsSendApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

const CString FILE_IN = _TEXT("�ļ����");
const CString HASTEN_POLICYID = _TEXT("HASTEN_POLICY_ID");
const CString LEAVE_REAL_FEE = _TEXT("LEAVE_REAL_FEE");
const CString REAL_FEE = _TEXT("REAL_FEE");
const CString CREDIT_VALUE = _TEXT("CREDIT_VALUE");


static std::map<CString, PropertyGrid> modulePropertys = {
	{ FILE_IN,
		{ _TEXT("/home/chengl/src/soPeriodSmsProcess/data/in"),nullptr , FALSE , }
	},
	{ HASTEN_POLICYID,
		{ _TEXT("40000036"),nullptr , FALSE , }
	},
	{ LEAVE_REAL_FEE,
		{ _TEXT("1000"),nullptr , FALSE , }
	},
	{ REAL_FEE,
		{ _TEXT("2000"),nullptr , FALSE , }
	},
	{ CREDIT_VALUE,
		{ _TEXT("3000"),nullptr , FALSE , }
	}
};


void PropertyInitilize(std::map<int, std::map<CString, PropertyGrid> > &gProperty)
{
	gProperty.insert(std::make_pair(_credit_sms, modulePropertys));
}

/*
#define BILL_URGING_PAY    7001 //�߷�����(��ֵ)
#define TRAFFIC_REMIND     7002 //��������->����ֵ(�ײ���)/����ֵ(�ײ���)/����ֵ(�ײ���)/����ֵ(ʹ������)
#define CONSUMPTION_REMIND 7003 //��������-->������ز������߼��жϣ�ֱ�Ӳ���ű�
#define DOUBLE_STOP        3110 //�ſ�ͣ�� -->Ŀǰ�ɷַ�����
#define SINGLE_STOP        3120 //�ſذ�ͣ�� -->�д���
#define TRAFFIC_CAP        3111 //�����ⶥ -->Ŀǰ��chengl�ַ��߼������ɱ������Ͷ���
#define LAST_PAY_HASTEN    3200 //�󸶷Ѵ߷�-->�󸶷ѽ������ڴ���ʱ
*/
void TriggerSmsSendFile(ModuleContext *ctx, void *ptr);
void TriggerOneWayStopMsg(ModuleContext *ctx, void *ptr);
void TriggerDoubleStopMsg(ModuleContext *ctx, void *ptr);
void TriggerNotEnoughBalanceMsg(ModuleContext *ctx, void *ptr);
void TriggerDataRemindMsg(ModuleContext *ctx, void *ptr);
void TriggerDataTopMsg(ModuleContext *ctx, void *ptr);
void TriggerPostPaypMsg(ModuleContext *ctx, void *ptr);


static _ItemCallBackDef moduleCallBackDef[] = {
	{ _credit_sms, TriggerSmsSendFile },
	{ _credit_sms, TriggerOneWayStopMsg },
	{ _credit_sms, TriggerDoubleStopMsg },
	{ _credit_sms, TriggerNotEnoughBalanceMsg },
	{ _credit_sms, TriggerDataRemindMsg },
	{ _credit_sms, TriggerDataTopMsg },
	{ _credit_sms, TriggerPostPaypMsg }};

void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("��������"), 0, 0);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("���ɶ����ļ�"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[0])));

	tmpItem = viewTree->InsertItem(_T("������ͣ����"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[1])));

	tmpItem = viewTree->InsertItem(_T("����˫ͣ����"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[2])));

	tmpItem = viewTree->InsertItem(_T("�����������"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[3])));
	
	tmpItem = viewTree->InsertItem(_T("��������ʹ�ö���"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[4])));

	tmpItem = viewTree->InsertItem(_T("���������ⶥ����"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[5])));

	tmpItem = viewTree->InsertItem(_T("�����󸶷��û��߷Ѷ���"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[6])));
}

std::vector<std::string> BuildSmsContents(CString serialNumber, CString userId)
{
	/*
	17001810501|120150105227073|1|";"=>"\n"|�𾴵ķ���ͨ�ſͻ������ã�;��2016��9���˵�129.00Ԫ��������129.00Ԫ���Żݼ�����0.00Ԫ�������У�;�ײͼ��̶��ѣ�129.00Ԫ;-�����ײͷѣ�129.00Ԫ;�ɷ������10039.cc
	*/
	std::vector<std::string> result;
	std::string content = CommonUtil::CStringToString(serialNumber, CP_ACP);
	content += "|";
	content += CommonUtil::CStringToString(serialNumber, CP_ACP);
	content += "|";
	content += CommonUtil::CStringToString(_TEXT("1|\"; \"=>\"\\n\"|�𾴵ķ���ͨ�ſͻ������ã�;��2016��9���˵�129.00Ԫ��������129.00Ԫ���Żݼ�����0.00Ԫ�������У�;�ײͼ��̶��ѣ�129.00Ԫ;-�����ײͷѣ�129.00Ԫ;�ɷ������10039.cc"), CP_UTF8);
	result.push_back(content);
	return result;

}

std::vector<std::string> GetFiles(ModuleContext *ctx)
{
	std::vector<std::string> result;
	result.push_back(CommonUtil::CStringToString(ctx->m_funcGetProperty(_credit_sms, FILE_IN), CP_ACP) + "/../tmp_smsSendFile");

	CString csInFile = ctx->m_funcGetProperty(_credit_sms, FILE_IN)
		+ _TEXT("/smsSendFile") + CommonUtil::GetSysYMDTime() + _TEXT(".dat");

	result.push_back(CommonUtil::CStringToString(csInFile, CP_ACP));
	return result;
}

void TriggerSmsSendFile(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, TEST_NUMBER), _TEXT("���ɶ����ļ�"));

	std::string hostName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, IP_ADDR), CP_ACP);
	std::string userName = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, HOST_USERNAME), CP_ACP);
	std::string userPwd = CommonUtil::CStringToString(ctx->m_funcGetProperty(_common, HOST_USERPWD), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(_common, TEST_NUMBER);
	UINT port = 22;

	std::vector<std::string> files =  GetFiles(ctx);
	std::string tmpInFile = files.at(0);
	std::string inFile = files.at(1);

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

		std::vector<std::string> contents = BuildSmsContents(testNumber, ctx->m_funcGetProperty(_common, USER_ID));

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

bool BuildHastenNotice(ModuleContext *ctx, CString userId, CString tradeTypeCode, CString policyId, 
									CString leaveRealFee,CString realFee,CString creditValue)
{
	try {
		std::string sql = "insert into CDT_HASTEN_NOTICE(trade_type_code, "
			"	user_id, "
			"	trade_id, "
			"	main_tag, "
			"	product_id, "
			"	leave_real_fee, "
			"	real_fee, "
			"	credit_value, "
			"	hasten_policy_id, "
			"	in_time, "
			"	hasten_times, "
			"	already_hasten, "
			"	exec_time,  "
			"	last_exec_time, "
			"	deal_tag, "
			"	region_id, "
			"	remark, "
			"	over_owe) "
			"	values(:v1<char[20]>, "
			"		:v2<char[20]>, "
			"		:v3<char[20]>, "
			"		0,999999,"
			"		:v4<char[20]>,:v5<char[20]>,:v6<char[20]>,:v7<char[20]>,"
			"		sysdate,0,0,sysdate,sysdate,0,'test','',0)";



		otl_stream otlStm;
		otlStm.open(1, sql.c_str(), *(ctx->m_dbConn));
		otlStm.set_commit(0);

		otlStm << CommonUtil::CStringToString(tradeTypeCode, CP_ACP).c_str()
			<< CommonUtil::CStringToString(userId, CP_ACP).c_str()
			<< CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP).c_str()
			<< CommonUtil::CStringToString(leaveRealFee, CP_ACP).c_str()
			<< CommonUtil::CStringToString(realFee, CP_ACP).c_str()
			<< CommonUtil::CStringToString(creditValue, CP_ACP).c_str()
			<< CommonUtil::CStringToString(policyId, CP_ACP).c_str();

		ctx->m_dbConn->commit();
	}
	catch (otl_exception &e)
	{
		char strExp[4096] = { 0 };
		sprintf_s(strExp, "code:%d,msg:%s,var_info:%s,stm_text:%s\n", e.code, e.msg, e.var_info, e.stm_text);
		CString exp = CommonUtil::StringToCString(strExp, CP_ACP);
		ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_STATUSBAR, 0, (LPARAM)exp.GetBuffer());
		exp.ReleaseBuffer();
		return false;
	}

	return true;
}


void TriggerOneWayStopMsg(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, TEST_NUMBER), _TEXT("������ͣ����"));

	if (!BuildHastenNotice(ctx, ctx->m_funcGetProperty(_common, USER_ID),
		_TEXT("3120"),
		ctx->m_funcGetProperty(_credit_sms, HASTEN_POLICYID),
		ctx->m_funcGetProperty(_credit_sms, LEAVE_REAL_FEE),
		ctx->m_funcGetProperty(_credit_sms, REAL_FEE),
		ctx->m_funcGetProperty(_credit_sms, CREDIT_VALUE)))
	{
		resultViewData.PushMsg(_TEXT("����ʧ��."));
	}
	else
	{
		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerDoubleStopMsg(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, TEST_NUMBER), _TEXT("����˫ͣ����"));

	
	if (!BuildHastenNotice(ctx, ctx->m_funcGetProperty(0, USER_ID),
		_TEXT("3110"),
		ctx->m_funcGetProperty(_credit_sms, HASTEN_POLICYID),
		ctx->m_funcGetProperty(_credit_sms, LEAVE_REAL_FEE),
		ctx->m_funcGetProperty(_credit_sms, REAL_FEE),
		ctx->m_funcGetProperty(_credit_sms, CREDIT_VALUE)))
	{
		resultViewData.PushMsg(_TEXT("����ʧ��."));
	}
	else
	{
		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}

void TriggerNotEnoughBalanceMsg(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, TEST_NUMBER), _TEXT("�����������"));

	if (!BuildHastenNotice(ctx, ctx->m_funcGetProperty(0, USER_ID),
		_TEXT("7001"),
		ctx->m_funcGetProperty(_credit_sms, HASTEN_POLICYID),
		ctx->m_funcGetProperty(_credit_sms, LEAVE_REAL_FEE),
		ctx->m_funcGetProperty(_credit_sms, REAL_FEE),
		ctx->m_funcGetProperty(_credit_sms, CREDIT_VALUE)))
	{
		resultViewData.PushMsg(_TEXT("����ʧ��."));
	}
	else
	{
		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}

void TriggerDataRemindMsg(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, TEST_NUMBER), _TEXT("��������ʹ�ö���"));

	/*
	ModuleContext *ctx, CString userId, CString tradeTypeCode, CString policyId,
	CString leaveRealFee,CString realFee,CString creditValue
	*/
	if (!BuildHastenNotice(ctx, ctx->m_funcGetProperty(0, USER_ID),
		_TEXT("7002"),
		ctx->m_funcGetProperty(_credit_sms, HASTEN_POLICYID),
		ctx->m_funcGetProperty(_credit_sms, LEAVE_REAL_FEE),
		ctx->m_funcGetProperty(_credit_sms, REAL_FEE),
		ctx->m_funcGetProperty(_credit_sms, CREDIT_VALUE)))
	{
		resultViewData.PushMsg(_TEXT("����ʧ��."));
	}
	else
	{
		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	}
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
	
}
void TriggerDataTopMsg(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, TEST_NUMBER), _TEXT("���������ⶥ����"));


	if (!BuildHastenNotice(ctx, ctx->m_funcGetProperty(0, USER_ID),
		_TEXT("3111"),
		ctx->m_funcGetProperty(_credit_sms, HASTEN_POLICYID),
		ctx->m_funcGetProperty(_credit_sms, LEAVE_REAL_FEE),
		ctx->m_funcGetProperty(_credit_sms, REAL_FEE),
		ctx->m_funcGetProperty(_credit_sms, CREDIT_VALUE)))
	{
		resultViewData.PushMsg(_TEXT("����ʧ��."));
	}
	else
	{
		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	}
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void TriggerPostPaypMsg(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, TEST_NUMBER), _TEXT("�����󸶷��û��߷Ѷ���"));


	if (!BuildHastenNotice(ctx, ctx->m_funcGetProperty(0, USER_ID),
		_TEXT("3200"),
		ctx->m_funcGetProperty(_credit_sms, HASTEN_POLICYID),
		ctx->m_funcGetProperty(_credit_sms, LEAVE_REAL_FEE),
		ctx->m_funcGetProperty(_credit_sms, REAL_FEE),
		ctx->m_funcGetProperty(_credit_sms, CREDIT_VALUE)))
	{
		resultViewData.PushMsg(_TEXT("����ʧ��."));
	}
	else
	{
		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
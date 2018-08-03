// CreditDegree.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "CreditDegree.h"
#include "../../BillingTool/PluginInterface.h"
#include "../../BillingTool/ViewTree.h"
#include "../../BillingTool/ModuleContext.h"
#include "../../BillingTool/BillingTool.h"
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

// CCreditDegreeApp

BEGIN_MESSAGE_MAP(CCreditDegreeApp, CWinApp)
END_MESSAGE_MAP()


// CCreditDegreeApp ����

CCreditDegreeApp::CCreditDegreeApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CCreditDegreeApp ����

//CCreditDegreeApp theApp;


// CCreditDegreeApp ��ʼ��

BOOL CCreditDegreeApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}



void CreateInitCreditDegree(ModuleContext *ctx, void *ptr);
void ActiveTempCreditDegree(ModuleContext *ctx, void *ptr);
void ActiveDynamicCreditDegree(ModuleContext *ctx, void *ptr);
void ActiveInitCreditDegree(ModuleContext *ctx, void *ptr);

void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("���öȴ���"), 0, 0);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("��ʼ���ö�����"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(CreateInitCreditDegree));

	tmpItem = viewTree->InsertItem(_T("��ʱ���ö���Ч"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(ActiveTempCreditDegree));

	tmpItem = viewTree->InsertItem(_T("��̬���ö���Ч"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(ActiveDynamicCreditDegree));

	tmpItem = viewTree->InsertItem(_T("��ʼ���ö���Ч"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(ActiveInitCreditDegree));
}



static bool BuildInitCredit(ModuleContext *ctx,CString serialNumber, CString userId, CString custId,CString vipClass)
{
	try {
		std::string sql = "insert into CS_CTOB_INITCREDIT("
			"	btoc_id, "
			"	serial_number, "
			"	user_id, "
			"	cust_id, "
			"	provider_code, "
			"	vip_class, "
			"	deal_tag, "
			"	update_time, "
			"	update_staff_id) "
			"	values (:v1<char[20]>,"
			"		:v2<char[20]>, "
			"		:v3<char[20]>, "
			"		:v4<char[20]>, "
			"		'CUCC', "
			"		:v5<char[20]>, "
			"		0,sysdate,'test') ";
			


		otl_stream otlStm;
		otlStm.open(1, sql.c_str(), *(ctx->m_dbConn));
		otlStm.set_commit(0);

		otlStm << CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP).c_str()
			<< CommonUtil::CStringToString(serialNumber, CP_ACP).c_str()
			<< CommonUtil::CStringToString(userId, CP_ACP).c_str()
			<< CommonUtil::CStringToString(custId, CP_ACP).c_str()
			<< CommonUtil::CStringToString(vipClass, CP_ACP).c_str();

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



static bool BuildUserCredit(ModuleContext *ctx, CString userId, CString creditValue,CString creditClass,CString creditType)
{
	try {
		std::string sql = "insert into CS_USER_CREDIT("
			"	user_id, "
			"	credit_value, "
			"	credit_class, "
			"	credit_type, "
			"	start_time, "
			"	end_time, "
			"	act_tag, "
			"	update_time, "
			"	update_staff_id) "
			"	values (:v1<char[20]>,"
			"		:v2<char[20]>, "
			"		:v3<char[6]>, "
			"		:v4<char[2]>, "
			"		sysdate,sysdate + 60,"
			"		0,sysdate,'test') ";



		otl_stream otlStm;
		otlStm.open(1, sql.c_str(), *(ctx->m_dbConn));
		otlStm.set_commit(0);

		otlStm << CommonUtil::CStringToString(userId, CP_ACP).c_str()
			<< CommonUtil::CStringToString(creditValue, CP_ACP).c_str()
			<< CommonUtil::CStringToString(creditClass, CP_ACP).c_str()
			<< CommonUtil::CStringToString(creditType, CP_ACP).c_str();

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

void CreateInitCreditDegree(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("��ʼ���ö�����"));
	resultViewData.m_result = _TEXT("�����ɹ�");
	if (!BuildInitCredit(ctx, ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")),
		ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
		ctx->m_funcGetProperty(_common, _TEXT("�ͻ�ID")),
		ctx->m_funcGetProperty(_credit_degree, _TEXT("VIP-CLASS"))))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void ActiveTempCreditDegree(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("��ʱ���ö���Ч"));
	resultViewData.m_result = _TEXT("�����ɹ�");
	if (!BuildUserCredit(ctx, ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
		ctx->m_funcGetProperty(_credit_degree, _TEXT("���ö�ֵ")),
		ctx->m_funcGetProperty(_credit_degree, _TEXT("���öȵȼ�")),
		_TEXT("3")))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void ActiveDynamicCreditDegree(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("��̬���ö���Ч"));
	resultViewData.m_result = _TEXT("�����ɹ�");
	if (!BuildUserCredit(ctx, ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
		ctx->m_funcGetProperty(_credit_degree, _TEXT("���ö�ֵ")),
		ctx->m_funcGetProperty(_credit_degree, _TEXT("���öȵȼ�")),
		_TEXT("2")))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}

void ActiveInitCreditDegree(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("��ʼ���ö���Ч"));
	resultViewData.m_result = _TEXT("�����ɹ�");
	if (!BuildUserCredit(ctx, ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
		ctx->m_funcGetProperty(_credit_degree, _TEXT("���ö�ֵ")),
		ctx->m_funcGetProperty(_credit_degree, _TEXT("���öȵȼ�")),
		_TEXT("1")))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
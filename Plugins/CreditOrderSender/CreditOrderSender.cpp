// CreditOrderSender.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "CreditOrderSender.h"
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

// CCreditOrderSenderApp

BEGIN_MESSAGE_MAP(CCreditOrderSenderApp, CWinApp)
END_MESSAGE_MAP()


// CCreditOrderSenderApp ����

CCreditOrderSenderApp::CCreditOrderSenderApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CCreditOrderSenderApp ����

//CCreditOrderSenderApp theApp;


// CCreditOrderSenderApp ��ʼ��

BOOL CCreditOrderSenderApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


static std::map<CString, PropertyInfo> modulePropertys = {
	
};

void PropertyInitilize(std::map<int, std::map<CString, PropertyInfo> > &gProperty)
{
	gProperty.insert(std::make_pair(_credit_sender, modulePropertys));
}

void TriggerStartUp(ModuleContext *ctx, void *ptr);
void TriggerOnWayStop(ModuleContext *ctx, void *ptr);
void TriggerDoubleStop(ModuleContext *ctx, void *ptr);



static _ItemCallBackDef moduleCallBackDef[] = {
	{ _credit_sender, TriggerStartUp },
	{ _credit_sender, TriggerOnWayStop },
	{ _credit_sender, TriggerDoubleStop } };


void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("�ſ�ָ���"), 0, 0);
	HTREEITEM tmpItem = viewTree->InsertItem(_T("���ɿ���ָ��"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[0])));

	tmpItem = viewTree->InsertItem(_T("���ɵ�ָͣ��"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[1])));

	tmpItem = viewTree->InsertItem(_T("����˫ָͣ��"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[2])));

}



bool BuildCreditOrder(ModuleContext *ctx, CString userId, CString tradeTypeCode)
{
	try {
		std::string sql = "insert into CDT_CREDIT_WORK(trade_type_code, "
			"	intrade_id, "
			"	trade_id, "
			"	user_id, "
			"	main_tag, "
			"	product_id, "
			"	in_time, "
			"	can_exec_time, "
			"	leave_real_fee, "
			"	real_fee, "
			"	credit_value, "
			"	net_type_code, "
			"	deal_tag,  "
			"	finish_time, "
			"	deal_time, "
			"	deal_region_id, "
			"	deal_province_code, "
			"	remark, "
			"	deal_info) "
			"	values(:v1<char[5]>, "
			"		:v2<char[20]>, "
			"		:v3<char[20]>, "
			"		:v4<char[20]>, "
			"		0,999999999,sysdate,sysdate,0,0,0,'C','0',sysdate,sysdate,'test','test','test','')";



		otl_stream otlStm;
		otlStm.open(1, sql.c_str(), *(ctx->m_dbConn));
		otlStm.set_commit(0);

		otlStm << CommonUtil::CStringToString(tradeTypeCode, CP_ACP).c_str()
			<< CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP).c_str()
			<< CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP).c_str()
			<< CommonUtil::CStringToString(userId, CP_ACP).c_str();

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

void TriggerStartUp(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("���ɿ���ָ��"));
	resultViewData.m_result = _TEXT("���ɳɹ�.");
	if (!BuildCreditOrder(ctx , ctx->m_funcGetProperty(_common, _TEXT("�û�ID")) , _TEXT("1100")))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}

void TriggerOnWayStop(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("���ɵ�ָͣ��"));
	resultViewData.m_result = _TEXT("���ɳɹ�.");
	if (!BuildCreditOrder(ctx, ctx->m_funcGetProperty(_common, _TEXT("�û�ID")), _TEXT("3120")))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerDoubleStop(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("����˫ָͣ��"));
	resultViewData.m_result = _TEXT("���ɳɹ�.");
	if (!BuildCreditOrder(ctx, ctx->m_funcGetProperty(_common, _TEXT("�û�ID")), _TEXT("3110")))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
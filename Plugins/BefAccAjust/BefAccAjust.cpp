// BefAccAjust.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "BefAccAjust.h"
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

// CBefAccAjustApp

BEGIN_MESSAGE_MAP(CBefAccAjustApp, CWinApp)
END_MESSAGE_MAP()


// CBefAccAjustApp ����

CBefAccAjustApp::CBefAccAjustApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CBefAccAjustApp ����

//CBefAccAjustApp theApp;


// CBefAccAjustApp ��ʼ��

BOOL CBefAccAjustApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}



void IncrementAjdustByMoney(ModuleContext *ctx, void *ptr);
void IncrementAjdustByRatio(ModuleContext *ctx, void *ptr);
void DecrementAjdustByMoney(ModuleContext *ctx, void *ptr);
void DecrementAjdustByRatio(ModuleContext *ctx, void *ptr);


static _ItemCallBackDef moduleCallBackDef[] = {
				{ _bef_adjust, IncrementAjdustByMoney },
				{ _bef_adjust, IncrementAjdustByRatio },
				{ _bef_adjust, DecrementAjdustByMoney },
				{ _bef_adjust, DecrementAjdustByRatio } };

void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("��ǰ����"), 0, 0);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("��������"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[0])));

	tmpItem = viewTree->InsertItem(_T("����������"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[1])));

	tmpItem = viewTree->InsertItem(_T("��������"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[2])));

	tmpItem = viewTree->InsertItem(_T("����������"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[3])));

	

}



bool BuildBefAccChk(ModuleContext *ctx, CString userId, CString acctId,CString serialNumber,
											CString adjustType,CString adjustMode,CString itemCode,CString moneyOrRatio,CString activeTag)
{
	try {
		std::string sql = "insert into ACC_ADJUST_BEFOR_CHK("
			"	batch_id, "
			"	serial_number, "
			"	user_id, "
			"	acct_id, "
			"	cycle_id, "
			"	adjust_type, "
			"	adjust_mode, "
			"	item_code, "
			"	active_tag, "
			"	adjust_fee, "
			"	real_fee, "
			"	adjust_reson_code, "
			"	region_code, "
			"	adjust_value,  "
			"	adjust_time, "
			"	adjust_depart_id, "
			"	adjust_staff_id, "
			"	act_tag, "
			"	deal_tag, "
			"	deal_time,"
			"	remark, "
			"	adjust_reson,"
			"	check_staff_id, "
			"	check_time) "
			"	values (:v1<char[16]>,"
			"		:v2<char[20]>, "
			"		:v3<char[20]>, "
			"		:v4<char[20]>, "
			"		:v5<char[7]>, "
			"		:v6<char[2]>, "
			"		:v7<char[2]>, "
			"		:v8<char[11]>, "
			"		:v9<char[2]>, "
			"		10000,"
			"		0,0,'test',"
			"		:v10<char[11]>, "
			"		sysdate,'test','test','1','0',sysdate,'NN','NN','test',sysdate)";



		otl_stream otlStm;
		otlStm.open(1, sql.c_str(), *(ctx->m_dbConn));
		otlStm.set_commit(0);

		otlStm << CommonUtil::CStringToString(CommonUtil::GetSysTime(), CP_ACP).c_str()
			<< CommonUtil::CStringToString(serialNumber, CP_ACP).c_str()
			<< CommonUtil::CStringToString(userId, CP_ACP).c_str()
			<< CommonUtil::CStringToString(acctId, CP_ACP).c_str()
			<< CommonUtil::CStringToString(CommonUtil::GetSysYMTime(), CP_ACP).c_str()
			<< CommonUtil::CStringToString(adjustType, CP_ACP).c_str()
			<< CommonUtil::CStringToString(adjustMode, CP_ACP).c_str()
			<< CommonUtil::CStringToString(itemCode, CP_ACP).c_str()
			<< CommonUtil::CStringToString(activeTag, CP_ACP).c_str()
			<< CommonUtil::CStringToString(moneyOrRatio, CP_ACP).c_str();

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


void IncrementAjdustByMoney(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("��ǰ����-��������"));
	resultViewData.m_result = _TEXT("���˳ɹ�");
	if (!BuildBefAccChk(ctx, ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
							ctx->m_funcGetProperty(_common, _TEXT("�˻�ID")),
							ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")),
							_TEXT("2"),_TEXT("1"),
							ctx->m_funcGetProperty(_bef_adjust, _TEXT("��Ŀ����")),
							ctx->m_funcGetProperty(_bef_adjust, _TEXT("���˽��/����")),
							ctx->m_funcGetProperty(_bef_adjust, _TEXT("��Ч��ʶ"))))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void IncrementAjdustByRatio(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("��ǰ����-����������"));
	resultViewData.m_result = _TEXT("���˳ɹ�");
	if (!BuildBefAccChk(ctx, ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
		ctx->m_funcGetProperty(_common, _TEXT("�˻�ID")),
		ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")),
		_TEXT("2"), _TEXT("2"),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("��Ŀ����")),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("���˽��/����")),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("��Ч��ʶ"))))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void DecrementAjdustByMoney(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("��ǰ����-��������"));
	resultViewData.m_result = _TEXT("���˳ɹ�");
	if (!BuildBefAccChk(ctx, ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
		ctx->m_funcGetProperty(_common, _TEXT("�˻�ID")),
		ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")),
		_TEXT("1"), _TEXT("1"),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("��Ŀ����")),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("���˽��/����")),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("��Ч��ʶ"))))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void DecrementAjdustByRatio(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("��ǰ����-����������"));
	resultViewData.m_result = _TEXT("���˳ɹ�");
	if (!BuildBefAccChk(ctx, ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
		ctx->m_funcGetProperty(_common, _TEXT("�˻�ID")),
		ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")),
		_TEXT("1"), _TEXT("2"),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("��Ŀ����")),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("���˽��/����")),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("��Ч��ʶ"))))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
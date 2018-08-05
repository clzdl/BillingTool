// BefAccAjust.cpp : 定义 DLL 的初始化例程。
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

// CBefAccAjustApp

BEGIN_MESSAGE_MAP(CBefAccAjustApp, CWinApp)
END_MESSAGE_MAP()


// CBefAccAjustApp 构造

CBefAccAjustApp::CBefAccAjustApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CBefAccAjustApp 对象

//CBefAccAjustApp theApp;


// CBefAccAjustApp 初始化

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


	HTREEITEM hRoot = viewTree->InsertItem(_T("帐前调账"), 0, 0);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("按金额调增"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[0])));

	tmpItem = viewTree->InsertItem(_T("按比例调增"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[1])));

	tmpItem = viewTree->InsertItem(_T("按金额调减"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[2])));

	tmpItem = viewTree->InsertItem(_T("按比例调减"), 1, 2, hRoot);
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
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("账前调账-按金额调增"));
	resultViewData.m_result = _TEXT("调账成功");
	if (!BuildBefAccChk(ctx, ctx->m_funcGetProperty(_common, _TEXT("用户ID")),
							ctx->m_funcGetProperty(_common, _TEXT("账户ID")),
							ctx->m_funcGetProperty(_common, _TEXT("测试号码")),
							_TEXT("2"),_TEXT("1"),
							ctx->m_funcGetProperty(_bef_adjust, _TEXT("账目编码")),
							ctx->m_funcGetProperty(_bef_adjust, _TEXT("调账金额/比例")),
							ctx->m_funcGetProperty(_bef_adjust, _TEXT("生效标识"))))
	{
		resultViewData.m_result = _TEXT("调账失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void IncrementAjdustByRatio(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("账前调账-按比例调增"));
	resultViewData.m_result = _TEXT("调账成功");
	if (!BuildBefAccChk(ctx, ctx->m_funcGetProperty(_common, _TEXT("用户ID")),
		ctx->m_funcGetProperty(_common, _TEXT("账户ID")),
		ctx->m_funcGetProperty(_common, _TEXT("测试号码")),
		_TEXT("2"), _TEXT("2"),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("账目编码")),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("调账金额/比例")),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("生效标识"))))
	{
		resultViewData.m_result = _TEXT("调账失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void DecrementAjdustByMoney(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("账前调账-按金额调减"));
	resultViewData.m_result = _TEXT("调账成功");
	if (!BuildBefAccChk(ctx, ctx->m_funcGetProperty(_common, _TEXT("用户ID")),
		ctx->m_funcGetProperty(_common, _TEXT("账户ID")),
		ctx->m_funcGetProperty(_common, _TEXT("测试号码")),
		_TEXT("1"), _TEXT("1"),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("账目编码")),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("调账金额/比例")),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("生效标识"))))
	{
		resultViewData.m_result = _TEXT("调账失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void DecrementAjdustByRatio(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("测试号码")), _TEXT("账前调账-按比例调减"));
	resultViewData.m_result = _TEXT("调账成功");
	if (!BuildBefAccChk(ctx, ctx->m_funcGetProperty(_common, _TEXT("用户ID")),
		ctx->m_funcGetProperty(_common, _TEXT("账户ID")),
		ctx->m_funcGetProperty(_common, _TEXT("测试号码")),
		_TEXT("1"), _TEXT("2"),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("账目编码")),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("调账金额/比例")),
		ctx->m_funcGetProperty(_bef_adjust, _TEXT("生效标识"))))
	{
		resultViewData.m_result = _TEXT("调账失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
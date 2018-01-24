// PrefeeRestore.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "PrefeeRestore.h"
#include "../../BillingTool/PluginInterface.h"
#include "../../BillingTool/ViewTree.h"
#include "../../BillingTool/ModuleContext.h"
#include "../../BillingTool/BillingTool.h"
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

// CPrefeeRestoreApp

BEGIN_MESSAGE_MAP(CPrefeeRestoreApp, CWinApp)
END_MESSAGE_MAP()


// CPrefeeRestoreApp 构造

CPrefeeRestoreApp::CPrefeeRestoreApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CPrefeeRestoreApp 对象

//CPrefeeRestoreApp theApp;


// CPrefeeRestoreApp 初始化

BOOL CPrefeeRestoreApp::InitInstance()
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

static CString GetSysTIme()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d%02d%02d%02d%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return result;
}

static int GetCurDay()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	
	return st.wDay;
}

static CString GetSysYMDTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d%02d"), st.wYear, st.wMonth, st.wDay);
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

void TriggerPrefee(ModuleContext *ctx, void *ptr);

void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("预存返还功能"), 0, 0);
	viewTree->SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("生成返还记录"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerPrefee));


}



bool BuildPrefee(ModuleContext *ctx, CString userId, CString activityId,CString ruleType,
			CString feeRuleId,CString cycleFee, CString cycleUnit , CString validProdState , CString acctBalanceId)
{
	try {
		std::string sql = "insert into CS_USER_PREFEE(user_id, "
			"	activity_id, "
			"	component_id, "
			"	component_type, "
			"	prefee_id, "
			"	prefee_type, "
			"	pre_fee, "
			"	pre_deposit_code, "
			"	month_fee, "
			"	reward_type, "
			"	reward_fee, "
			"	reward_deposit_code, "
			"	cont_deposit_code,  "
			"	fee_type_code, "
			"	next_tag, "
			"	start_date, "
			"	end_date, "
			"	item_id, "
			"	fire_day, "
			"	fire_count,"
			"	rule_type, "
			"	fee_rule_id, "
			"	fee_start_tag, "
			"	fee_start_offset, "
			"	fee_start_unit, "
			"	cycle_fee,"
			"	cycle_unit, "
			"	cycle_offset, "
			"	fee_cycle_unit , "
			"	fee_cycle_offset, "
			"	first_date, "
			"	exec_date, "
			"	next_date, "
			"	acct_balance_id, "
			"	update_staff_id , "
			"	update_depart_id, "
			"	update_date, "
			"	provider_prefee_inst_id, "
			"	valid_prod_state, "
			"	prefee_desc, "
			"	pre_payment_id, "
			"	pre_fee_mode_code, "
			"	pre_sms_id, "
			"	reward_payment_id,"
			"	reward_fee_mode_code , "
			"	reward_sms_id ,"
			"	last_sms_id , "
			"	prefee_name , "
			"	reward_return_fee , "
			"	activity_inst_id) "
			"	values(:v1<char[20]>, "
			"		:v2<char[20]>, "
			"		0,'C',0,'F',10000,0,0,'Y',10000,0,0,0,0,sysdate, sysdate + 60,"
			"		0,:v3<int>,0,:v4<char[2]>,:v5<char[20]>,0,0,0,"
			"		:v6<char[20]>,:v7<char[20]>,0,0,0,"
			"		sysdate,sysdate,sysdate,:v8<char[20]>,'test','test',sysdate,"
			"		0,:v9<char[2]>,'',0,0,0,50000002,100009,0,0,'',0,0)";



		otl_stream otlStm;
		otlStm.open(1, sql.c_str(), *(ctx->m_dbConn));
		otlStm.set_commit(0);

		otlStm << CStringToString(userId, CP_ACP).c_str()
			<< CStringToString(activityId, CP_ACP).c_str()
			<< GetCurDay()
			<< CStringToString(ruleType, CP_ACP).c_str()
			<< CStringToString(feeRuleId, CP_ACP).c_str()
			<< CStringToString(cycleFee, CP_ACP).c_str()
			<< CStringToString(cycleUnit, CP_ACP).c_str()
			<< CStringToString(acctBalanceId, CP_ACP).c_str()
			<< CStringToString(validProdState, CP_ACP).c_str();

		ctx->m_dbConn->commit();
	}
	catch (otl_exception &e)
	{
		char strExp[4096] = { 0 };
		sprintf_s(strExp, "code:%d,msg:%s,var_info:%s,stm_text:%s\n", e.code, e.msg, e.var_info, e.stm_text);
		CString exp = ctx->m_funcString2CString(strExp, CP_ACP);
		ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_STATUSBAR, 0, (LPARAM)exp.GetBuffer());
		exp.ReleaseBuffer();
		return false;
	}

	return true;
}


void TriggerPrefee(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("测试号码")), _TEXT("预存返回功能"));
	resultViewData.m_result = _TEXT("触发成功.");
	if (!BuildPrefee(ctx, ctx->m_funcGetProperty(0, _TEXT("用户ID")),
						ctx->m_funcGetProperty(4, _TEXT("活动ID")),
						ctx->m_funcGetProperty(4, _TEXT("规则类型")),
						ctx->m_funcGetProperty(4, _TEXT("自定义规则ID")),
						ctx->m_funcGetProperty(4, _TEXT("返还费用")),
						ctx->m_funcGetProperty(4, _TEXT("返还周期")),
						ctx->m_funcGetProperty(4, _TEXT("校验规则")),
						ctx->m_funcGetProperty(4, _TEXT("预存返还账本")) ))
	{
		resultViewData.m_result = _TEXT("触发失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
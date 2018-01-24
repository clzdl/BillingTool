// BefAccAjust.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "BefAccAjust.h"
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

static CString GetSysTIme()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d%02d%02d%02d%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
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


void IncrementAjdustByMoney(ModuleContext *ctx, void *ptr);
void IncrementAjdustByRatio(ModuleContext *ctx, void *ptr);
void DecrementAjdustByMoney(ModuleContext *ctx, void *ptr);
void DecrementAjdustByRatio(ModuleContext *ctx, void *ptr);

void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("帐前调账功能"), 0, 0);
	viewTree->SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("按比例调增"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(IncrementAjdustByRatio));

	tmpItem = viewTree->InsertItem(_T("按金额调增"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(IncrementAjdustByMoney));

	tmpItem = viewTree->InsertItem(_T("按比例调减"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(DecrementAjdustByRatio));

	tmpItem = viewTree->InsertItem(_T("按金额调减"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(DecrementAjdustByMoney));

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

		otlStm << CStringToString(GetSysTIme(), CP_ACP).c_str()
			<< CStringToString(serialNumber, CP_ACP).c_str()
			<< CStringToString(userId, CP_ACP).c_str()
			<< CStringToString(acctId, CP_ACP).c_str()
			<< CStringToString(GetSysYMTime(), CP_ACP).c_str()
			<< CStringToString(adjustType, CP_ACP).c_str()
			<< CStringToString(adjustMode, CP_ACP).c_str()
			<< CStringToString(itemCode, CP_ACP).c_str()
			<< CStringToString(activeTag, CP_ACP).c_str()
			<< CStringToString(moneyOrRatio, CP_ACP).c_str();

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


void IncrementAjdustByMoney(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("测试号码")), _TEXT("账前调账-按金额调增"));
	resultViewData.m_result = _TEXT("调账成功");
	if (!BuildBefAccChk(ctx, ctx->m_funcGetProperty(0, _TEXT("用户ID")),
							ctx->m_funcGetProperty(0, _TEXT("账户ID")),
							ctx->m_funcGetProperty(0, _TEXT("测试号码")),
							_TEXT("2"),_TEXT("1"),
							ctx->m_funcGetProperty(2, _TEXT("账目编码")),
							ctx->m_funcGetProperty(2, _TEXT("调账金额/比例")),
							ctx->m_funcGetProperty(2, _TEXT("生效标识"))))
	{
		resultViewData.m_result = _TEXT("调账失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void IncrementAjdustByRatio(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("测试号码")), _TEXT("账前调账-按比例调增"));
	resultViewData.m_result = _TEXT("调账成功");
	if (!BuildBefAccChk(ctx, ctx->m_funcGetProperty(0, _TEXT("用户ID")),
		ctx->m_funcGetProperty(0, _TEXT("账户ID")),
		ctx->m_funcGetProperty(0, _TEXT("测试号码")),
		_TEXT("2"), _TEXT("2"),
		ctx->m_funcGetProperty(2, _TEXT("账目编码")),
		ctx->m_funcGetProperty(2, _TEXT("调账金额/比例")),
		ctx->m_funcGetProperty(2, _TEXT("生效标识"))))
	{
		resultViewData.m_result = _TEXT("调账失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void DecrementAjdustByMoney(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("测试号码")), _TEXT("账前调账-按金额调减"));
	resultViewData.m_result = _TEXT("调账成功");
	if (!BuildBefAccChk(ctx, ctx->m_funcGetProperty(0, _TEXT("用户ID")),
		ctx->m_funcGetProperty(0, _TEXT("账户ID")),
		ctx->m_funcGetProperty(0, _TEXT("测试号码")),
		_TEXT("1"), _TEXT("1"),
		ctx->m_funcGetProperty(2, _TEXT("账目编码")),
		ctx->m_funcGetProperty(2, _TEXT("调账金额/比例")),
		ctx->m_funcGetProperty(2, _TEXT("生效标识"))))
	{
		resultViewData.m_result = _TEXT("调账失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void DecrementAjdustByRatio(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("测试号码")), _TEXT("账前调账-按比例调减"));
	resultViewData.m_result = _TEXT("调账成功");
	if (!BuildBefAccChk(ctx, ctx->m_funcGetProperty(0, _TEXT("用户ID")),
		ctx->m_funcGetProperty(0, _TEXT("账户ID")),
		ctx->m_funcGetProperty(0, _TEXT("测试号码")),
		_TEXT("1"), _TEXT("2"),
		ctx->m_funcGetProperty(2, _TEXT("账目编码")),
		ctx->m_funcGetProperty(2, _TEXT("调账金额/比例")),
		ctx->m_funcGetProperty(2, _TEXT("生效标识"))))
	{
		resultViewData.m_result = _TEXT("调账失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
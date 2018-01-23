// CreditOrderSender.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "CreditOrderSender.h"
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

// CCreditOrderSenderApp

BEGIN_MESSAGE_MAP(CCreditOrderSenderApp, CWinApp)
END_MESSAGE_MAP()


// CCreditOrderSenderApp 构造

CCreditOrderSenderApp::CCreditOrderSenderApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CCreditOrderSenderApp 对象

//CCreditOrderSenderApp theApp;


// CCreditOrderSenderApp 初始化

BOOL CCreditOrderSenderApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


#define FAILURE		-1
#define SUCCESS		0
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

static CString GetSysYMDTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d%02d"), st.wYear, st.wMonth, st.wDay);
	return result;
}

static CString GetSerialNo()
{
	CString csSerial;
	SYSTEMTIME st;
	GetLocalTime(&st);
	csSerial.Format(_TEXT("%02d%02d%02d"), st.wHour, st.wMinute, st.wSecond);

	return csSerial;
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

void TriggerStartUp(ModuleContext *ctx, void *ptr);
void TriggerOnWayStop(ModuleContext *ctx, void *ptr);
void TriggerDoubleStop(ModuleContext *ctx, void *ptr);


void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("信控指令发送功能"), 0, 0);
	viewTree->SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("生成开机指令"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerStartUp));

	tmpItem = viewTree->InsertItem(_T("生成单停指令"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerOnWayStop));

	tmpItem = viewTree->InsertItem(_T("生成双停指令"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerDoubleStop));

	viewTree->Expand(hRoot, TVE_EXPAND);

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

		otlStm << CStringToString(tradeTypeCode, CP_ACP).c_str()
			<< CStringToString(GetSysTIme(), CP_ACP).c_str()
			<< CStringToString(GetSysTIme(), CP_ACP).c_str()
			<< CStringToString(userId, CP_ACP).c_str();

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

void TriggerStartUp(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("测试号码")), _TEXT("生成开机指令"));
	resultViewData.m_result = _TEXT("生成成功.");
	if (!BuildCreditOrder(ctx , ctx->m_funcGetProperty(0, _TEXT("用户ID")) , _TEXT("1100")))
	{
		resultViewData.m_result = _TEXT("触发失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}

void TriggerOnWayStop(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("测试号码")), _TEXT("生成单停指令"));
	resultViewData.m_result = _TEXT("生成成功.");
	if (!BuildCreditOrder(ctx, ctx->m_funcGetProperty(0, _TEXT("用户ID")), _TEXT("3120")))
	{
		resultViewData.m_result = _TEXT("触发失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerDoubleStop(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("测试号码")), _TEXT("生成双停指令"));
	resultViewData.m_result = _TEXT("生成成功.");
	if (!BuildCreditOrder(ctx, ctx->m_funcGetProperty(0, _TEXT("用户ID")), _TEXT("3110")))
	{
		resultViewData.m_result = _TEXT("触发失败.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
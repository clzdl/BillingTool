// CreditOrderSender.cpp : ���� DLL �ĳ�ʼ�����̡�
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


	HTREEITEM hRoot = viewTree->InsertItem(_T("�ſ�ָ��͹���"), 0, 0);
	viewTree->SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("���ɿ���ָ��"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerStartUp));

	tmpItem = viewTree->InsertItem(_T("���ɵ�ָͣ��"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerOnWayStop));

	tmpItem = viewTree->InsertItem(_T("����˫ָͣ��"), 1, 2, hRoot);
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
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("���Ժ���")), _TEXT("���ɿ���ָ��"));
	resultViewData.m_result = _TEXT("���ɳɹ�.");
	if (!BuildCreditOrder(ctx , ctx->m_funcGetProperty(0, _TEXT("�û�ID")) , _TEXT("1100")))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}

void TriggerOnWayStop(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("���Ժ���")), _TEXT("���ɵ�ָͣ��"));
	resultViewData.m_result = _TEXT("���ɳɹ�.");
	if (!BuildCreditOrder(ctx, ctx->m_funcGetProperty(0, _TEXT("�û�ID")), _TEXT("3120")))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
void TriggerDoubleStop(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("���Ժ���")), _TEXT("����˫ָͣ��"));
	resultViewData.m_result = _TEXT("���ɳɹ�.");
	if (!BuildCreditOrder(ctx, ctx->m_funcGetProperty(0, _TEXT("�û�ID")), _TEXT("3110")))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
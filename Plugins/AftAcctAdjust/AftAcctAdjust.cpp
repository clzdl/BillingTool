// AftAcctAdjust.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "AftAcctAdjust.h"
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

// CAftAcctAdjustApp

BEGIN_MESSAGE_MAP(CAftAcctAdjustApp, CWinApp)
END_MESSAGE_MAP()


// CAftAcctAdjustApp ����

CAftAcctAdjustApp::CAftAcctAdjustApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CAftAcctAdjustApp ����

//CAftAcctAdjustApp theApp;


// CAftAcctAdjustApp ��ʼ��

BOOL CAftAcctAdjustApp::InitInstance()
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


	HTREEITEM hRoot = viewTree->InsertItem(_T("�ʺ����"), 0, 0);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("����������"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(IncrementAjdustByRatio));

	tmpItem = viewTree->InsertItem(_T("��������"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(IncrementAjdustByMoney));

	tmpItem = viewTree->InsertItem(_T("����������"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(DecrementAjdustByRatio));

	tmpItem = viewTree->InsertItem(_T("��������"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(DecrementAjdustByMoney));
}



bool BuildAftAccChk(ModuleContext *ctx, CString userId, CString acctId, CString serialNumber,
	CString adjustType, CString adjustMode,CString billId, CString itemCode, CString moneyOrRatio,
	CString fee, CString balance,CString recvTag)
{
	try {
		std::string sql = "insert into acc_adjust_after_chk("
			"	batch_id, "
			"	serial_number, "
			"	user_id, "
			"	acct_id, "
			"	cycle_id, "
			"	adjust_type, "
			"	adjust_mode, "
			"	adjust_fee, "
			"	real_fee, "
			"	adjust_reson_code, "
			"	region_code, "
			"	adjust_value,  "
			"	bill_id, "
			"	item_code, "
			"	fee, "
			"	balance, "
			"	pay_tag, "
			"	can_pay_tag, "
			"	recv_tag, "
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
			"		10000,0, 0, 'test', "
			"		:v8<char[11]>, "
			"		:v9<char[17]>, "
			"		:v10<char[11]>, "
			"		:v11<char[11]>, "
			"		:v12<char[11]>, "
			"		'0','0',"
			"		:v13<char[2]>, "
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
			<< CStringToString(moneyOrRatio, CP_ACP).c_str()
			<< CStringToString(billId, CP_ACP).c_str()
			<< CStringToString(itemCode, CP_ACP).c_str()
			<< CStringToString(fee, CP_ACP).c_str()
			<< CStringToString(balance, CP_ACP).c_str()
			<< CStringToString(recvTag, CP_ACP).c_str();

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
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("���Ժ���")), _TEXT("�˺����-��������"));
	resultViewData.m_result = _TEXT("���˳ɹ�");
	if (!BuildAftAccChk(ctx, ctx->m_funcGetProperty(0, _TEXT("�û�ID")),
		ctx->m_funcGetProperty(0, _TEXT("�˻�ID")),
		ctx->m_funcGetProperty(0, _TEXT("���Ժ���")),
		_TEXT("2"), _TEXT("1"),
		ctx->m_funcGetProperty(3, _TEXT("�˵�ID")),
		ctx->m_funcGetProperty(3, _TEXT("��Ŀ����")),
		ctx->m_funcGetProperty(3, _TEXT("���˽��/����")),
		ctx->m_funcGetProperty(3, _TEXT("�˵�����")),
		ctx->m_funcGetProperty(3, _TEXT("�˵����")),
		ctx->m_funcGetProperty(3, _TEXT("��������ʽ"))))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void IncrementAjdustByRatio(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("���Ժ���")), _TEXT("�˺����-����������"));
	resultViewData.m_result = _TEXT("���˳ɹ�");
	if (!BuildAftAccChk(ctx, ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
		ctx->m_funcGetProperty(_common, _TEXT("�˻�ID")),
		ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")),
		_TEXT("2"), _TEXT("2"),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("�˵�ID")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("��Ŀ����")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("���˽��/����")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("�˵�����")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("�˵����")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("��������ʽ"))))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void DecrementAjdustByMoney(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("�˺����-��������"));
	resultViewData.m_result = _TEXT("���˳ɹ�");
	if (!BuildAftAccChk(ctx, ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
		ctx->m_funcGetProperty(_common, _TEXT("�˻�ID")),
		ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")),
		_TEXT("1"), _TEXT("1"),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("�˵�ID")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("��Ŀ����")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("���˽��/����")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("�˵�����")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("�˵����")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("��������ʽ"))))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
void DecrementAjdustByRatio(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("�˺����-����������"));
	resultViewData.m_result = _TEXT("���˳ɹ�");
	if (!BuildAftAccChk(ctx, ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
		ctx->m_funcGetProperty(_common, _TEXT("�˻�ID")),
		ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")),
		_TEXT("1"), _TEXT("2"),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("�˵�ID")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("��Ŀ����")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("���˽��/����")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("�˵�����")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("�˵����")),
		ctx->m_funcGetProperty(_aft_adjust, _TEXT("��������ʽ"))))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
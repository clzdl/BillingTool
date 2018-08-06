// PrefeeRestore.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "PrefeeRestore.h"
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

// CPrefeeRestoreApp

BEGIN_MESSAGE_MAP(CPrefeeRestoreApp, CWinApp)
END_MESSAGE_MAP()


// CPrefeeRestoreApp ����

CPrefeeRestoreApp::CPrefeeRestoreApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CPrefeeRestoreApp ����

//CPrefeeRestoreApp theApp;


// CPrefeeRestoreApp ��ʼ��

BOOL CPrefeeRestoreApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


const CString ACTIVITY_ID = _TEXT("�ID");
const CString RULE_TYPE = _TEXT("��������");
const CString RULE_TYPE_AVG = _TEXT("����");
const CString RULE_TYPE_CUSTOM = _TEXT("�Զ���");
const CString CUSTOM_RULE_ID = _TEXT("�Զ������ID");
const CString PRESENT_FEE = _TEXT("��������");
const CString PRESENT_CYCLE = _TEXT("��������");
const CString PRESENT_CYCLE_DAY = _TEXT("����");
const CString PRESENT_CYCLE_NATURALDAY = _TEXT("����Ȼ��");
const CString PRESENT_CYCLE_MONTH = _TEXT("����");
const CString PRESENT_CYCLE_NATURALMONTH = _TEXT("����Ȼ��");
const CString VALID_RULE = _TEXT("У�����");
const CString VALID_RULE_NOCHECK = _TEXT("��У��ǿ�Ʒ���");
const CString VALID_RULE_NOPASS_DISCARD = _TEXT("У�鲻ͨ������");
const CString VALID_RULE_NOPASS_DELAY = _TEXT("У�鲻ͨ��˳��");
const CString PRESENT_BALANCE = _TEXT("Ԥ�淵���˱�");


static std::map<CString, PropertyGrid> modulePropertys = {
	{ ACTIVITY_ID,
		{ _TEXT("1111111000"),nullptr , FALSE , }
	},
	{ RULE_TYPE,
		{ RULE_TYPE_AVG,nullptr , TRUE ,{
				{ RULE_TYPE_AVG,_TEXT("0") },
				{ RULE_TYPE_CUSTOM,_TEXT("1") }
			}
		}
	},
	{ CUSTOM_RULE_ID,
		{ _TEXT("1101111000"),nullptr , FALSE , }
	},
	{ PRESENT_FEE,
		{ _TEXT("10000"),nullptr , FALSE , }
	},
	{ PRESENT_CYCLE,
		{ PRESENT_CYCLE_DAY,nullptr , TRUE ,{
				{ PRESENT_CYCLE_DAY,_TEXT("0") },
				{ PRESENT_CYCLE_NATURALDAY,_TEXT("1") },
				{ PRESENT_CYCLE_MONTH,_TEXT("2") },
				{ PRESENT_CYCLE_NATURALMONTH,_TEXT("3") }
			}
		}
	},
	{ VALID_RULE,
		{ VALID_RULE_NOCHECK,nullptr , TRUE ,{
				{ VALID_RULE_NOCHECK,_TEXT("0") },
				{ VALID_RULE_NOPASS_DISCARD,_TEXT("1") },
				{ VALID_RULE_NOPASS_DELAY,_TEXT("2") }
			}
		}
	},
	{ PRESENT_BALANCE,
		{ _TEXT("2111111010130"),nullptr , FALSE , }
	}
};

void PropertyInitilize(std::map<int, std::map<CString, PropertyGrid> > &gProperty)
{
	gProperty.insert(std::make_pair(_prefee_restore, modulePropertys));
}


void TriggerPrefee(ModuleContext *ctx, void *ptr);


static _ItemCallBackDef moduleCallBackDef[] = {
	{ _prefee_restore, TriggerPrefee } };


void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("Ԥ�淵��"), 0, 0);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("���ɷ�����¼"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[0])));


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

		otlStm << CommonUtil::CStringToString(userId, CP_ACP).c_str()
			<< CommonUtil::CStringToString(activityId, CP_ACP).c_str()
			<< CommonUtil::GetCurDay()
			<< CommonUtil::CStringToString(ruleType, CP_ACP).c_str()
			<< CommonUtil::CStringToString(feeRuleId, CP_ACP).c_str()
			<< CommonUtil::CStringToString(cycleFee, CP_ACP).c_str()
			<< CommonUtil::CStringToString(cycleUnit, CP_ACP).c_str()
			<< CommonUtil::CStringToString(acctBalanceId, CP_ACP).c_str()
			<< CommonUtil::CStringToString(validProdState, CP_ACP).c_str();

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


void TriggerPrefee(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, TEST_NUMBER), _TEXT("Ԥ�淵������"));
	if (!BuildPrefee(ctx, ctx->m_funcGetProperty(_common, USER_ID),
						ctx->m_funcGetProperty(_prefee_restore, ACTIVITY_ID),
						ctx->m_funcGetProperty(_prefee_restore, RULE_TYPE),
						ctx->m_funcGetProperty(_prefee_restore, CUSTOM_RULE_ID),
						ctx->m_funcGetProperty(_prefee_restore, PRESENT_FEE),
						ctx->m_funcGetProperty(_prefee_restore, PRESENT_CYCLE),
						ctx->m_funcGetProperty(_prefee_restore, VALID_RULE),
						ctx->m_funcGetProperty(_prefee_restore, PRESENT_BALANCE) ))
	{
		resultViewData.PushMsg(_TEXT("����ʧ��."));
	}
	else
	{
		resultViewData.PushMsg(_TEXT("�����ɹ�."));
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
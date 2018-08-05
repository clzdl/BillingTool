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



static std::map<CString, PropertyGrid> modulePropertys = {
	{ _TEXT("�ID"),
		{ _TEXT("1111111000"),nullptr , FALSE , }
	},
	{ _TEXT("��������"),
		{ _TEXT("����"),nullptr , TRUE ,{
				{ _TEXT("����"),_TEXT("0") },
				{ _TEXT("�Զ���"),_TEXT("1") }
			}
		}
	},
	{ _TEXT("�Զ������ID"),
		{ _TEXT("1101111000"),nullptr , FALSE , }
	},
	{ _TEXT("��������"),
		{ _TEXT("10000"),nullptr , FALSE , }
	},
	{ _TEXT("��������"),
		{ _TEXT("����"),nullptr , TRUE ,{
				{ _TEXT("����"),_TEXT("0") },
				{ _TEXT("����Ȼ��"),_TEXT("1") },
				{ _TEXT("����"),_TEXT("2") },
				{ _TEXT("����Ȼ��"),_TEXT("3") }
			}
		}
	},
	{ _TEXT("У�����"),
		{ _TEXT("��У��ǿ�Ʒ���"),nullptr , TRUE ,{
				{ _TEXT("��У��ǿ�Ʒ���"),_TEXT("0") },
				{ _TEXT("У�鲻ͨ������"),_TEXT("1") },
				{ _TEXT("У�鲻ͨ��˳��"),_TEXT("2") }
			}
		}
	},
	{ _TEXT("Ԥ�淵���˱�"),
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
	ListViewData resultViewData(ctx->m_funcGetProperty(_common, _TEXT("���Ժ���")), _TEXT("Ԥ�淵�ع���"));
	resultViewData.m_result = _TEXT("�����ɹ�.");
	if (!BuildPrefee(ctx, ctx->m_funcGetProperty(_common, _TEXT("�û�ID")),
						ctx->m_funcGetProperty(_prefee_restore, _TEXT("�ID")),
						ctx->m_funcGetProperty(_prefee_restore, _TEXT("��������")),
						ctx->m_funcGetProperty(_prefee_restore, _TEXT("�Զ������ID")),
						ctx->m_funcGetProperty(_prefee_restore, _TEXT("��������")),
						ctx->m_funcGetProperty(_prefee_restore, _TEXT("��������")),
						ctx->m_funcGetProperty(_prefee_restore, _TEXT("У�����")),
						ctx->m_funcGetProperty(_prefee_restore, _TEXT("Ԥ�淵���˱�")) ))
	{
		resultViewData.m_result = _TEXT("����ʧ��.");
	}

	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);

}
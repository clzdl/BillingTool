#include "stdafx.h"
#include <map>
#include "PubFunc.h"
#include "BillingTool.h"
#include "PropertiesWnd.h"
#include "../Plugins/UtilDll/UtilDll.h"
#include "ViewTree.h"
#include "PluginInterface.h"

void cbTestPhoneChg(CPropertiesWnd *propWnd, std::map<CString, PropertyGrid> &modProp, CString newValue);


std::map<int, std::map<CString, PropertyGrid> > gProperties = {
	{ _common /*公共属性*/,
		{
			{ _TEXT("IP地址"),
				{ _TEXT("192.168.88.150"),nullptr,FALSE, }
			},
			{ _TEXT("端口号"),
				{ _TEXT("4444"),nullptr,FALSE, }
			},
			{ _TEXT("测试号码"),
				{ _TEXT("17001818555"),cbTestPhoneChg,FALSE, }
			},
			{ _TEXT("账户ID"),
				{ _TEXT("320150105718968"),nullptr , FALSE, }
			},
			{ _TEXT("用户ID"),
				{ _TEXT("120150105199770"),nullptr , FALSE , }
			},
			{ _TEXT("用户IMSI"),
				{ _TEXT("4600121321301023010"),nullptr , FALSE , }
			},
			{ _TEXT("用户IMEI"),
				{ _TEXT("4600121321301023010"),nullptr , FALSE , }
			},
			{ _TEXT("用户归属地"),
				{ _TEXT("311"),nullptr , FALSE , }
			},
			{ _TEXT("归属运营商"),
				{ _TEXT("CMCC"),nullptr , FALSE , }
			},
			{ _TEXT("客户ID"),
				{ _TEXT("220150105192242"),nullptr , FALSE , }
			},
			{ _TEXT("数据库连接串"),
				{ _TEXT("cmcc/CMCC@fxzn"),nullptr, FALSE , }
			},
			{ _TEXT("用户名"),
				{ _TEXT("chengl"),nullptr, FALSE , }
			},
			{ _TEXT("密码"),
				{ _TEXT("chengl123"),nullptr , FALSE , }
			}
		}
	}
};


void cbTestPhoneChg(CPropertiesWnd *propWnd, std::map<CString, PropertyGrid> &modProp, CString newValue)
{
	if (!gDbConn.connected)
	{
		CString text;
		text.Format(_TEXT("数据库未连接"));
		theApp.GetMainWnd()->SendMessage(MSG_WRITE_MSG2_STATUSBAR, 0, (LPARAM)text.GetBuffer());
		text.ReleaseBuffer();
		return;
	}
	newValue.Trim();

	char strUserId[30] = { 0 }, strAcctId[30] = { 0 }, strCustId[30] = { 0 };
	try {
		std::string sql = "select to_char(t1.user_id), to_char(t2.acct_id),to_char(t1.cust_id) "
			" from cs_user_info t1, cs_user_payrelation t2 "
			" where t1.user_id = t2.user_id "
			"	and t2.default_tag = '1' "
			"	and t2.state = '0' "
			"	and sysdate between t2.start_date and t2.end_date "
			"	and serial_number = :v1<char[32]>";


		otl_stream otlStm;
		otlStm.open(1, sql.c_str(), gDbConn);
		otlStm.set_commit(0);

		otlStm << CommonUtil::CStringToString(newValue, CP_ACP).c_str();

		otlStm >> strUserId >> strAcctId >> strCustId;

		modProp.at(_TEXT("账户ID")).propertyValue = CommonUtil::StringToCString(strAcctId, CP_ACP);
		modProp.at(_TEXT("用户ID")).propertyValue = CommonUtil::StringToCString(strUserId, CP_ACP);
		modProp.at(_TEXT("客户ID")).propertyValue = CommonUtil::StringToCString(strCustId, CP_ACP);
	}
	catch (otl_exception &e)
	{
		char strExp[4096] = { 0 };
		sprintf_s(strExp, "code:%d,msg:%s,var_info:%s,stm_text:%s\n", e.code, e.msg, e.var_info, e.stm_text);
		CString exp = CommonUtil::StringToCString(strExp, CP_ACP);
		theApp.GetMainWnd()->SendMessage(MSG_WRITE_MSG2_STATUSBAR, 0, (LPARAM)exp.GetBuffer());
		exp.ReleaseBuffer();
	}



	propWnd->Refresh(_common);
}
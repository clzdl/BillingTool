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
			{ IP_ADDR,
				{ _TEXT("192.168.88.150"),nullptr,FALSE, }
			},
			{ IP_PORT,
				{ _TEXT("4444"),nullptr,FALSE, }
			},
			{ TEST_NUMBER,
				{ _TEXT("17001818555"),cbTestPhoneChg,FALSE, }
			},
			{ ACCT_ID,
				{ _TEXT("320150105718968"),nullptr , FALSE, }
			},
			{ USER_ID,
				{ _TEXT("120150105199770"),nullptr , FALSE , }
			},
			{ USER_IMSI,
				{ _TEXT("4600121321301023010"),nullptr , FALSE , }
			},
			{ USER_IMEI,
				{ _TEXT("4600121321301023010"),nullptr , FALSE , }
			},
			{ USER_HOME_CODE,
				{ _TEXT("311"),nullptr , FALSE , }
			},
			{ USER_PROVIDER_CODE,
				{ _TEXT("CMCC"),nullptr , FALSE , }
			},
			{ CUST_ID,
				{ _TEXT("220150105192242"),nullptr , FALSE , }
			},
			{ DB_CONN_STRING,
				{ _TEXT("cmcc/CMCC@fxzn"),nullptr, FALSE , }
			},
			{ HOST_USERNAME,
				{ _TEXT("chengl"),nullptr, FALSE , }
			},
			{ HOST_USERPWD ,
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

	char userId[30] = { 0 }, acctId[30] = { 0 }, custId[30] = { 0 };
	try {
		std::string sql ="select t.user_id,t.cust_id from cs_user_info t where t.serial_number = :v1<char[21]>";

		otl_stream otlStm;
		otlStm.set_all_column_types(otl_all_num2str); 
		otlStm.open(1, sql.c_str(), gDbConn);
		otlStm.set_commit(0);
		otlStm << CommonUtil::CStringToString(newValue, CP_ACP).c_str();
		otlStm >> userId >> custId;
		otlStm.close();

		if (userId[0] != '\0')
		{
			sql = "select t.acct_id from cs_user_payrelation t where t.user_id = :v1<char[30]> and t.state = '1' and t.default_tag ='1'";
			otlStm.open(1, sql.c_str(), gDbConn);
			otlStm.set_commit(0);
			otlStm << userId;
			otlStm >> acctId;
			otlStm.close();
		}

	
		modProp.at(ACCT_ID).propertyValue = CommonUtil::StringToCString(acctId, CP_ACP);
		modProp.at(USER_ID).propertyValue = CommonUtil::StringToCString(userId, CP_ACP);
		modProp.at(CUST_ID).propertyValue = CommonUtil::StringToCString(custId, CP_ACP);
		propWnd->Refresh(_common);
	}
	catch (otl_exception &e)
	{
		char strExp[4096] = { 0 };
		sprintf_s(strExp, "code:%d,msg:%s,var_info:%s,stm_text:%s\n", e.code, e.msg, e.var_info, e.stm_text);
		CString exp = CommonUtil::StringToCString(strExp, CP_ACP);
		theApp.GetMainWnd()->SendMessage(MSG_WRITE_MSG2_STATUSBAR, 0, (LPARAM)exp.GetBuffer());
		exp.ReleaseBuffer();
	}

}
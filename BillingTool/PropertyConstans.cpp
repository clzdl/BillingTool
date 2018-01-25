
#include "stdafx.h"
#include <map>
#include "PubFunc.h"
#include "BillingTool.h"
#include "PropertiesWnd.h"

void cbTestPhoneChg(CPropertiesWnd *propWnd, std::map<CString, PropertyInfo> &modProp, CString newValue);


std::map<int, std::map<CString, PropertyInfo> > gProperties = {
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
	},

	{ _credit_dispatch/*信控分发属性*/,
		{
			{ _TEXT("触发停机服务地址"),
				{ _TEXT("/creditTrigger"),nullptr, FALSE, }
			},
			{ _TEXT("话单费用"),
				{ _TEXT("1000"),nullptr ,FALSE , }
			},
			{ _TEXT("话单使用量"),
				{ _TEXT("10"),nullptr ,FALSE , }
			},
			{ _TEXT("截止本条话单前的总是用量"),
				{ _TEXT("100"),nullptr ,FALSE , }
			},
			{ _TEXT("用户总的基础量"),
				{ _TEXT("200"),nullptr , FALSE , }
			},
			{ _TEXT("信控分发文件入口"),
				{ _TEXT("/home/chengl/src/soCreditDispatch/data/in"),nullptr , FALSE , }
			}
		}
	} ,

	{ _bef_adjust/*帐前调账*/,
		{
			{ _TEXT("调账金额/比例"),
				{ _TEXT("1000"),nullptr , FALSE , }
			},
			{ _TEXT("账目编码"),
				{ _TEXT("110000"),nullptr , FALSE , }
			},
			{ _TEXT("生效标识"),
				{ _TEXT("立即生效"),nullptr , TRUE ,{
													{ _TEXT("立即生效"),_TEXT("0") } ,
													{ _TEXT("月末生效"),_TEXT("1") }
												}
				}
			}
		}
	},
	{ _aft_adjust/*帐后调账*/,
		{
			{ _TEXT("账单ID"),
				{ _TEXT("1111111000"),nullptr , FALSE , }
			},
			{ _TEXT("调账金额/比例"),
				{ _TEXT("1000"),nullptr , FALSE , }
			},
			{ _TEXT("账目编码"),
				{ _TEXT("110000"),nullptr , FALSE , }
			},
			{ _TEXT("账单费用"),
				{ _TEXT("10000"),nullptr , FALSE , }
			},
			{ _TEXT("账单余额"),
				{ _TEXT("100"),nullptr , FALSE , }
			},
			{ _TEXT("调减余额处理方式"),
				{ _TEXT("作废"),nullptr , TRUE ,{
												{ _TEXT("作废"),_TEXT("1") },
												{ _TEXT("转赠款"),_TEXT("2") }
											}
				}
			}
		}
	},
	{ _prefee_restore /*预存返还*/,
		{
			{ _TEXT("活动ID"),
				{ _TEXT("1111111000"),nullptr , FALSE , }
			},
			{ _TEXT("规则类型"),
				{ _TEXT("均分"),nullptr , TRUE ,{
													{ _TEXT("均分"),_TEXT("0") },
													{ _TEXT("自定义"),_TEXT("1") }
												}
				}
			},
			{ _TEXT("自定义规则ID"),
				{ _TEXT("1101111000"),nullptr , FALSE , }
			},
			{ _TEXT("返还费用"),
				{ _TEXT("10000"),nullptr , FALSE , }
			},
			{ _TEXT("返还周期"),
				{ _TEXT("按天"),nullptr , TRUE ,{
													{ _TEXT("按天"),_TEXT("0") },
													{ _TEXT("按自然甜"),_TEXT("1") },
													{ _TEXT("按月"),_TEXT("2") },
													{ _TEXT("按自然月"),_TEXT("3") }
												}
				}
			},
			{ _TEXT("校验规则"),
				{ _TEXT("不校验强制返费"),nullptr , TRUE ,{
														{ _TEXT("不校验强制返费"),_TEXT("0") },
														{ _TEXT("校验不通过废弃"),_TEXT("1") },
														{ _TEXT("校验不通过顺延"),_TEXT("2") }
													}
				}
			},
			{ _TEXT("预存返还账本"),
				{ _TEXT("2111111010130"),nullptr , FALSE , }
			}
		}
	},
	{ _credit_degree /*信用度评估、生失效*/,
		{
			{ _TEXT("VIP-CLASS"),
				{ _TEXT("10"),nullptr , FALSE , }
			},
			{ _TEXT("信用度值"),
				{ _TEXT("1000"),nullptr , FALSE , }
			},
			{ _TEXT("信用度等级"),
				{ _TEXT("A"),nullptr , FALSE , }
			}
		}
	},
	{ _predeal/*预处理*/,
		{
			{ _TEXT("对端号码"),
				{ _TEXT("18731173110"),nullptr , FALSE , }
			},
			{ _TEXT("SESSIONID"),
				{ _TEXT("Eadfkjla234"),nullptr , FALSE , }
			},
			{ _TEXT("文件入口"),
				{ _TEXT("/home/chengl/src/soPredealBin/data/in"),nullptr , FALSE , }
			},

			{ _TEXT("流量话单类型"),
				{ _TEXT("首单"),nullptr , TRUE ,{
													{ _TEXT("首单"),_TEXT("0") },
													{ _TEXT("中间单"),_TEXT("1") },
													{ _TEXT("尾单"),_TEXT("-1") },
												}
				}
			}
		}
	},
	{ _sms_send/*短信发送*/,
		{
			{ _TEXT("文件入口"),
				{ _TEXT("/home/chengl/src/soPeriodSmsProcess/data/in"),nullptr , FALSE , }
			},
			{ _TEXT("HASTEN_POLICY_ID"),
				{ _TEXT("40000036"),nullptr , FALSE , }
			},
			{ _TEXT("LEAVE_REAL_FEE"),
				{ _TEXT("1000"),nullptr , FALSE , }
			},
			{ _TEXT("REAL_FEE"),
				{ _TEXT("2000"),nullptr , FALSE , }
			},
			{ _TEXT("CREDIT_VALUE"),
				{ _TEXT("3000"),nullptr , FALSE , }
			}
		}
	}
};


void cbTestPhoneChg(CPropertiesWnd *propWnd, std::map<CString, PropertyInfo> &modProp, CString newValue)
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

		otlStm << CStringToString(newValue, CP_ACP).c_str();

		otlStm >> strUserId >> strAcctId >> strCustId;

		modProp.at(_TEXT("账户ID")).propertyValue = StringToCString(strAcctId, CP_ACP);
		modProp.at(_TEXT("用户ID")).propertyValue = StringToCString(strUserId, CP_ACP);
		modProp.at(_TEXT("客户ID")).propertyValue = StringToCString(strCustId, CP_ACP);
	}
	catch (otl_exception &e)
	{
		char strExp[4096] = { 0 };
		sprintf_s(strExp, "code:%d,msg:%s,var_info:%s,stm_text:%s\n", e.code, e.msg, e.var_info, e.stm_text);
		CString exp = StringToCString(strExp, CP_ACP);
		theApp.GetMainWnd()->SendMessage(MSG_WRITE_MSG2_STATUSBAR, 0, (LPARAM)exp.GetBuffer());
		exp.ReleaseBuffer();
	}



	propWnd->OnCbnSelChanged();
}

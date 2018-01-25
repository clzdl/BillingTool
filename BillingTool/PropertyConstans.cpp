
#include "stdafx.h"
#include <map>
#include "PubFunc.h"
#include "BillingTool.h"
#include "PropertiesWnd.h"

void cbTestPhoneChg(CPropertiesWnd *propWnd, std::map<CString, PropertyInfo> &modProp, CString newValue);


std::map<int, std::map<CString, PropertyInfo> > gProperties = {
	{ _common /*��������*/,
		{
			{ _TEXT("IP��ַ"),
				{ _TEXT("192.168.88.150"),nullptr,FALSE, }
			},
			{ _TEXT("�˿ں�"),
				{ _TEXT("4444"),nullptr,FALSE, }
			},
			{ _TEXT("���Ժ���"),
				{ _TEXT("17001818555"),cbTestPhoneChg,FALSE, }
			},
			{ _TEXT("�˻�ID"),
				{ _TEXT("320150105718968"),nullptr , FALSE, }
			},
			{ _TEXT("�û�ID"),
				{ _TEXT("120150105199770"),nullptr , FALSE , }
			},
			{ _TEXT("�û�IMSI"),
				{ _TEXT("4600121321301023010"),nullptr , FALSE , }
			},
			{ _TEXT("�û�IMEI"),
				{ _TEXT("4600121321301023010"),nullptr , FALSE , }
			},
			{ _TEXT("�û�������"),
				{ _TEXT("311"),nullptr , FALSE , }
			},
			{ _TEXT("�ͻ�ID"),
				{ _TEXT("220150105192242"),nullptr , FALSE , }
			},
			{ _TEXT("���ݿ����Ӵ�"),
				{ _TEXT("cmcc/CMCC@fxzn"),nullptr, FALSE , }
			},
			{ _TEXT("�û���"),
				{ _TEXT("chengl"),nullptr, FALSE , }
			},
			{ _TEXT("����"),
				{ _TEXT("chengl123"),nullptr , FALSE , }
			}
		}
	},

	{ _credit_dispatch/*�ſطַ�����*/,
		{
			{ _TEXT("����ͣ�������ַ"),
				{ _TEXT("/creditTrigger"),nullptr, FALSE, }
			},
			{ _TEXT("��������"),
				{ _TEXT("1000"),nullptr ,FALSE , }
			},
			{ _TEXT("����ʹ����"),
				{ _TEXT("10"),nullptr ,FALSE , }
			},
			{ _TEXT("��ֹ��������ǰ����������"),
				{ _TEXT("100"),nullptr ,FALSE , }
			},
			{ _TEXT("�û��ܵĻ�����"),
				{ _TEXT("200"),nullptr , FALSE , }
			},
			{ _TEXT("�ſطַ��ļ����"),
				{ _TEXT("/home/chengl/src/soCreditDispatch/data/in"),nullptr , FALSE , }
			}
		}
	} ,

	{ _bef_adjust/*��ǰ����*/,
		{
			{ _TEXT("���˽��/����"),
				{ _TEXT("1000"),nullptr , FALSE , }
			},
			{ _TEXT("��Ŀ����"),
				{ _TEXT("110000"),nullptr , FALSE , }
			},
			{ _TEXT("��Ч��ʶ"),
				{ _TEXT("������Ч"),nullptr , TRUE ,{
													{ _TEXT("������Ч"),_TEXT("0") } ,
													{ _TEXT("��ĩ��Ч"),_TEXT("1") }
												}
				}
			}
		}
	},
	{ _aft_adjust/*�ʺ����*/,
		{
			{ _TEXT("�˵�ID"),
				{ _TEXT("1111111000"),nullptr , FALSE , }
			},
			{ _TEXT("���˽��/����"),
				{ _TEXT("1000"),nullptr , FALSE , }
			},
			{ _TEXT("��Ŀ����"),
				{ _TEXT("110000"),nullptr , FALSE , }
			},
			{ _TEXT("�˵�����"),
				{ _TEXT("10000"),nullptr , FALSE , }
			},
			{ _TEXT("�˵����"),
				{ _TEXT("100"),nullptr , FALSE , }
			},
			{ _TEXT("��������ʽ"),
				{ _TEXT("����"),nullptr , TRUE ,{
												{ _TEXT("����"),_TEXT("1") },
												{ _TEXT("ת����"),_TEXT("2") }
											}
				}
			}
		}
	},
	{ _prefee_restore /*Ԥ�淵��*/,
		{
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
		}
	},
	{ _credit_degree /*���ö���������ʧЧ*/,
		{
			{ _TEXT("VIP-CLASS"),
				{ _TEXT("10"),nullptr , FALSE , }
			},
			{ _TEXT("���ö�ֵ"),
				{ _TEXT("1000"),nullptr , FALSE , }
			},
			{ _TEXT("���öȵȼ�"),
				{ _TEXT("A"),nullptr , FALSE , }
			}
		}
	},
	{ _predeal/*Ԥ����*/,
		{
			{ _TEXT("�Զ˺���"),
				{ _TEXT("18731173110"),nullptr , FALSE , }
			},
			{ _TEXT("SESSIONID"),
				{ _TEXT("Eadfkjla234"),nullptr , FALSE , }
			},
			{ _TEXT("�ļ����"),
				{ _TEXT("/home/chengl/src/soPredealBin/data/in"),nullptr , FALSE , }
			},

			{ _TEXT("������������"),
				{ _TEXT("�׵�"),nullptr , TRUE ,{
													{ _TEXT("�׵�"),_TEXT("0") },
													{ _TEXT("�м䵥"),_TEXT("1") },
													{ _TEXT("β��"),_TEXT("-1") },
												}
				}
			}
		}
	},
	{ _sms_send/*���ŷ���*/,
		{
			{ _TEXT("�ļ����"),
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
		text.Format(_TEXT("���ݿ�δ����"));
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

		modProp.at(_TEXT("�˻�ID")).propertyValue = StringToCString(strAcctId, CP_ACP);
		modProp.at(_TEXT("�û�ID")).propertyValue = StringToCString(strUserId, CP_ACP);
		modProp.at(_TEXT("�ͻ�ID")).propertyValue = StringToCString(strCustId, CP_ACP);
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

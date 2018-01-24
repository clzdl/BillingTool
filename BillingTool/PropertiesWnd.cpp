#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "BillingTool.h"
#include <map>
#include "PubFunc.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
static void cbTestPhoneChg(CPropertiesWnd *propWnd,std::map<CString, PropertyInfo> &modProp, CString newValue)
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

	char strUserId[30] = { 0 }, strAcctId[30] = { 0 }, strCustId[30] = {0};
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

		modProp.at(_TEXT("账户ID")).propertyValue = StringToCString(strAcctId,CP_ACP);
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

// CResourceViewBar
std::map<int , std::map<CString, PropertyInfo> > gProperties = {
	{ 0/*公共属性*/,	
			{ 
				{ _TEXT("IP地址"),
					{_TEXT("192.168.88.150"),nullptr,FALSE, } 
				},
				{ _TEXT("端口号"),
					{_TEXT("4444"),nullptr,FALSE, } 
				},
				{ _TEXT("测试号码"),
					{_TEXT("17001818555"),cbTestPhoneChg,FALSE, } 
				},
				{ _TEXT("账户ID"),
					{_TEXT("320150105718968"),nullptr , FALSE,  } 
				},
				{ _TEXT("用户ID"),
					{_TEXT("120150105199770"),nullptr , FALSE ,  } 
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
					{_TEXT("cmcc/CMCC@fxzn"),nullptr, FALSE ,  } 
				},
				{ _TEXT("用户名"),
					{_TEXT("chengl"),nullptr, FALSE , } 
				},
				{ _TEXT("密码"),
					{_TEXT("chengl123"),nullptr , FALSE ,  } 
				}
			} 
	},

	{ 1/*信控分发属性*/,
			{ 
				{ _TEXT("触发停机服务地址"), 
					{ _TEXT("/creditTrigger"),nullptr, FALSE, } 
				},
				{ _TEXT("话单费用"), 
					{_TEXT("1000"),nullptr ,FALSE , } 
				},
				{ _TEXT("话单使用量"), 
					{_TEXT("10"),nullptr ,FALSE , } 
				},
				{ _TEXT("截止本条话单前的总是用量"), 
					{_TEXT("100"),nullptr ,FALSE , } 
				},
				{ _TEXT("用户总的基础量"), 
					{_TEXT("200"),nullptr , FALSE , } 
				},
				{ _TEXT("信控分发文件入口"), 
					{_TEXT("/home/chengl/src/soCreditDispatch/data/in"),nullptr , FALSE , } 
				}
			} 
	} ,

	{ 2/*帐前调账*/,
		{
			{ _TEXT("调账金额/比例"),
				{_TEXT("1000"),nullptr , FALSE , } 
			},
			{ _TEXT("账目编码"),
				{_TEXT("110000"),nullptr , FALSE , } 
			},
			{ _TEXT("生效标识"),
				{_TEXT("立即生效"),nullptr , TRUE , {
														{_TEXT("立即生效"),_TEXT("0")} ,
														{ _TEXT("月末生效"),_TEXT("1") } 
													}
				}
			}
		}
	},
	{ 3/*帐后调账*/,
		{
			{ _TEXT("账单ID"),
				{_TEXT("1111111000"),nullptr , FALSE , } 
			},
			{ _TEXT("调账金额/比例"),
				{_TEXT("1000"),nullptr , FALSE , } 
			},
			{ _TEXT("账目编码"),	
				{_TEXT("110000"),nullptr , FALSE , } 
			},
			{ _TEXT("账单费用"),
				{_TEXT("10000"),nullptr , FALSE ,} 
			},
			{ _TEXT("账单余额"),
				{_TEXT("100"),nullptr , FALSE ,  } 
			},
			{ _TEXT("调减余额处理方式"),
				{_TEXT("作废"),nullptr , TRUE , { 
												{_TEXT("作废"),_TEXT("1")},
												{ _TEXT("转赠款"),_TEXT("2") }
											}
				}
			}
		}
	},
	{ 4/*预存返还*/,
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
	{ 5/*信用度评估、生失效*/,
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
	{ 6/*预处理*/,
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
				{ _TEXT("首单"),nullptr , TRUE , {
													{ _TEXT("首单"),_TEXT("0") },
													{ _TEXT("中间单"),_TEXT("1") },
													{ _TEXT("尾单"),_TEXT("-1") },
												}
				}
			}
		}
	},
	{ 7/*短信发送*/,
		{
			{ _TEXT("文件入口"),
				{ _TEXT("/home/chengl/src/soPeriodSmsProcess/data/in"),nullptr , FALSE , }
			}
		}
	}
};

CPropertiesWnd::CPropertiesWnd()
{
	m_nComboHeight = 0;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_CBN_SELCHANGE(1 , OnCbnSelChanged)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight , rectClient.Width(), rectClient.Height() -(m_nComboHeight), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建组合: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("未能创建属性组合 \n");
		return -1;      // 未能创建
	}
	int idx = 0;
	idx = m_wndObjectCombo.AddString(_T("公共属性"));
	m_wndObjectCombo.SetItemData(idx, 0);
	idx = m_wndObjectCombo.AddString(_T("信控分发"));
	m_wndObjectCombo.SetItemData(idx, 1);
	idx = m_wndObjectCombo.AddString(_T("帐前调账"));
	m_wndObjectCombo.SetItemData(idx, 2);
	idx = m_wndObjectCombo.AddString(_T("帐后调账"));
	m_wndObjectCombo.SetItemData(idx, 3);
	idx = m_wndObjectCombo.AddString(_T("预存返还"));
	m_wndObjectCombo.SetItemData(idx, 4);
	idx = m_wndObjectCombo.AddString(_T("信用度评估及生失效"));
	m_wndObjectCombo.SetItemData(idx, 5);
	idx = m_wndObjectCombo.AddString(_T("预处理"));
	m_wndObjectCombo.SetItemData(idx, 6);
	idx = m_wndObjectCombo.AddString(_T("短信发送"));
	m_wndObjectCombo.SetItemData(idx, 7);

	m_wndObjectCombo.SetCurSel(1);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect (&rectCombo);

	m_nComboHeight = rectCombo.Height();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	InitCommonPropList();

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnCbnSelChanged()
{
	DWORD_PTR val =  m_wndObjectCombo.GetItemData(m_wndObjectCombo.GetCurSel());
	m_wndPropList.RemoveAll();
	switch (val)
	{
	case 0://公共属性
		return InitCommonPropList();
	case 1://信控分发属性
		return InitCreditDispatchPropList();
	case 2://帐前调账
		return InitAdjustPropList();
	case 3://账后调账
		return InitAftAdjustPropList();
	case 4://预存返还
		return InitPrefeeRestorePropList();
	case 5://信用度评估
		return InitCreditDegreePropList();
	case 6://预处理
		return InitPredealPropList();
	case 7://短信发送
		return InitSmsSendPropList();
	}

}

CMFCPropertyGridProperty* CPropertiesWnd::BuildPropertyGridGroup(CString groupName, UINT module)
{
	CMFCPropertyGridProperty *pCreditDispatchGroup = new CMFCPropertyGridProperty(groupName);
	CMFCPropertyGridProperty *pProp = nullptr;
	for (auto comm : gProperties.at(module))
	{
		pProp = new CMFCPropertyGridProperty(comm.first, comm.second.propertyValue, comm.first);

		if (comm.second.isCombox)
		{
			for (auto it : comm.second.comboxValRel)
			{
				pProp->AddOption(it.first);
			}
			pProp->AllowEdit(FALSE);
		}

		pCreditDispatchGroup->AddSubItem(pProp);
	}

	return pCreditDispatchGroup;
}

void CPropertiesWnd::InitCommonPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_T("公共属性"),0));
	
}


void CPropertiesWnd::InitCreditDispatchPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	
	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("信控分发属性"),1));

}

void CPropertiesWnd::InitAdjustPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("帐前调账属性"), 2));
}

void CPropertiesWnd::InitAftAdjustPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("账后调账属性"), 3));
}

void CPropertiesWnd::InitPrefeeRestorePropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("预存返还属性"), 4));
}

void CPropertiesWnd::InitCreditDegreePropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("信用度评估及生失效"), 5));
}


void CPropertiesWnd::InitPredealPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("预处理"), 6));
}

void CPropertiesWnd::InitSmsSendPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("短信发送"), 7));
}


void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}


LRESULT CPropertiesWnd::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*)lParam;
	std::map<CString, PropertyInfo> &properties = gProperties.at(m_wndObjectCombo.GetItemData(m_wndObjectCombo.GetCurSel()));
	properties[pProp->GetName()].propertyValue = pProp->GetValue();
	PropertyInfo &tmpProp = properties[pProp->GetName()];
	if (tmpProp.callBack != nullptr)
	{
		tmpProp.callBack(this,properties,pProp->GetValue());
	}
	


	return 0;
}

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
		text.Format(_TEXT("���ݿ�δ����"));
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

		modProp.at(_TEXT("�˻�ID")).propertyValue = StringToCString(strAcctId,CP_ACP);
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

// CResourceViewBar
std::map<int , std::map<CString, PropertyInfo> > gProperties = {
	{ 0/*��������*/,	
			{ 
				{ _TEXT("IP��ַ"),
					{_TEXT("192.168.88.150"),nullptr,FALSE, } 
				},
				{ _TEXT("�˿ں�"),
					{_TEXT("4444"),nullptr,FALSE, } 
				},
				{ _TEXT("���Ժ���"),
					{_TEXT("17001818555"),cbTestPhoneChg,FALSE, } 
				},
				{ _TEXT("�˻�ID"),
					{_TEXT("320150105718968"),nullptr , FALSE,  } 
				},
				{ _TEXT("�û�ID"),
					{_TEXT("120150105199770"),nullptr , FALSE ,  } 
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
					{_TEXT("cmcc/CMCC@fxzn"),nullptr, FALSE ,  } 
				},
				{ _TEXT("�û���"),
					{_TEXT("chengl"),nullptr, FALSE , } 
				},
				{ _TEXT("����"),
					{_TEXT("chengl123"),nullptr , FALSE ,  } 
				}
			} 
	},

	{ 1/*�ſطַ�����*/,
			{ 
				{ _TEXT("����ͣ�������ַ"), 
					{ _TEXT("/creditTrigger"),nullptr, FALSE, } 
				},
				{ _TEXT("��������"), 
					{_TEXT("1000"),nullptr ,FALSE , } 
				},
				{ _TEXT("����ʹ����"), 
					{_TEXT("10"),nullptr ,FALSE , } 
				},
				{ _TEXT("��ֹ��������ǰ����������"), 
					{_TEXT("100"),nullptr ,FALSE , } 
				},
				{ _TEXT("�û��ܵĻ�����"), 
					{_TEXT("200"),nullptr , FALSE , } 
				},
				{ _TEXT("�ſطַ��ļ����"), 
					{_TEXT("/home/chengl/src/soCreditDispatch/data/in"),nullptr , FALSE , } 
				}
			} 
	} ,

	{ 2/*��ǰ����*/,
		{
			{ _TEXT("���˽��/����"),
				{_TEXT("1000"),nullptr , FALSE , } 
			},
			{ _TEXT("��Ŀ����"),
				{_TEXT("110000"),nullptr , FALSE , } 
			},
			{ _TEXT("��Ч��ʶ"),
				{_TEXT("������Ч"),nullptr , TRUE , {
														{_TEXT("������Ч"),_TEXT("0")} ,
														{ _TEXT("��ĩ��Ч"),_TEXT("1") } 
													}
				}
			}
		}
	},
	{ 3/*�ʺ����*/,
		{
			{ _TEXT("�˵�ID"),
				{_TEXT("1111111000"),nullptr , FALSE , } 
			},
			{ _TEXT("���˽��/����"),
				{_TEXT("1000"),nullptr , FALSE , } 
			},
			{ _TEXT("��Ŀ����"),	
				{_TEXT("110000"),nullptr , FALSE , } 
			},
			{ _TEXT("�˵�����"),
				{_TEXT("10000"),nullptr , FALSE ,} 
			},
			{ _TEXT("�˵����"),
				{_TEXT("100"),nullptr , FALSE ,  } 
			},
			{ _TEXT("��������ʽ"),
				{_TEXT("����"),nullptr , TRUE , { 
												{_TEXT("����"),_TEXT("1")},
												{ _TEXT("ת����"),_TEXT("2") }
											}
				}
			}
		}
	},
	{ 4/*Ԥ�淵��*/,
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
	{ 5/*���ö���������ʧЧ*/,
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
	{ 6/*Ԥ����*/,
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
				{ _TEXT("�׵�"),nullptr , TRUE , {
													{ _TEXT("�׵�"),_TEXT("0") },
													{ _TEXT("�м䵥"),_TEXT("1") },
													{ _TEXT("β��"),_TEXT("-1") },
												}
				}
			}
		}
	},
	{ 7/*���ŷ���*/,
		{
			{ _TEXT("�ļ����"),
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
// CResourceViewBar ��Ϣ�������

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

	// �������: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("δ�ܴ���������� \n");
		return -1;      // δ�ܴ���
	}
	int idx = 0;
	idx = m_wndObjectCombo.AddString(_T("��������"));
	m_wndObjectCombo.SetItemData(idx, 0);
	idx = m_wndObjectCombo.AddString(_T("�ſطַ�"));
	m_wndObjectCombo.SetItemData(idx, 1);
	idx = m_wndObjectCombo.AddString(_T("��ǰ����"));
	m_wndObjectCombo.SetItemData(idx, 2);
	idx = m_wndObjectCombo.AddString(_T("�ʺ����"));
	m_wndObjectCombo.SetItemData(idx, 3);
	idx = m_wndObjectCombo.AddString(_T("Ԥ�淵��"));
	m_wndObjectCombo.SetItemData(idx, 4);
	idx = m_wndObjectCombo.AddString(_T("���ö���������ʧЧ"));
	m_wndObjectCombo.SetItemData(idx, 5);
	idx = m_wndObjectCombo.AddString(_T("Ԥ����"));
	m_wndObjectCombo.SetItemData(idx, 6);
	idx = m_wndObjectCombo.AddString(_T("���ŷ���"));
	m_wndObjectCombo.SetItemData(idx, 7);

	m_wndObjectCombo.SetCurSel(1);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect (&rectCombo);

	m_nComboHeight = rectCombo.Height();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("δ�ܴ�����������\n");
		return -1;      // δ�ܴ���
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
	case 0://��������
		return InitCommonPropList();
	case 1://�ſطַ�����
		return InitCreditDispatchPropList();
	case 2://��ǰ����
		return InitAdjustPropList();
	case 3://�˺����
		return InitAftAdjustPropList();
	case 4://Ԥ�淵��
		return InitPrefeeRestorePropList();
	case 5://���ö�����
		return InitCreditDegreePropList();
	case 6://Ԥ����
		return InitPredealPropList();
	case 7://���ŷ���
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

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_T("��������"),0));
	
}


void CPropertiesWnd::InitCreditDispatchPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	
	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("�ſطַ�����"),1));

}

void CPropertiesWnd::InitAdjustPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("��ǰ��������"), 2));
}

void CPropertiesWnd::InitAftAdjustPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("�˺��������"), 3));
}

void CPropertiesWnd::InitPrefeeRestorePropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("Ԥ�淵������"), 4));
}

void CPropertiesWnd::InitCreditDegreePropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("���ö���������ʧЧ"), 5));
}


void CPropertiesWnd::InitPredealPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("Ԥ����"), 6));
}

void CPropertiesWnd::InitSmsSendPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("���ŷ���"), 7));
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

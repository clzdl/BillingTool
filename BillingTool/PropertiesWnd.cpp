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

static CString GetRigistryKey(DWORD module, CString name)
{
	CString key;
	key.Format(_TEXT("module-%d-%s"), module, name);

	return key;
}

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
	m_wndObjectCombo.InsertString(idx,_T("公共属性"));
	m_wndObjectCombo.SetItemData(idx++, _common);

	m_wndObjectCombo.InsertString(idx,_T("信控分发"));
	m_wndObjectCombo.SetItemData(idx++, _credit_dispatch);

	m_wndObjectCombo.InsertString(idx,_T("帐前调账"));
	m_wndObjectCombo.SetItemData(idx++, _bef_adjust);

	m_wndObjectCombo.InsertString(idx,_T("帐后调账"));
	m_wndObjectCombo.SetItemData(idx++, _aft_adjust);

	m_wndObjectCombo.InsertString(idx,_T("预存返还"));
	m_wndObjectCombo.SetItemData(idx++, _prefee_restore);

	m_wndObjectCombo.InsertString(idx,_T("信用度评估及生失效"));
	m_wndObjectCombo.SetItemData(idx++, _credit_degree);

	m_wndObjectCombo.InsertString(idx,_T("预处理"));
	m_wndObjectCombo.SetItemData(idx++, _predeal);

	m_wndObjectCombo.InsertString(idx,_T("短信发送"));
	m_wndObjectCombo.SetItemData(idx++, _sms_send);

	m_wndObjectCombo.InsertString(idx, _T("二次批价"));
	m_wndObjectCombo.SetItemData(idx++, _sec_price);

	m_wndObjectCombo.InsertString(idx, _T("二次批价(结算)"));
	m_wndObjectCombo.SetItemData(idx++, _sett_sec_price);

	m_wndObjectCombo.InsertString(idx, _T("累账"));
	m_wndObjectCombo.SetItemData(idx++, _agg_bill);

	m_wndObjectCombo.InsertString(idx, _T("标批"));
	m_wndObjectCombo.SetItemData(idx++, _first_price);

	m_wndObjectCombo.SetCurSel(0);

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
	case _common://公共属性
		return InitCommonPropList();
	case _credit_dispatch://信控分发属性
		return InitCreditDispatchPropList();
	case _bef_adjust://帐前调账
		return InitAdjustPropList();
	case _aft_adjust://账后调账
		return InitAftAdjustPropList();
	case _prefee_restore://预存返还
		return InitPrefeeRestorePropList();
	case _credit_degree://信用度评估
		return InitCreditDegreePropList();
	case _predeal://预处理
		return InitPredealPropList();
	case _sms_send://短信发送
		return InitSmsSendPropList();
	case _sec_price://二次批价
		return InitSecPricePropList();
	case _sett_sec_price://结算二次批价
		return InitSettSecPricePropList();
	case _agg_bill://累账
		return InitAggBillPropList();
	case _first_price://标批
		return InitFirstPricePropList();

	}

}

CMFCPropertyGridProperty* CPropertiesWnd::BuildPropertyGridGroup(CString groupName, UINT module)
{
	CMFCPropertyGridProperty *pCreditDispatchGroup = new CMFCPropertyGridProperty(groupName);
	CMFCPropertyGridProperty *pProp = nullptr;
	CString value;
	for (auto comm : gProperties.at(module))
	{
		value = theApp.GetString(GetRigistryKey(module, comm.first), comm.second.propertyValue);
		
		pProp = new CMFCPropertyGridProperty(comm.first, value, comm.first);

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

void CPropertiesWnd::InitSecPricePropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("二次批价"), 8));
}

void CPropertiesWnd::InitSettSecPricePropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("二次批价(结算)"), 9));
}

void CPropertiesWnd::InitAggBillPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("累账"), 10));
}

void CPropertiesWnd::InitFirstPricePropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndPropList.AddProperty(BuildPropertyGridGroup(_TEXT("标批"), 11));
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
	CString newValue = pProp->GetValue();
	
	properties[pProp->GetName()].propertyValue = newValue;
	PropertyInfo &tmpProp = properties[pProp->GetName()];
	if (tmpProp.callBack != nullptr)
	{
		tmpProp.callBack(this,properties, newValue);
	}
	
	theApp.WriteString(GetRigistryKey(m_wndObjectCombo.GetItemData(m_wndObjectCombo.GetCurSel()), pProp->GetName()), newValue);

	return 0;
}

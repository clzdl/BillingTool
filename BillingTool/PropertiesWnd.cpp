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
	m_wndObjectCombo.SetItemData(idx++, 0);

	m_wndObjectCombo.InsertString(idx,_T("信控分发"));
	m_wndObjectCombo.SetItemData(idx++, 1);

	m_wndObjectCombo.InsertString(idx,_T("帐前调账"));
	m_wndObjectCombo.SetItemData(idx++, 2);

	m_wndObjectCombo.InsertString(idx,_T("帐后调账"));
	m_wndObjectCombo.SetItemData(idx++, 3);

	m_wndObjectCombo.InsertString(idx,_T("预存返还"));
	m_wndObjectCombo.SetItemData(idx++, 4);

	m_wndObjectCombo.InsertString(idx,_T("信用度评估及生失效"));
	m_wndObjectCombo.SetItemData(idx++, 5);

	m_wndObjectCombo.InsertString(idx,_T("预处理"));
	m_wndObjectCombo.SetItemData(idx++, 6);

	m_wndObjectCombo.InsertString(idx,_T("短信发送"));
	m_wndObjectCombo.SetItemData(idx++, 7);

	m_wndObjectCombo.InsertString(idx, _T("二次批价"));
	m_wndObjectCombo.SetItemData(idx++, 8);
	m_wndObjectCombo.InsertString(idx, _T("二次批价(结算)"));
	m_wndObjectCombo.SetItemData(idx++, 9);


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
	case 8://二次批价
		return InitSecPricePropList();
	case 9://结算二次批价
		return InitSettSecPricePropList();

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

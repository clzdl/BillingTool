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

	char strUserId[30] = {0}, strAcctId[30] = { 0 };
	try {
		std::string sql = "select to_char(t1.user_id), to_char(t2.acct_id) "
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

		otlStm >> strUserId >> strAcctId;

		modProp.at(_TEXT("�˻�ID")).propertyValue = StringToCString(strAcctId,CP_ACP);
		modProp.at(_TEXT("�û�ID")).propertyValue = StringToCString(strUserId, CP_ACP);
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
				{_TEXT("IP��ַ"),{_TEXT("192.168.88.150"),nullptr} },
				{ _TEXT("�˿ں�"),{_TEXT("4444"),nullptr} },
				{ _TEXT("���Ժ���"),{_TEXT("17001818555"),cbTestPhoneChg } },
				{ _TEXT("�˻�ID"),{_TEXT("320150105718968"),nullptr} },
				{ _TEXT("�û�ID"),{_TEXT("120150105199770"),nullptr} },
				{ _TEXT("���ݿ����Ӵ�"),{_TEXT("cmcc/CMCC@fxzn"),nullptr} },
				{ _TEXT("�û���"),{_TEXT("chengl"),nullptr} },
				{ _TEXT("����"),{_TEXT("chengl123"),nullptr} }
				
			} 
	},

	{ 1/*�ſطַ�����*/,
			{ 
				{ _TEXT("����ͣ�������ַ"),{_TEXT("/creditTrigger"),nullptr} },
				{ _TEXT("��������"), {_TEXT("1000"),nullptr} },
				{ _TEXT("����ʹ����"), {_TEXT("10"),nullptr} },
				{ _TEXT("��ֹ��������ǰ����������"), {_TEXT("100"),nullptr} },
				{ _TEXT("�û��ܵĻ�����"), {_TEXT("200"),nullptr} },
				{ _TEXT("�ſطַ��ļ����"), {_TEXT("/home/chengl/src/soCreditDispatch/data/in"),nullptr} },
			} 
	} ,
	{ 2/*��ǰ����*/,
		{
			{ _TEXT("���˽��/����"),{_TEXT("1000"),nullptr} },
			{ _TEXT("��Ŀ����"),{_TEXT("110000"),nullptr} },
			{ _TEXT("��Ч��ʶ"),{_TEXT("0"),nullptr} }
		}
	},
	{ 3/*�ʺ����*/,
		{
			{ _TEXT("�˵�ID"),{_TEXT("1111111000"),nullptr} },
			{ _TEXT("���˽��/����"),{_TEXT("1000"),nullptr} },
			{ _TEXT("��Ŀ����"),{_TEXT("110000"),nullptr} },
			{ _TEXT("�˵�����"),{_TEXT("10000"),nullptr} },
			{ _TEXT("�˵����"),{_TEXT("100"),nullptr} },
			{ _TEXT("��������ʽ"),{_TEXT("0"),nullptr} }
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
	m_wndObjectCombo.SetCurSel(0);

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
	}

}


void CPropertiesWnd::InitCommonPropList()
{
	
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	CMFCPropertyGridProperty *pCommonGroup = new CMFCPropertyGridProperty(_T("��������"));
	for (auto comm : gProperties.at(0))
	{
		pCommonGroup->AddSubItem(new CMFCPropertyGridProperty(comm.first, comm.second.propertyValue, comm.first));
	
	}
	
	
	m_wndPropList.AddProperty(pCommonGroup);

	/*CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("�߿�"), _T("�Ի������"), _T("����֮һ: ���ޡ�����ϸ�������ɵ�����С���򡰶Ի������"));
	pProp->AddOption(_T("��"));
	pProp->AddOption(_T("ϸ"));
	pProp->AddOption(_T("�ɵ�����С"));
	pProp->AddOption(_T("�Ի������"));
	pProp->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("����"), (_variant_t) _T("����"), _T("ָ�����ڱ���������ʾ���ı�")));

	

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("���ڴ�С"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("�߶�"), (_variant_t) 250l, _T("ָ�����ڵĸ߶�"));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("���"), (_variant_t) 150l, _T("ָ�����ڵĿ��"));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("����"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	_tcscpy_s(lf.lfFaceName, _T("����, Arial"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("����"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("ָ�����ڵ�Ĭ������")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("ʹ��ϵͳ����"), (_variant_t) true, _T("ָ������ʹ�á�MS Shell Dlg������")));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("����"));
	pProp = new CMFCPropertyGridProperty(_T("(����)"), _T("Ӧ�ó���"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("������ɫ"), RGB(210, 192, 254), NULL, _T("ָ��Ĭ�ϵĴ�����ɫ"));
	pColorProp->EnableOtherButton(_T("����..."));
	pColorProp->EnableAutomaticButton(_T("Ĭ��"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	static const TCHAR szFilter[] = _T("ͼ���ļ�(*.ico)|*.ico|�����ļ�(*.*)|*.*||");
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("ͼ��"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("ָ������ͼ��")));

	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("�ļ���"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3);
	*/
}



void CPropertiesWnd::InitCreditDispatchPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty *pCreditDispatchGroup = new CMFCPropertyGridProperty(_T("�ſطַ�����"));
	for (auto comm : gProperties.at(1))
	{
		pCreditDispatchGroup->AddSubItem(new CMFCPropertyGridProperty(comm.first, comm.second.propertyValue, comm.first));

	}

	m_wndPropList.AddProperty(pCreditDispatchGroup);

}

void CPropertiesWnd::InitAdjustPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty *pCreditDispatchGroup = new CMFCPropertyGridProperty(_T("��ǰ��������"));
	for (auto comm : gProperties.at(2))
	{
		pCreditDispatchGroup->AddSubItem(new CMFCPropertyGridProperty(comm.first, comm.second.propertyValue, comm.first));

	}

	m_wndPropList.AddProperty(pCreditDispatchGroup);
}

void CPropertiesWnd::InitAftAdjustPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty *pCreditDispatchGroup = new CMFCPropertyGridProperty(_T("�˺��������"));
	for (auto comm : gProperties.at(3))
	{
		pCreditDispatchGroup->AddSubItem(new CMFCPropertyGridProperty(comm.first, comm.second.propertyValue, comm.first));

	}

	m_wndPropList.AddProperty(pCreditDispatchGroup);
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

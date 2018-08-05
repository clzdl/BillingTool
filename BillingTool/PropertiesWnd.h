
#pragma once



class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
// ����
public:
	CPropertiesWnd();

	void AdjustLayout();
	void Refresh(int propType);
// ����
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropGridCtrl.SetVSDotNetLook(bSet);
		m_wndPropGridCtrl.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	CMFCPropertyGridCtrl m_wndPropGridCtrl;

// ʵ��
public:
	virtual ~CPropertiesWnd();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	
	afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);

	
	DECLARE_MESSAGE_MAP()

	void InitCommonPropList();
	void InitCreditDispatchPropList();
	void InitAdjustPropList();
	void InitAftAdjustPropList();
	void InitPrefeeRestorePropList();
	void InitCreditDegreePropList();
	void InitPredealPropList();
	void InitSmsSendPropList();
	void InitSecPricePropList();
	void InitSettSecPricePropList();
	void InitAggBillPropList();
	void InitFirstPricePropList();
	void SetPropListFont();
	
	CMFCPropertyGridProperty* BuildPropertyGridGroup(CString groupName,UINT module);
};


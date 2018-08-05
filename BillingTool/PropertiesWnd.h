
#pragma once

#include "BillingTool.h"

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
// 构造
public:
	CPropertiesWnd();

	void AdjustLayout();
	void Refresh(ModuleType propType);
// 特性
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropGridCtrl.SetVSDotNetLook(bSet);
		m_wndPropGridCtrl.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	CMFCPropertyGridCtrl m_wndPropGridCtrl;

// 实现
public:
	virtual ~CPropertiesWnd();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	
	afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);

	
	DECLARE_MESSAGE_MAP()

	void SetPropListFont();
	void BuildPropertyList(ModuleType moduleType);
	
	CMFCPropertyGridProperty* BuildPropertyGridGroup(CString groupName,UINT module);

	ModuleType m_specModuleType;
};


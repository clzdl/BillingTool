#pragma once
#include "ViewTree.h"

class CCModuleViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CModuleView : public CDockablePane
{
// 构造
public:
	CModuleView();

	void AdjustLayout();
	void OnChangeVisualStyle();
	static void ConnectDb(ModuleContext *ctx , void *ptr);

// 特性
protected:

	CViewTree m_wndModuleView;
	CImageList m_moduleViewImages;
	CCModuleViewToolBar m_wndToolBar;

protected:
	void InitializeModules();
	void InitializeCommonModule();

// 实现
public:
	virtual ~CModuleView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnWndFileTreeViewClick(NMHDR *pNMHDR, LRESULT *pResult);
	
	DECLARE_MESSAGE_MAP()
};


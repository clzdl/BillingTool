
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

#include "ModuleView.h"
#include "PropertiesWnd.h"
class CMainFrame : public CFrameWndEx
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:
	void WriteString2StatusBar(CString str);
// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCStatusBar     m_wndStatusBar;
	CModuleView         m_wndModuleView;
	CPropertiesWnd    m_wndProperties;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnViewModule();
	afx_msg void OnUpdateViewModule(CCmdUI* pCmdUI);
	afx_msg void OnViewProperty();
	afx_msg void OnUpdateViewProperty(CCmdUI* pCmdUI);
	
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg LRESULT OnWriteMsg2StatusBar(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWriteMsg2ListView(WPARAM wParam, LPARAM lParam);


	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};



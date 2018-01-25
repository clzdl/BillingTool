
// BillingToolView.h : CBillingToolView 类的接口
//

#pragma once
#include <afxcview.h>
#include "BillingToolDoc.h"

class CBillingToolView : public CListView
{
protected: // 仅从序列化创建
	CBillingToolView();
	DECLARE_DYNCREATE(CBillingToolView)

// 特性
public:
	CBillingToolDoc* GetDocument() const;

// 操作
public:
	/*
		phone: 号码，
		scene: 场景
		result: 操作结果
	*/
	void AddResult2ListCtrl(CString phone, CString  scene, CString result);
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CBillingToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnEditClean();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()


public:
//	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // BillingToolView.cpp 中的调试版本
inline CBillingToolDoc* CBillingToolView::GetDocument() const
   { return reinterpret_cast<CBillingToolDoc*>(m_pDocument); }
#endif


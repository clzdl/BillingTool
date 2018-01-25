
// BillingToolView.h : CBillingToolView ��Ľӿ�
//

#pragma once
#include <afxcview.h>
#include "BillingToolDoc.h"

class CBillingToolView : public CListView
{
protected: // �������л�����
	CBillingToolView();
	DECLARE_DYNCREATE(CBillingToolView)

// ����
public:
	CBillingToolDoc* GetDocument() const;

// ����
public:
	/*
		phone: ���룬
		scene: ����
		result: �������
	*/
	void AddResult2ListCtrl(CString phone, CString  scene, CString result);
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CBillingToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // BillingToolView.cpp �еĵ��԰汾
inline CBillingToolDoc* CBillingToolView::GetDocument() const
   { return reinterpret_cast<CBillingToolDoc*>(m_pDocument); }
#endif


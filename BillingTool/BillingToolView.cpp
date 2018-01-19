
// BillingToolView.cpp : CBillingToolView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "BillingTool.h"
#endif

#include "BillingToolDoc.h"
#include "BillingToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBillingToolView

IMPLEMENT_DYNCREATE(CBillingToolView, CListView)

BEGIN_MESSAGE_MAP(CBillingToolView, CListView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBillingToolView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CBillingToolView ����/����

CBillingToolView::CBillingToolView()
{
	// TODO: �ڴ˴���ӹ������

}

CBillingToolView::~CBillingToolView()
{
}

BOOL CBillingToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CListView::PreCreateWindow(cs);
}

// CBillingToolView ����

void CBillingToolView::OnDraw(CDC* /*pDC*/)
{
	CBillingToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

}


// CBillingToolView ��ӡ


void CBillingToolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBillingToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CBillingToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CBillingToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CBillingToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBillingToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBillingToolView ���

#ifdef _DEBUG
void CBillingToolView::AssertValid() const
{
	CListView::AssertValid();
}

void CBillingToolView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CBillingToolDoc* CBillingToolView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBillingToolDoc)));
	return (CBillingToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CBillingToolView ��Ϣ�������

//void CBillingToolView::OnInitialUpdate()
//{
//	CListView::OnInitialUpdate();
//
//	
//}

int CBillingToolView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	GetListCtrl().ModifyStyle(0, LVS_REPORT| LVS_EX_FULLROWSELECT | LVS_SHOWSELALWAYS | LVS_SORTASCENDING);
	GetListCtrl().SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	GetListCtrl().InsertColumn(0, _TEXT("����"), LVCFMT_LEFT, 150);
	GetListCtrl().InsertColumn(1, _TEXT("����"), LVCFMT_LEFT, 150);
	GetListCtrl().InsertColumn(2, _TEXT("���"), LVCFMT_LEFT, 600);
	GetListCtrl().InsertColumn(2, _TEXT("ʱ��"), LVCFMT_LEFT, 150);
	
	return 0;
}

void CBillingToolView::AddResult2ListCtrl(CString phone, CString  scene, CString result)
{
	UINT itemCount = GetListCtrl().GetItemCount();
	int i = GetListCtrl().InsertItem(itemCount, _TEXT("111"));
	GetListCtrl().SetItemText(i, 0, phone.IsEmpty()?_TEXT("XXXXXXXXXXX"):phone);
	GetListCtrl().SetItemText(i, 1, scene);
	GetListCtrl().SetItemText(i, 2, result);
}

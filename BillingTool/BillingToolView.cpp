
// BillingToolView.cpp : CBillingToolView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBillingToolView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CBillingToolView 构造/析构

CBillingToolView::CBillingToolView()
{
	// TODO: 在此处添加构造代码

}

CBillingToolView::~CBillingToolView()
{
}

BOOL CBillingToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CListView::PreCreateWindow(cs);
}

// CBillingToolView 绘制

void CBillingToolView::OnDraw(CDC* /*pDC*/)
{
	CBillingToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

}


// CBillingToolView 打印


void CBillingToolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBillingToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CBillingToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CBillingToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CBillingToolView 诊断

#ifdef _DEBUG
void CBillingToolView::AssertValid() const
{
	CListView::AssertValid();
}

void CBillingToolView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CBillingToolDoc* CBillingToolView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBillingToolDoc)));
	return (CBillingToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CBillingToolView 消息处理程序

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

	// TODO:  在此添加您专用的创建代码
	GetListCtrl().ModifyStyle(0, LVS_REPORT| LVS_EX_FULLROWSELECT | LVS_SHOWSELALWAYS | LVS_SORTASCENDING);
	GetListCtrl().SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	GetListCtrl().InsertColumn(0, _TEXT("号码"), LVCFMT_LEFT, 150);
	GetListCtrl().InsertColumn(1, _TEXT("场景"), LVCFMT_LEFT, 150);
	GetListCtrl().InsertColumn(2, _TEXT("结果"), LVCFMT_LEFT, 600);
	GetListCtrl().InsertColumn(2, _TEXT("时间"), LVCFMT_LEFT, 150);
	
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

#include "stdafx.h"
#include "mainfrm.h"
#include "ModuleView.h"
#include "Resource.h"
#include "BillingTool.h"
#include "PluginInterface.h"
#include "BillingToolView.h"
#include "LoadingDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CModuleView::CModuleView()
{
}

CModuleView::~CModuleView()
{
}

BEGIN_MESSAGE_MAP(CModuleView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_NOTIFY(NM_DBLCLK, 4, OnWndFileTreeViewClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar 消息处理程序

int CModuleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndModuleView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("未能创建文件视图\n");
		return -1;      // 未能创建
	}

	// 加载视图图像: 
	m_moduleViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndModuleView.SetImageList(&m_moduleViewImages, TVSIL_NORMAL);
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	
	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由: 
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// 填入一些静态树视图数据(此处只需填入虚拟代码，而不是复杂的数据)
	InitializeCommonModule();
	InitializeModules();
	AdjustLayout();

	return 0;
}

void CModuleView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CModuleView::InitializeCommonModule()
{
	HTREEITEM hRoot = m_wndModuleView.InsertItem(_T("基础功能"), 0, 0);
	m_wndModuleView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM tmpItem = m_wndModuleView.InsertItem(_T("连接数据库"), 1, 2, hRoot);
	m_wndModuleView.SetItemData(tmpItem, DWORD_PTR(CModuleView::ConnectDb));



	m_wndModuleView.Expand(hRoot, TVE_EXPAND);
}
void CModuleView::InitializeModules()
{
	HINSTANCE lib = ::LoadLibrary(TEXT("./CreditDispatch.dll"));
	if (NULL == lib)
	{
		DWORD  err = GetLastError();
		MessageBox(_TEXT("LoadLibrary fail"));
		return;
	}
	((INIT_FUNC)GetProcAddress(lib, "Initilize"))(GetParent(),&m_wndModuleView);
}

void CModuleView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndModuleView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项: 
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CModuleView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndModuleView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}


void CModuleView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndModuleView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CModuleView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndModuleView.SetFocus();
}

void CModuleView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* 锁定*/);

	m_moduleViewImages.DeleteImageList();

	CBitmap bmp;
	if (!bmp.LoadBitmap(IDB_FILE_VIEW))
	{
		TRACE(_T("无法加载位图: %x\n"), IDB_FILE_VIEW);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_moduleViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_moduleViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndModuleView.SetImageList(&m_moduleViewImages, TVSIL_NORMAL);
}

bool ALongRightProcessProc(const CUPDUPDATA* pCUPDUPData)
{
	ITEM_FUNC ptrFunc = (ITEM_FUNC)pCUPDUPData->GetAppData();
	
	ptrFunc(gModuleContext, nullptr);

	return true;	// Return true to indicate everything has completed successfully
}

void CModuleView::OnWndFileTreeViewClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hCurItem = m_wndModuleView.GetSelectedItem();//获得当前选中ID  
	ITEM_FUNC func = (ITEM_FUNC)(m_wndModuleView.GetItemData(hCurItem));
	if (nullptr == func)
		return;
	LoadingDlg Dlg(AfxGetMainWnd()->GetSafeHwnd(), ALongRightProcessProc, func, _TEXT("请等待..."), false, true);
	// Use My custom dialog template
	Dlg.SetDialogTemplate(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDD_DLG_LOADING), NULL, IDC_PROGRESS_LOADING, NULL);
	Dlg.DoModal();
	
	*pResult = 0;
}



void CModuleView::ConnectDb(ModuleContext *ctx, void *ptr)
{
	ListViewData data(_TEXT("XXXXXXXXXXX") , _TEXT("基础功能"));
	data.m_result = _TEXT("连接数据库成功");
	if (SUCCESS != ctx->ConnectDb("billtest1/BILLTEST1@FXZN"))
	{
		data.m_result = _TEXT("连接数据库失败");
	}
	
	theApp.GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&data);

}


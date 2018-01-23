// CreditDispatch.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "CreditDispatch.h"
#include "../../BillingTool/PluginInterface.h"
#include "../../BillingTool/ViewTree.h"

#include "BusiFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#



//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CCreditDispatchApp

BEGIN_MESSAGE_MAP(CCreditDispatchApp, CWinApp)
END_MESSAGE_MAP()


// CCreditDispatchApp 构造

CCreditDispatchApp::CCreditDispatchApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CCreditDispatchApp 对象

//CCreditDispatchApp theApp;
// CCreditDispatchApp 初始化

BOOL CCreditDispatchApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


void Initilize(CWnd *mainWnd,CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	

	HTREEITEM hRoot = viewTree->InsertItem(_T("信控分发功能"), 0, 0);
	viewTree->SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("触发开机"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(BusiFunc::TriggerStartUp));
	
	tmpItem = viewTree->InsertItem(_T("触发停机【NET】"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(BusiFunc::TriggerStopByNet));

	tmpItem = viewTree->InsertItem(_T("触发停机【FILE】"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(BusiFunc::TriggerStopByFile));
	
	tmpItem = viewTree->InsertItem(_T("触发提醒【FILE】"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(BusiFunc::TriggerRemindByFile));

	viewTree->Expand(hRoot, TVE_EXPAND);
	
}
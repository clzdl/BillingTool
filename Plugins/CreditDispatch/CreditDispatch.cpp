// CreditDispatch.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "CreditDispatch.h"
#include "../../BillingTool/PluginInterface.h"
#include "../../BillingTool/ViewTree.h"
#include "../../BillingTool/BillingTool.h"
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


static std::map<CString, PropertyInfo> modulePropertys = {
	{ _TEXT("触发停机服务地址"),
		{ _TEXT("/creditTrigger"),nullptr, FALSE, }
	},
	{ _TEXT("话单费用"),
		{ _TEXT("1000"),nullptr ,FALSE , }
	},
	{ _TEXT("话单使用量"),
		{ _TEXT("10"),nullptr ,FALSE , }
	},
	{ _TEXT("截止本条话单前的总是用量"),
		{ _TEXT("100"),nullptr ,FALSE , }
	},
	{ _TEXT("用户总的基础量"),
		{ _TEXT("200"),nullptr , FALSE , }
	},
	{ _TEXT("信控分发文件入口"),
		{ _TEXT("/home/chengl/src/soCreditDispatch/data/in"),nullptr , FALSE , }
	}
};

void PropertyInitilize(std::map<int, std::map<CString, PropertyInfo> > &gProperty)
{
	gProperty.insert(std::make_pair(_credit_dispatch, modulePropertys));
}


static _ItemCallBackDef moduleCallBackDef[] = {
	{ _credit_dispatch, BusiFunc::TriggerStartUp },
	{ _credit_dispatch, BusiFunc::TriggerStopByNet },
	{ _credit_dispatch, BusiFunc::TriggerStopByFile },
	{ _credit_dispatch, BusiFunc::TriggerRemindByFile } };

void Initilize(CWnd *mainWnd,CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	

	HTREEITEM hRoot = viewTree->InsertItem(_T("信控分发"), 0, 0);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("触发开机"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[0])));
	
	tmpItem = viewTree->InsertItem(_T("触发停机【NET】"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[1])));

	tmpItem = viewTree->InsertItem(_T("触发停机【FILE】"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[2])));
	
	tmpItem = viewTree->InsertItem(_T("触发提醒【FILE】"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[3])));
	
}
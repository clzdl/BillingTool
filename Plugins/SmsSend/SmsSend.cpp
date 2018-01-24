// SmsSend.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "SmsSend.h"
#include "../../BillingTool/PluginInterface.h"
#include "../../BillingTool/ViewTree.h"
#include "../../BillingTool/ModuleContext.h"
#include "../../BillingTool/BillingTool.h"
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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

// CSmsSendApp

BEGIN_MESSAGE_MAP(CSmsSendApp, CWinApp)
END_MESSAGE_MAP()


// CSmsSendApp 构造

CSmsSendApp::CSmsSendApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CSmsSendApp 对象

//CSmsSendApp theApp;


// CSmsSendApp 初始化

BOOL CSmsSendApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

static CString GetSysYMDTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString result;
	result.Format(_TEXT("%04d%02d%02d"), st.wYear, st.wMonth, st.wDay);
	return result;
}

static std::string CStringToString(const CString& src, UINT codepage)
{
	std::string dst;
	if (src.IsEmpty())
	{
		dst.clear();
		return "";
	}

	int length = ::WideCharToMultiByte(codepage, 0, src, src.GetLength(), NULL, 0, NULL, NULL);
	dst.resize(length);
	::WideCharToMultiByte(codepage, 0, src, src.GetLength(), &dst[0], (int)dst.size(), NULL, NULL);

	return dst;
}

static CString StringToCString(const std::string& src, UINT codepage)
{
	CString dst;
	if (src.empty())
	{
		return  dst;
	}
	int length = ::MultiByteToWideChar(codepage, 0, src.data(), (int)src.size(), NULL, 0);
	WCHAR* pBuffer = dst.GetBufferSetLength(length);
	::MultiByteToWideChar(codepage, 0, src.data(), (int)src.size(), pBuffer, length);

	return dst;
}


void TriggerSmsSendFile(ModuleContext *ctx, void *ptr);


void Initilize(CWnd *mainWnd, CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	HTREEITEM hRoot = viewTree->InsertItem(_T("短信提醒"), 0, 0);
	viewTree->SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("生成短信文件"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerSmsSendFile));


}

std::vector<std::string> BuildSmsContents(CString serialNumber, CString userId)
{
	/*
	17001810501|120150105227073|1|";"=>"\n"|尊敬的分享通信客户，您好！;您2016年9月账单129.00元（总消费129.00元，优惠及减免0.00元），其中：;套餐及固定费：129.00元;-基本套餐费：129.00元;缴费请访问10039.cc
	*/
	std::vector<std::string> result;
	std::string content = CStringToString(serialNumber, CP_ACP);
	content += "|";
	content += CStringToString(serialNumber, CP_ACP);
	content += "|";
	content += CStringToString(_TEXT("1|\"; \"=>\"\\n\"|尊敬的分享通信客户，您好！;您2016年9月账单129.00元（总消费129.00元，优惠及减免0.00元），其中：;套餐及固定费：129.00元;-基本套餐费：129.00元;缴费请访问10039.cc"), CP_UTF8);
	result.push_back(content);
	return result;

}

void TriggerSmsSendFile(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("测试号码")), _TEXT("生成短信文件"));
	resultViewData.m_result = _TEXT("触发成功.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(0, _TEXT("IP地址")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(0, _TEXT("用户名")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(0, _TEXT("密码")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(0, _TEXT("测试号码"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(7, _TEXT("文件入口")), CP_ACP) + "/tmp_smsSendFile";
	CString csInFile = ctx->m_funcGetProperty(7, _TEXT("文件入口"))
							+ _TEXT("/smsSendFile") + GetSysYMDTime() + _TEXT(".dat");

	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("触发失败.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("触发失败.");
			break;
		}

		std::vector<std::string> contents = BuildSmsContents(testNumber, ctx->m_funcGetProperty(0, _TEXT("用户ID")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("触发失败.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("触发失败.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
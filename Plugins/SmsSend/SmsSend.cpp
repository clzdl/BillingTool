// SmsSend.cpp : ���� DLL �ĳ�ʼ�����̡�
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
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CSmsSendApp

BEGIN_MESSAGE_MAP(CSmsSendApp, CWinApp)
END_MESSAGE_MAP()


// CSmsSendApp ����

CSmsSendApp::CSmsSendApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CSmsSendApp ����

//CSmsSendApp theApp;


// CSmsSendApp ��ʼ��

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


	HTREEITEM hRoot = viewTree->InsertItem(_T("��������"), 0, 0);
	viewTree->SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("���ɶ����ļ�"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(TriggerSmsSendFile));


}

std::vector<std::string> BuildSmsContents(CString serialNumber, CString userId)
{
	/*
	17001810501|120150105227073|1|";"=>"\n"|�𾴵ķ���ͨ�ſͻ������ã�;��2016��9���˵�129.00Ԫ��������129.00Ԫ���Żݼ�����0.00Ԫ�������У�;�ײͼ��̶��ѣ�129.00Ԫ;-�����ײͷѣ�129.00Ԫ;�ɷ������10039.cc
	*/
	std::vector<std::string> result;
	std::string content = CStringToString(serialNumber, CP_ACP);
	content += "|";
	content += CStringToString(serialNumber, CP_ACP);
	content += "|";
	content += CStringToString(_TEXT("1|\"; \"=>\"\\n\"|�𾴵ķ���ͨ�ſͻ������ã�;��2016��9���˵�129.00Ԫ��������129.00Ԫ���Żݼ�����0.00Ԫ�������У�;�ײͼ��̶��ѣ�129.00Ԫ;-�����ײͷѣ�129.00Ԫ;�ɷ������10039.cc"), CP_UTF8);
	result.push_back(content);
	return result;

}

void TriggerSmsSendFile(ModuleContext *ctx, void *ptr)
{
	ListViewData resultViewData(ctx->m_funcGetProperty(0, _TEXT("���Ժ���")), _TEXT("���ɶ����ļ�"));
	resultViewData.m_result = _TEXT("�����ɹ�.");

	std::string hostName = CStringToString(ctx->m_funcGetProperty(0, _TEXT("IP��ַ")), CP_ACP);
	std::string userName = CStringToString(ctx->m_funcGetProperty(0, _TEXT("�û���")), CP_ACP);
	std::string userPwd = CStringToString(ctx->m_funcGetProperty(0, _TEXT("����")), CP_ACP);
	CString testNumber = ctx->m_funcGetProperty(0, _TEXT("���Ժ���"));
	std::string tmpInFile = CStringToString(ctx->m_funcGetProperty(7, _TEXT("�ļ����")), CP_ACP) + "/tmp_smsSendFile";
	CString csInFile = ctx->m_funcGetProperty(7, _TEXT("�ļ����"))
							+ _TEXT("/smsSendFile") + GetSysYMDTime() + _TEXT(".dat");

	std::string inFile = CStringToString(csInFile, CP_ACP);

	UINT port = 22;

	bool result = true;
	do {
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshConnectAndInit))(hostName, port, userName, userPwd);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}
		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("touch " + tmpInFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}

		std::vector<std::string> contents = BuildSmsContents(testNumber, ctx->m_funcGetProperty(0, _TEXT("�û�ID")));

		for (auto it : contents)
		{
			result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("echo '" + it + "' >>" + tmpInFile);
			if (!result)
			{
				resultViewData.m_result = _TEXT("����ʧ��.");
				break;
			}
		}

		result = (ctx->m_objSshCmdExecutor->*(ctx->m_funcSshExecuteCmd))("mv  " + tmpInFile + " " + inFile);
		if (!result)
		{
			resultViewData.m_result = _TEXT("����ʧ��.");
			break;
		}


	} while (false);
	(ctx->m_objSshCmdExecutor->*(ctx->m_funcSshDisconnectAndFree))();
	ctx->m_theApp->GetMainWnd()->SendMessage(MSG_WRITE_MSG2_LISTVIEW, 0, (LPARAM)&resultViewData);
}
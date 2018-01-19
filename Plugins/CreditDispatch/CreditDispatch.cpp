// CreditDispatch.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "CreditDispatch.h"
#include "../../BillingTool/PluginInterface.h"
#include "../../BillingTool/ViewTree.h"
#include "CreditDispatchDlg.h"
#include "BusiFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#



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

// CCreditDispatchApp

BEGIN_MESSAGE_MAP(CCreditDispatchApp, CWinApp)
END_MESSAGE_MAP()


// CCreditDispatchApp ����

CCreditDispatchApp::CCreditDispatchApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CCreditDispatchApp ����

CCreditDispatchApp theApp;
// CCreditDispatchApp ��ʼ��

BOOL CCreditDispatchApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


void Initilize(CWnd *mainWnd,CViewTree *viewTree)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	

	HTREEITEM hRoot = viewTree->InsertItem(_T("�ſطַ�����"), 0, 0);
	viewTree->SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("��������"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(BusiFunc::TriggerStartUp));
	
	tmpItem = viewTree->InsertItem(_T("����ͣ��"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(BusiFunc::TriggerStop));

	tmpItem = viewTree->InsertItem(_T("��������"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(BusiFunc::TriggerStartUp));
	

	viewTree->Expand(hRoot, TVE_EXPAND);
	
}
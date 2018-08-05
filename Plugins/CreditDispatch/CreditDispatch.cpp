// CreditDispatch.cpp : ���� DLL �ĳ�ʼ�����̡�
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

//CCreditDispatchApp theApp;
// CCreditDispatchApp ��ʼ��

BOOL CCreditDispatchApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


static std::map<CString, PropertyInfo> modulePropertys = {
	{ _TEXT("����ͣ�������ַ"),
		{ _TEXT("/creditTrigger"),nullptr, FALSE, }
	},
	{ _TEXT("��������"),
		{ _TEXT("1000"),nullptr ,FALSE , }
	},
	{ _TEXT("����ʹ����"),
		{ _TEXT("10"),nullptr ,FALSE , }
	},
	{ _TEXT("��ֹ��������ǰ����������"),
		{ _TEXT("100"),nullptr ,FALSE , }
	},
	{ _TEXT("�û��ܵĻ�����"),
		{ _TEXT("200"),nullptr , FALSE , }
	},
	{ _TEXT("�ſطַ��ļ����"),
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
	

	HTREEITEM hRoot = viewTree->InsertItem(_T("�ſطַ�"), 0, 0);

	HTREEITEM tmpItem = viewTree->InsertItem(_T("��������"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[0])));
	
	tmpItem = viewTree->InsertItem(_T("����ͣ����NET��"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[1])));

	tmpItem = viewTree->InsertItem(_T("����ͣ����FILE��"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[2])));
	
	tmpItem = viewTree->InsertItem(_T("�������ѡ�FILE��"), 1, 2, hRoot);
	viewTree->SetItemData(tmpItem, DWORD_PTR(&(moduleCallBackDef[3])));
	
}
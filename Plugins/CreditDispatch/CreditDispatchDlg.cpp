// CreditDispatchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CreditDispatch.h"
#include "CreditDispatchDlg.h"
#include "afxdialogex.h"


// CCreditDispatchDlg 对话框

IMPLEMENT_DYNAMIC(CCreditDispatchDlg, CDialogEx)

CCreditDispatchDlg::CCreditDispatchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CCreditDispatchDlg::~CCreditDispatchDlg()
{
}

void CCreditDispatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCreditDispatchDlg, CDialogEx)
END_MESSAGE_MAP()


// CCreditDispatchDlg 消息处理程序

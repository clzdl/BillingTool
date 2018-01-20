// LoadingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BillingTool.h"
#include "LoadingDlg.h"


// LoadingDlg 对话框
LoadingDlg::LoadingDlg(HWND hParentWnd, LP_CUPDIALOG_USERPROC lpUserProc, LPVOID lpUserProcParam, LPCTSTR lpszDlgTitle, bool bAllowCancel, bool autoIncrement)
	: CUPDialog(hParentWnd, lpUserProc, lpUserProcParam, lpszDlgTitle, bAllowCancel, autoIncrement)
{
}
LoadingDlg::~LoadingDlg()
{
}
INT_PTR LoadingDlg::OnMessage(HWND hDlg, UINT Message, WPARAM wParam, LPARAM lParam, BOOL bProcessed)
{
	switch (Message)
	{
		case WM_INITDIALOG:
		{
			return TRUE;
		}
	}
	return FALSE; // Return false to continue any Default processing
}
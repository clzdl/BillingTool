#pragma once
#include "UniversalProgressDialog/UPDialog.h"
// LoadingDlg ¶Ô»°¿ò

class LoadingDlg : public CUPDialog
{

public:
	LoadingDlg(HWND hParentWnd, LP_CUPDIALOG_USERPROC lpUserProc, LPVOID lpUserProcParam, LPCTSTR lpszDlgTitle = _T("Please Wait.."), bool bAllowCancel = true,bool autoIncrement = false);
	virtual ~LoadingDlg();


	INT_PTR OnMessage(HWND hDlg, UINT Message, WPARAM wParam, LPARAM lParam, BOOL bProcessed);
};

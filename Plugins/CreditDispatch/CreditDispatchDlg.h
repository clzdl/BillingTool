#pragma once


// CCreditDispatchDlg 对话框

class CCreditDispatchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCreditDispatchDlg)

public:
	CCreditDispatchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCreditDispatchDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

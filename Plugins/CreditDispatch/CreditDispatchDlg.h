#pragma once


// CCreditDispatchDlg �Ի���

class CCreditDispatchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCreditDispatchDlg)

public:
	CCreditDispatchDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCreditDispatchDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

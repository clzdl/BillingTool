
#pragma once
/////////////////////////////////////////////////////////////////////////////
// CViewTree ����
class ModuleContext;
typedef void(*ITEM_FUNC)(ModuleContext *ctx , void *ptr);

typedef struct {
	int modulePropType;
	ITEM_FUNC  cb;
}_ItemCallBackDef;


class CViewTree : public CTreeCtrl
{
// ����
public:
	CViewTree();

// ��д
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// ʵ��
public:
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()
	BOOL  m_bTracking;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};

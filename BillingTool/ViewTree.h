
#pragma once
/////////////////////////////////////////////////////////////////////////////
// CViewTree ����
class ModuleContext;
typedef void(*ITEM_FUNC)(ModuleContext *ctx , void *ptr);

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
};
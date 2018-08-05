#pragma once
#include <map>
class CViewTree;
struct PropertyGrid;
class CPropertiesWnd;
typedef void(*PROPERTY_CHG_FUNC)(CPropertiesWnd *propWnd, std::map<CString, PropertyGrid> &modProp, CString newValue);

struct PropertyGrid
{
	CString propertyValue;
	PROPERTY_CHG_FUNC callBack;   ///�ص�����
	BOOL isCombox;    ///�Ƿ�����������
	std::map<CString, CString> comboxValRel;    ///�������ֵӳ��
};

/*ȫ������*/
extern std::map<int, std::map<CString, PropertyGrid> > gProperties;

/*�˵���ʼ��*/
typedef void(__cdecl * INIT_FUNC)(CWnd *mainWnd, CViewTree *viewTree);
extern "C" __declspec(dllexport) void Initilize(CWnd *mainWnd, CViewTree *viewTree);
/*��ʼ��ģ������*/
typedef void(__cdecl * INIT_PROPERTY_FUNC)(std::map<int, std::map<CString, PropertyGrid> > &gProperty);
extern "C" __declspec(dllexport) void PropertyInitilize(std::map<int, std::map<CString, PropertyGrid> > &gProperty);


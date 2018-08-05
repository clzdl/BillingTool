#pragma once
#include <map>
class CViewTree;
struct PropertyInfo;
class CPropertiesWnd;
typedef void(*PROPERTY_CHG_FUNC)(CPropertiesWnd *propWnd, std::map<CString, PropertyInfo> &modProp, CString newValue);

struct PropertyInfo
{
	CString propertyValue;
	PROPERTY_CHG_FUNC callBack;
	BOOL isCombox;    ///�Ƿ�����������
	std::map<CString, CString> comboxValRel;    ///�������ֵӳ��
};

/*ȫ������*/
extern std::map<int, std::map<CString, PropertyInfo> > gProperties;

/*�˵���ʼ��*/
typedef void(__cdecl * INIT_FUNC)(CWnd *mainWnd, CViewTree *viewTree);
extern "C" __declspec(dllexport) void Initilize(CWnd *mainWnd, CViewTree *viewTree);
/*��ʼ��ģ������*/
typedef void(__cdecl * INIT_PROPERTY_FUNC)(std::map<int, std::map<CString, PropertyInfo> > &gProperty);
extern "C" __declspec(dllexport) void PropertyInitilize(std::map<int, std::map<CString, PropertyInfo> > &gProperty);


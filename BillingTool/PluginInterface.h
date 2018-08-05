#pragma once
#include <map>
class CViewTree;
struct PropertyGrid;
class CPropertiesWnd;
typedef void(*PROPERTY_CHG_FUNC)(CPropertiesWnd *propWnd, std::map<CString, PropertyGrid> &modProp, CString newValue);

struct PropertyGrid
{
	CString propertyValue;
	PROPERTY_CHG_FUNC callBack;   ///回调函数
	BOOL isCombox;    ///是否下拉框属性
	std::map<CString, CString> comboxValRel;    ///下拉框的值映射
};

/*全局属性*/
extern std::map<int, std::map<CString, PropertyGrid> > gProperties;

/*菜单初始化*/
typedef void(__cdecl * INIT_FUNC)(CWnd *mainWnd, CViewTree *viewTree);
extern "C" __declspec(dllexport) void Initilize(CWnd *mainWnd, CViewTree *viewTree);
/*初始化模块属性*/
typedef void(__cdecl * INIT_PROPERTY_FUNC)(std::map<int, std::map<CString, PropertyGrid> > &gProperty);
extern "C" __declspec(dllexport) void PropertyInitilize(std::map<int, std::map<CString, PropertyGrid> > &gProperty);


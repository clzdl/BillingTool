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



/*公共属性名称定义*/
const CString IP_ADDR = _TEXT("IP地址");
const CString IP_PORT = _TEXT("端口号");
const CString TEST_NUMBER = _TEXT("测试号码");
const CString ACCT_ID = _TEXT("账户ID");
const CString USER_ID = _TEXT("用户ID");
const CString USER_IMSI = _TEXT("用户IMSI");
const CString USER_IMEI = _TEXT("用户IMEI");
const CString USER_HOME_CODE = _TEXT("用户归属地");
const CString USER_PROVIDER_CODE = _TEXT("归属运营商");
const CString CUST_ID = _TEXT("客户ID");
const CString DB_CONN_STRING = _TEXT("数据库连接串");
const CString HOST_USERNAME = _TEXT("用户名");
const CString HOST_USERPWD = _TEXT("密码");



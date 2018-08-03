#pragma once
#include <string>
#include <map>

extern std::map<int, std::map<CString, PropertyInfo> > gProperties;

/*获取参数属性*/
CString GetProperty(int module, CString properyName);

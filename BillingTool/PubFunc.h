#pragma once
#include <string>
#include <map>

extern std::map<int, std::map<CString, PropertyInfo> > gProperties;

/*��ȡ��������*/
CString GetProperty(int module, CString properyName);

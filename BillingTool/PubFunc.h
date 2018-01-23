#pragma once
#include <string>
#include <map>

std::string CStringToString(const CString& src, UINT codepage = CP_UTF8);

CString StringToCString(const std::string& src, UINT codepage = CP_UTF8);

extern std::map<int, std::map<CString, CString> > gProperties;
CString GetProperty(int module, CString properyName);
CString GetFormtSysTime();


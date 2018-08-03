#include "stdafx.h"
#include "PubFunc.h"
#include <string>


CString GetProperty(int module, CString properyName)
{
	std::map<CString, PropertyInfo> props = gProperties.at(module);
	PropertyInfo &prop = props.at(properyName);
	if (!prop.isCombox)
	{
		return prop.propertyValue;
	}
	else
	{//获取值得映射关系
		return prop.comboxValRel.at(prop.propertyValue);
	}
}


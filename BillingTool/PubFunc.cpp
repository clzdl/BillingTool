#include "stdafx.h"
#include "PubFunc.h"
#include <string>
#include "PluginInterface.h"

CString GetProperty(int module, CString properyName)
{
	std::map<CString, PropertyGrid> props = gProperties.at(module);
	PropertyGrid &prop = props.at(properyName);
	if (!prop.isCombox)
	{
		return prop.propertyValue;
	}
	else
	{//获取值得映射关系
		return prop.comboxValRel.at(prop.propertyValue);
	}
}


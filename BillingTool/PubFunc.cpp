#include "stdafx.h"
#include "PubFunc.h"
#include <string>
#include "PluginInterface.h"
#include "BillingTool.h"

#define _gen_module_name(e,c)	c,

static CString gModuleName[] = {
	_mod_type_map(_gen_module_name)
};
#undef _gen_module_name


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



CString GetModuleNameByModuleType(ModuleType type)
{
	return gModuleName[type];
}

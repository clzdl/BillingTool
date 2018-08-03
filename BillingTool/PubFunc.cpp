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
	{//��ȡֵ��ӳ���ϵ
		return prop.comboxValRel.at(prop.propertyValue);
	}
}


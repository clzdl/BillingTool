#pragma once
#include <string>
#include "otlv4.h"
#define FAILURE		-1
#define SUCCESS		0


class CBillingToolApp;
class CBillingToolView;

///���ַ�ת���ɶ��ֽ��ַ�
typedef std::string (*CSTRING2STRING)(const CString&, UINT);
///���ֽ��ַ�ת���ɿ��ַ�
typedef CString (*STRING2CSTRING)(const std::string&, UINT);
//��ȡģ������
typedef CString(*GET_PROPERTY)(int, CString);


class ModuleContext
{
public:
	ModuleContext(CBillingToolApp *app);
	~ModuleContext();
	int ConnectDb(std::string dbString);

private:
	ModuleContext(const ModuleContext &mc) = delete;
	ModuleContext& operator = (const ModuleContext &mc) = delete;
	ModuleContext(ModuleContext &&mc) = delete;
	ModuleContext& operator = (ModuleContext &&mc) = delete;

public:
	otl_connect *m_dbConn;
	CBillingToolApp *m_theApp;

	CSTRING2STRING m_funcCString2String;
	STRING2CSTRING m_funcString2CString;
	GET_PROPERTY m_funcGetProperty;

};

extern ModuleContext *gModuleContext;
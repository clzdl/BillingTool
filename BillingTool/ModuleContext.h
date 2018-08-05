#pragma once
#include <string>
#include "database/otlv4.h"

#define FAILURE		-1
#define SUCCESS		0


class CBillingToolApp;
class CBillingToolView;
class SshCmdExecutor;


//获取模块属性
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

	GET_PROPERTY m_funcGetProperty;
	SshCmdExecutor *m_objSshCmdExecutor;
};

extern ModuleContext *gModuleContext;
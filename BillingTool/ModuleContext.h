#pragma once
#include <string>
#include "database/otlv4.h"

#define FAILURE		-1
#define SUCCESS		0


class CBillingToolApp;
class CBillingToolView;
class SshCmdExecutor;

///宽字符转换成多字节字符
typedef std::string (*CSTRING2STRING)(const CString&, UINT);
///多字节字符转换成宽字符
typedef CString (*STRING2CSTRING)(const std::string&, UINT);
//获取模块属性
typedef CString(*GET_PROPERTY)(int, CString);


///连接服务器，并且初始化ssh
typedef bool (SshCmdExecutor::*CONNECT_AND_INIT_FUNC)(std::string, int , std::string, std::string);
//执行远程命令
typedef bool (SshCmdExecutor::*EXECUTE_CMD)(std::string);
//断开连接,释放ssh句柄
typedef void (SshCmdExecutor::*DISCONNECT_FREE)();

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

	SshCmdExecutor *m_objSshCmdExecutor;
	CONNECT_AND_INIT_FUNC m_funcSshConnectAndInit;
	EXECUTE_CMD m_funcSshExecuteCmd;
	DISCONNECT_FREE m_funcSshDisconnectAndFree;
};

extern ModuleContext *gModuleContext;
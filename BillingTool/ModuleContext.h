#pragma once
#include <string>
#include "database/otlv4.h"

#define FAILURE		-1
#define SUCCESS		0


class CBillingToolApp;
class CBillingToolView;
class SshCmdExecutor;

///���ַ�ת���ɶ��ֽ��ַ�
typedef std::string (*CSTRING2STRING)(const CString&, UINT);
///���ֽ��ַ�ת���ɿ��ַ�
typedef CString (*STRING2CSTRING)(const std::string&, UINT);
//��ȡģ������
typedef CString(*GET_PROPERTY)(int, CString);


///���ӷ����������ҳ�ʼ��ssh
typedef bool (SshCmdExecutor::*CONNECT_AND_INIT_FUNC)(std::string, int , std::string, std::string);
//ִ��Զ������
typedef bool (SshCmdExecutor::*EXECUTE_CMD)(std::string);
//�Ͽ�����,�ͷ�ssh���
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
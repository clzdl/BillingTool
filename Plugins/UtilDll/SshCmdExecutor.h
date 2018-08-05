#pragma once
#include "Poco/Net/StreamSocket.h"
#include "libssh2.h"
#include "stdafx.h"
/*
#ifdef AFX_SSHDLL_CLASS
#define AFX_SSHEX_CLASS _declspec(dllexport)
#else
#define AFX_SSHEX_CLASS _declspec(dllimport)
#endif
*/
class _declspec(dllexport) SshCmdExecutor
{
public:
	SshCmdExecutor();
	~SshCmdExecutor();

	//���Ӳ��ҳ�ʼ��
	bool ConnectAndInit(std::string hostName, int  port, std::string userName, std::string userPwd);
	//ִ������
	bool ExecuteCmd(std::string commandline);
	//�Ͽ�����
	void DisconnectAndFree();
	CString GetErrMsg();

private:
	SshCmdExecutor(const SshCmdExecutor &sce) = delete;
	SshCmdExecutor &operator = (const SshCmdExecutor &sce) = delete;
	SshCmdExecutor(SshCmdExecutor &&sce) = delete;
	SshCmdExecutor& operator = (SshCmdExecutor &&sce) = delete;

	Poco::Net::StreamSocket m_streamSocket;
	LIBSSH2_SESSION *m_session;
	LIBSSH2_CHANNEL *m_channel;
	CString m_errMsg;
};

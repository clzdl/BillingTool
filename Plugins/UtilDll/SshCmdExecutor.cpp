#include "stdafx.h"

#include "SshCmdExecutor.h"
#include "UtilDll.h"
#include "Poco/Net/NetException.h"


SshCmdExecutor::SshCmdExecutor()
{
}
SshCmdExecutor::~SshCmdExecutor()
{

}

bool SshCmdExecutor::ConnectAndInit(std::string hostName, int  port, std::string userName, std::string userPwd)
{
	LIBSSH2_KNOWNHOSTS *nh;
	const char *fingerprint;
	try
	{
		m_streamSocket.connect(Poco::Net::SocketAddress(hostName, port));
	}
	catch (Poco::Net::NetException &e)
	{
		m_errMsg.Format(_TEXT("连接服务器[%s,%d]异常."), CommonUtil::StringToCString(hostName, CP_ACP), port);
		return false;
	}
	SOCKET socket = m_streamSocket.impl()->sockfd();

	int rc = libssh2_init(0);

	if (rc != 0)
	{
		m_errMsg.Format(_TEXT("libssh2 initialization failed (%d)"), rc);
		return false;
	}


	/* Create a session instance */
	m_session = libssh2_session_init();

	if (!m_session)
	{
		return false;
	}
	/* tell libssh2 we want it all done blocking */
	libssh2_session_set_blocking(m_session, 1);

	/* ... start it up. This will trade welcome banners, exchange keys,
	* and setup crypto, compression, and MAC layers
	*/
	while ((rc = libssh2_session_handshake(m_session, socket)) == LIBSSH2_ERROR_EAGAIN);
	if (rc) 
	{
		m_errMsg.Format(_TEXT("Failure establishing SSH session: %d"), rc);
		return false;
	}
	nh = libssh2_knownhost_init(m_session);

	if (!nh) 
	{
		/* eeek, do cleanup here */
		return false;
	}

	/* read all hosts from here */
	libssh2_knownhost_readfile(nh, "known_hosts", LIBSSH2_KNOWNHOST_FILE_OPENSSH);
	/* store all known hosts to here */
	libssh2_knownhost_writefile(nh, "dumpfile", LIBSSH2_KNOWNHOST_FILE_OPENSSH);
	size_t len = 0;
	int type;
	fingerprint = libssh2_session_hostkey(m_session, &len, &type);
	if (fingerprint) 
	{
		struct libssh2_knownhost *host;
		/* introduced in 1.2.6 */
		int check = libssh2_knownhost_checkp(nh, hostName.c_str(), port,
			fingerprint, len,
			LIBSSH2_KNOWNHOST_TYPE_PLAIN |
			LIBSSH2_KNOWNHOST_KEYENC_RAW,
			&host);

		CString text = (check <= LIBSSH2_KNOWNHOST_CHECK_MISMATCH) ? CommonUtil::StringToCString(host->key, CP_ACP): _TEXT("<none>");
		TRACE(_TEXT( "Host check: %d, key: %s\n"), check, text.GetBuffer());
		text.ReleaseBuffer();

		/*****
		* At this point, we could verify that 'check' tells us the key is
		* fine or bail out.
		*****/
	}
	else
	{
		/* eeek, do cleanup here */
		return false;
	}
	libssh2_knownhost_free(nh);

	/* We could authenticate via password */
	rc = libssh2_userauth_password(m_session, userName.c_str(), userPwd.c_str());
	if (rc)
	{
		m_errMsg.Format(_TEXT("Authentication by password failed."));
		return false;
	}

	return true;
}

bool SshCmdExecutor::ExecuteCmd(std::string commandline)
{
	int rc = 0;
	bool result = true;
	do
	{
		m_channel = libssh2_channel_open_session(m_session);
		if (m_channel == NULL)
		{
			m_errMsg.Format(_TEXT("open channel failed."));
			result = false;
			break;
		}


		/* Open a SHELL on that pty */
		if (libssh2_channel_shell(m_channel))
		{
			m_errMsg.Format(_TEXT("Unable to request shell on allocated pty"));
			result = false;
			break;
		}

		int bytecount = 0;

		libssh2_channel_write(m_channel, commandline.c_str(), commandline.size());
		libssh2_channel_send_eof(m_channel);

		char buffer[4096] = { 0 };
		do
		{///错误流通道
			rc = libssh2_channel_read_stderr(m_channel, buffer, sizeof(buffer));
			if (rc > 0)
			{
				bytecount += rc;
				m_errMsg.Format(_TEXT("errMsg:%s"), CommonUtil::StringToCString(buffer, CP_UTF8));
				result = false;
			}
		} while (rc > 0);
		if (!result)
		{
			break;
		}

		////正常流通道
		memset(buffer, 0, sizeof(buffer));
		do
		{
			rc = libssh2_channel_read(m_channel, buffer, sizeof(buffer));
			if (rc > 0)
			{
				bytecount += rc;
				TRACE(_TEXT("we read: %s \n"), CommonUtil::StringToCString(buffer, CP_UTF8));
			}
		} while (rc > 0);
	} while (false);

	libssh2_channel_close(m_channel);
	int exitcode = 0;
	char *exitsignal = (char *)"none";
	if (rc == 0)
	{
		exitcode = libssh2_channel_get_exit_status(m_channel);
		libssh2_channel_get_exit_signal(m_channel, &exitsignal, NULL, NULL, NULL, NULL, NULL);
	}


	if (exitsignal)
	{
		fprintf(stderr, "\nGot signal: %s\n", exitsignal);
	}
	else
	{
		fprintf(stderr, "\nEXIT: %d\n", exitcode);
	}
	libssh2_channel_free(m_channel);
	m_channel = NULL;
	return result;
}

void SshCmdExecutor::DisconnectAndFree()
{
	if (m_session)
	{
	
		libssh2_session_disconnect(m_session, "Normal Shutdown, Thank you for playing");
		libssh2_session_free(m_session);
		m_session = NULL;
		m_streamSocket.close();
		
	}
	libssh2_exit();
}

CString SshCmdExecutor::GetErrMsg()
{
	return m_errMsg;
}

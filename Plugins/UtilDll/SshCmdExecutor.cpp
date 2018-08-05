#include "stdafx.h"

#include "SshCmdExecutor.h"
#include "UtilDll.h"
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
	m_streamSocket.connect(Poco::Net::SocketAddress(hostName, port));
	SOCKET socket = m_streamSocket.impl()->sockfd();

	int rc = libssh2_init(0);

	if (rc != 0) {
		m_errMsg.Format(_TEXT("libssh2 initialization failed (%d)"), rc);
		return false;
	}


	/* Create a session instance */
	m_session = libssh2_session_init();

	if (!m_session)
		return false;

	/* tell libssh2 we want it all done blocking */
	libssh2_session_set_blocking(m_session, 1);

	/* ... start it up. This will trade welcome banners, exchange keys,
	* and setup crypto, compression, and MAC layers
	*/
	while ((rc = libssh2_session_handshake(m_session, socket)) == LIBSSH2_ERROR_EAGAIN);
	if (rc) {
		fprintf(stderr, "Failure establishing SSH session: %d\n", rc);
		return false;
	}
	nh = libssh2_knownhost_init(m_session);

	if (!nh) {
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

	if (fingerprint) {
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
	else {
		/* eeek, do cleanup here */
		return false;
	}
	libssh2_knownhost_free(nh);


	/* We could authenticate via password */
	while ((rc = libssh2_userauth_password(m_session, userName.c_str(), userPwd.c_str())) == LIBSSH2_ERROR_EAGAIN);
	if (rc) {
		m_errMsg.Format(_TEXT("Authentication by password failed."));
		return false;
	}

	return true;
}

bool SshCmdExecutor::ExecuteCmd(std::string commandline)
{
	int rc = 0;

	while ((m_channel = libssh2_channel_open_session(m_session)) == NULL &&
		libssh2_session_last_error(m_session, NULL, NULL, 0) == LIBSSH2_ERROR_EAGAIN);

	if (m_channel == NULL)
	{
		m_errMsg.Format(_TEXT("open channel failed."));
		return false;
	}


	while ((rc = libssh2_channel_exec(m_channel, commandline.c_str())) == LIBSSH2_ERROR_EAGAIN);
	if (rc != 0)
	{
		m_errMsg.Format(_TEXT("execute command failed."));
		return false;
	}

	int bytecount = 0;
	do
	{
		char buffer[4096] = { 0 };
		rc = libssh2_channel_read(m_channel, buffer, sizeof(buffer));

		if (rc > 0)
		{
			bytecount += rc;
			CString text = CommonUtil::StringToCString(buffer, CP_UTF8);
			TRACE(_TEXT("we read: %s \n") , text.GetBuffer() );
			text.ReleaseBuffer();
		
		}
		else {
			if (0 >rc && rc != LIBSSH2_ERROR_EAGAIN)
			{
				/* no need to output this for the EAGAIN case */
				m_errMsg.Format(_TEXT("libssh2_channel_read returned %d"), rc);
				return false;
			}
		}
	} while (rc > 0 || LIBSSH2_ERROR_EAGAIN == rc);

	while ((rc = libssh2_channel_close(m_channel)) == LIBSSH2_ERROR_EAGAIN);
	int exitcode = 0;
	char *exitsignal = (char *)"none";
	if (rc == 0)
	{
		exitcode = libssh2_channel_get_exit_status(m_channel);

		libssh2_channel_get_exit_signal(m_channel, &exitsignal, NULL, NULL, NULL, NULL, NULL);
	}


	if (exitsignal)
		fprintf(stderr, "\nGot signal: %s\n", exitsignal);
	else
		fprintf(stderr, "\nEXIT: %d\n", exitcode);

	libssh2_channel_free(m_channel);

	m_channel = NULL;
	return true;
}

void SshCmdExecutor::DisconnectAndFree()
{
	int rc = 0;
	libssh2_session_disconnect(m_session, "Normal Shutdown, Thank you for playing");
	libssh2_session_free(m_session);
	m_session = NULL;
	m_streamSocket.close();
	libssh2_exit();

}

CString SshCmdExecutor::GetErrMsg()
{
	return m_errMsg;
}

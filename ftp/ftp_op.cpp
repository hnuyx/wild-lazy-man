/* File Name: ftp_op.cpp
 *
 * Description: ftp operation
 *
 * Created by henuyx on 2015-06-18
 *
 */

/*******************INCLUDE*******************************/
#include <stdio.h>

#include "ftp_op.h"

/*******************GLOBAL********************************/

FtpOp::FtpOp() : TcpClient(false)
{
}

FtpOp::~FtpOp()
{
}

// set ip, port
void FtpOp::set_ip_port(char *ip, int port)
{
	init_socket(ip, port);
}

// set login user name, password
void FtpOp::set_login(char *usr, char *pwd)
{
	// save user/pwd
	snprintf(m_usr, FTP_USERNAME_SIZE, "%s", usr);
	snprintf(m_pwd, FTP_PASSWORD_SIZE, "%s", pwd);

	// send user

	// send password
}

// connect server
int FtpOp::connect_ftp()
{
	connect_server();

	// receive login data
	int n = read_data(m_ftp_buf, FTP_BUFFER_MAX_SIZE);

	return 0;
}

// cloes connect

// download files, path, filename

// upload files, path, filename

/*******************EOF***********************************/

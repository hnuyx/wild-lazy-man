/* File Name: ftp_op.cpp
 *
 * Description: ftp operation
 *
 * Created by henuyx on 2015-06-18
 *
 */

/*******************INCLUDE*******************************/
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
}

// connect server

// cloes connect

// download files, path, filename

// upload files, path, filename

/*******************EOF***********************************/

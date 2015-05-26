/* File Name: ftp_op.h
 *
 * Description: ftp operation
 *
 * Created by henuyx on 2015-05-26
 *
 */

#ifndef __FTP_OP_H__
#define __FTP_OP_H__

/*******************INCLUDE*******************************/

/*******************GLOBAL********************************/

#define FTP_IP_SIZE		16
#define FTP_USERNAME_SIZE	128
#define FTP_PASSWORD_SIZE	128

class FtpOp
{
public:
	FtpOp();
	~FtpOp();

	// set ip, port
	void set_ip_port(char *ip, short port);
	// set login user name, password
	void set_login(char *usr, char *pwd);

	// connect server

	// cloes connect

	// download files, path, filename

	// upload files, path, filename

private:
	// ip, port
	char m_ip[FTP_IP_SIZE];
	short m_port;

	// username, password
	char m_usr[FTP_USERNAME_SIZE];
	char m_pwd[FTP_PASSWORD_SIZE];
};

#endif

/*******************EOF***********************************/

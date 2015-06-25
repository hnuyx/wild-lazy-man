#include "ftp_op.h"

int main()
{
	FtpOp fo;
	fo.set_ip_port("192.168.1.166");
	fo.connect_ftp();
	return 0;
}


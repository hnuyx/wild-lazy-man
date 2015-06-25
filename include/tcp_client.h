/* File Name: tcp_client.h
 *
 * Description: tcp client
 *
 * Created by henuyx on 2015-06-12
 *
 */

#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__

/*******************INCLUDE*******************************/
#include "bl_common.h"

/*******************GLOBAL********************************/

class TcpClient
{
public:
	TcpClient(bool used_block = false);
	virtual ~TcpClient();

	// init data
	void init_socket(const char *srv_ip, int srv_port, int select_time = 5, int sleep_time = 1);

	// connect to server, return 0 for success, or try to connect server until success
	int connect_server();
	// disconnect
	inline void disconnect();

	// recv data, read n bytes data from socket and store into buf
	// return n byts read for success, -1 for failed
	int read_n(char *buf, BL_NS::uint32 n);
	// recv data, read n bytes data form cache block and set *pptr to the position of the data
	// return n byts read for success, -1 for failed
	int read_n(char **pptr, BL_NS::uint32 n);
	// recv data, read data and store into buf, n is the size of buf
	// return n byts read for success, -1 for failed
	int read_data(char *buf, BL_NS::uint32 n);
	// send data
	// return n byts sent for success, -1 for failed
	int send_n(char *buf, BL_NS::uint32 n);

protected:

private:
	// socket
	int m_socket;

	// use block for cache
	bool m_used_block_flag;
	// block, read position, recv len
	char *m_block;
	char *m_ptr;
	int m_recv_len;

	// server ip, port
	char m_srv_ip[BL_NS::BL_MAX_IP_SIZE];
	int m_srv_port;

	// local ip, port
	char m_loc_ip[BL_NS::BL_MAX_IP_SIZE];
	int m_loc_port;

	// select time
	int m_select_time;
	// sleep time
	int m_sleep_time;

};

#endif

/*******************EOF***********************************/

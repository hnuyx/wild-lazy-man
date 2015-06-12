/* File Name: tcp_client.cpp
 *
 * Description: tcp client
 *
 * Created by henuyx on 2015-06-12
 *
 */

/*******************INCLUDE*******************************/
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "tcp_client.h"

/*******************GLOBAL********************************/

TcpClient::TcpClient(bool used_block)
{
	m_used_block_flag = used_block;
	m_socket = -1;

	// malloc data
	if(m_used_block_flag)
	{
		m_block = (char *)malloc(BL_NS::SOCKET_BLOCK_SIZE);
		m_ptr = m_block;
	}
	else
	{
		m_block = NULL;
		m_ptr = NULL:
	}

	m_recv_len = 0;
}

TcpClient::~TcpClient()
{
	// disconnect
	disconnect();

	// free block
	if(m_used_block_flag && (NULL != m_block))
	{
		free(m_block);
	}
}

// init data
void TcpClient::init_socket(const char *srv_ip, int srv_port, int select_time, int sleep_time)
{
	snprintf(m_srv_ip, BL_NS::MAX_IP_SIZE, "%s", srv_ip);
	m_srv_port = srv_port;
	m_select_time = select_time;
	m_sleep_time = sleep_time;
}

// connect to server, return 0 for success, or try to connect server until success
int TcpClient::connect_server()
{
	struct socketaddr_in srv_addr;
	struct socketaddr_in cli_addr;
	socklen_t len;

	// server addr
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr(m_srv_ip);
	srv_addr.sin_port = htons(m_srv_port);

	// init block
	m_ptr = m_block;
	m_recv_len = 0;

RECONNECT:
	// disconnect
	disconnect();

	// get socket
	if((m_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		m_socket = -1;
		printf("socket failed, sleep %ds, server: %s:%d\n", m_sleep_time, m_srv_ip, m_srv_port);
		sleep(m_sleep_time);
		goto RECONNECT;
	}

	// set reused
	bool b_reused = true;
	if(setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (void *)&b_reused, sizeof(b_reused)) < 0)
	{
		disconnect();
		printf("setsockopt SO_REUSEADDR failed, sleep: %ds, server: %s:%d\n", m_sleep_time, m_srv_ip, m_srv_port);
		sleep(m_sleep_time);
		goto RECONNECT;
	}

	// set no send buffer
	int i_buf = 0;
	if(setsockopt(m_socket, SOL_SOCKET, SO_SNDBUF, (void *)&i_buf, sizeof(i_buf)) < 0)
	{
		disconnect();
		printf("setsockopt SO_SNDBUF failed, sleep :%ds, server: %s:%d\n", m_sleep_time, m_srv_ip, m_srv_port);
		sleep(m_sleep_time);
		goto RECONNECT;
	}

	// connect
	if(connect(m_socket, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0)
	{
		disconnect();
		printf("connect failed, sleep: %ds, server: %s:%d\n", m_sleep_time, m_srv_ip, m_srv_port);
		sleep(m_sleep_time);
		goto RECONNECT;
	}

	// get local ip:port
	if(getsockname(m_socket, (struct sockaddr *)cli_addr, sizeof(cli_addr)) < 0)
	{
		// failed
		snprintf(m_loc_ip, BL_NS::MAX_IP_SIZE, "127.0.0.1");
		m_loc_port = 0;
	}
	else
	{
		// success
		snprintf(m_loc_ip, BL_NS::MAX_IP_SIZE, cli_addr.sin_addr.s_addr);
		m_loc_port = ntohs(cli_addr.sin_port);
	}

}

// disconnect
void TcpClient::disconnect()
{
	if(-1 != m_socket)
	{
		close(m_socket);
		m_socket = -1;
	}
}

// recv data, read n bytes data from socket and store into buf
// return n byts read for success, -1 for failed
int TcpClient::read_n(char *buf, BL_NS::uint32 n)
{
}

// recv data, read n bytes data form cache block and set *vptr to the position of the data
// return n byts read for success, -1 for failed
int TcpClient::read_n(char **vpter, BL_NS::uint32 n)
{
}

// send data
int TcpClient::send_n(char *buf, BL_NS::uint32 n)
{
}

/*******************EOF***********************************/

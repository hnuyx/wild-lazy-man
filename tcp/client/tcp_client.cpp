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
#include <sys/select.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "tcp_client.h"

/*******************GLOBAL********************************/

TcpClient::TcpClient(bool used_block)
{
	m_used_block_flag = used_block;
	m_socket = -1;

	// malloc data
	if(m_used_block_flag)
	{
		m_block = (char *)malloc(BL_NS::BL_SOCKET_BLOCK_SIZE);
		m_ptr = m_block;
	}
	else
	{
		m_block = NULL;
		m_ptr = NULL;
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
	snprintf(m_srv_ip, BL_NS::BL_MAX_IP_SIZE, "%s", srv_ip);
	m_srv_port = srv_port;
	m_select_time = select_time;
	m_sleep_time = sleep_time;
}

// connect to server, return 0 for success, or try to connect server until success
int TcpClient::connect_server()
{
	struct sockaddr_in srv_addr;
	struct sockaddr_in cli_addr;

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
	int i_reused = 1;
	if(setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (void *)&i_reused, sizeof(i_reused)) < 0)
	{
		disconnect();
		printf("setsockopt SO_REUSEADDR failed, sleep: %ds, server: %s:%d\n", m_sleep_time, m_srv_ip, m_srv_port);
		printf("error: %s\n", strerror(errno));
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
	socklen_t slen;
	if(getsockname(m_socket, (struct sockaddr *)&cli_addr, &slen) < 0)
	{
		// failed
		snprintf(m_loc_ip, BL_NS::BL_MAX_IP_SIZE, "%s", "127.0.0.1");
		m_loc_port = 0;
	}
	else
	{
		// success
		snprintf(m_loc_ip, BL_NS::BL_MAX_IP_SIZE, "%s", inet_ntoa(cli_addr.sin_addr));
		m_loc_port = ntohs(cli_addr.sin_port);
	}

	return 0;
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
	fd_set fset;
	struct timeval ts;

	// record left bytes and recv result
	int left = (int)n;
	int ret = 0;

	// disconnect
	if(-1 == m_socket)
	{
		return -1;
	}

	while(left > 0)
	{
		FD_ZERO(&fset);
		FD_SET(m_socket, &fset);
		ts.tv_sec = m_select_time;
		ts.tv_usec = 0;

		if(select(m_socket + 1, &fset, 0, 0, &ts) > 0)
		{
			ret = recv(m_socket, buf + n - left, left, 0);
			if(ret < 0)
			{
				if(EINTR == errno)
				{
					// interrupt
					ret = 0;
				}
				else if(EAGAIN == errno)
				{
					//  resource temporaritily unavailable
					sleep(m_sleep_time);
					ret = 0;
				}
				else
				{
					// error
					return -1;
				}
			}
			else if(0 == ret)
			{
				return -1;
			}

			left -= ret;
		}
	}

	return (n - left);
}

// recv data, read data and store into buf, n is the size of buf
// return n byts read for success, -1 for failed
int TcpClient::read_data(char *buf, BL_NS::uint32 n)
{
	fd_set fset;
	struct timeval ts;

	// recv result
	int ret = 0;

	// disconnect
	if(-1 == m_socket)
	{
		return -1;
	}

	FD_ZERO(&fset);
	FD_SET(m_socket, &fset);
	ts.tv_sec = m_select_time;
	ts.tv_usec = 0;

	if(select(m_socket + 1, &fset, 0, 0, &ts) > 0)
	{
		ret = recv(m_socket, buf, n, 0);
		if(ret < 0)
		{
			if(EINTR == errno)
			{
				// interrupt
				ret = 0;
			}
			else if(EAGAIN == errno)
			{
				//  resource temporaritily unavailable
				sleep(m_sleep_time);
				ret = 0;
			}
			else
			{
				// error
				return -1;
			}
		}
		else if(0 == ret)
		{
			return -1;
		}
	}

	return ret;
}

// recv data, read n bytes data form cache block and set *vptr to the position of the data
// return n byts read for success, -1 for failed
int TcpClient::read_n(char **pptr, BL_NS::uint32 n)
{
	// check block
	if(!m_used_block_flag)
	{
		printf("block is not in-used\n");
		return -1;
	}

	fd_set fset;
	struct timeval ts;
	ts.tv_sec = m_select_time;
	ts.tv_usec = 0;

READ_BLOCK:
	// read form block
	if(m_recv_len >= (int)n)
	{
		*pptr = m_ptr;
		m_recv_len -= n;
		m_ptr += n;

		return n;
	}

	// move left data
	if(m_recv_len > 0)
	{
		memmove(m_block, m_ptr, m_recv_len);
	}
	m_ptr = m_block;

	// disconnect
	if(m_block < 0)
	{
		return -1;
	}

	// n bigger than block
	if(BL_NS::BL_SOCKET_BLOCK_SIZE < n)
	{
		return -1;
	}

	// recv data
	int ret = 0;
	while(m_recv_len < (int)n)
	{
		FD_ZERO(&fset);
		FD_SET(m_socket, &fset);
		ts.tv_sec = m_select_time;
		ts.tv_usec = 0;
		if(select(m_socket + 1, &fset, 0, 0, &ts) > 0)
		{
			ret = recv(m_socket, m_block + m_recv_len, BL_NS::BL_SOCKET_BLOCK_SIZE - m_recv_len, 0);
			if(ret < 0)
			{
				if(EINTR == errno)
				{
					// interrupt
					ret = 0;
				}
				else if(EAGAIN == errno)
				{
					//  resource temporaritily unavailable
					sleep(m_sleep_time);
					ret = 0;
				}
				else
				{
					// error
					return -1;
				}
			}
			m_recv_len += ret;
		}
	}

	goto READ_BLOCK;
}

// send data
// return n byts sent for success, -1 for failed
int TcpClient::send_n(char *buf, BL_NS::uint32 n)
{
	// record left bytes and send result
	int left = (int)n;
	int ret = 0;

	// disconnect
	if(-1 == m_socket)
	{
		return -1;
	}

	while(left > 0)
	{
		ret = send(m_socket, buf + n - left, left, 0);
		if(ret < 0)
		{
			if(EINTR == errno)
			{
				// interrupt
				ret = 0;
			}
			else if(EAGAIN == errno)
			{
				//  resource temporaritily unavailable
				sleep(m_sleep_time);
				ret = 0;
			}
			else
			{
				// error
				return -1;
			}
		}

		left -= ret;
	}

	return (n - left);
}

/*******************EOF***********************************/

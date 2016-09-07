// libuv sever
// http://blog.chinaunix.net/uid-15063109-id-3064600.html

#include <stdio.h>
#include <stdlib.h>

#include <uv.h>

#define SERVER_PORT 1234
#define BUFF_SIZE	1500

#define ASSERT(expr)	\
	do					\
	{					\
		if(!(expr))		\
		{				\
			fprintf(stderr, "Assertion failed in %s on line %d: %s\n.",		\
						__FILE__, __LINE__, #expr);							\
			abort();	\
		}				\
	} while(0)


void do_alloc(uv_handle_t *handle, size_t size, uv_buf_t *uv_buf)
{
	static char buf[BUFF_SIZE];
	uv_buf_init(buf, BUFF_SIZE);
}

void do_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
	printf("nread: %d\n", nread);
}

void do_accept(uv_stream_t *server, int status)
{
	ASSERT(status == 0);

	uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
	ASSERT(client != NULL);

	int r = uv_tcp_init(server->loop, client);
	ASSERT(r == 0);

	r = uv_accept(server, client);
	ASSERT(r == 0);

	r = uv_read_start(client, do_alloc, do_read);

	return ;
}

int main()
{
	struct sockaddr_in addr;
	uv_loop_t *loop;
	uv_tcp_t tcp_server;

	loop = uv_default_loop();
	int r = uv_ip4_addr("127.0.0.1", SERVER_PORT, &addr);
	ASSERT(r == 0);

	r = uv_tcp_init(loop, &tcp_server);
	ASSERT(r == 0);

	r = uv_tcp_bind(&tcp_server, (struct sockaddr*)&addr, 0);
	ASSERT(r == 0);

	r = uv_listen((uv_stream_t *)&tcp_server, 128, do_accept);

	r = uv_run(loop, UV_RUN_DEFAULT);
	ASSERT(r == 0);

	return 0;
}

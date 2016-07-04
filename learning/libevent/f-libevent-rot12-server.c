// a rot13 server written by select
// from: http://www.wangafu.net/~nickm/libevent-book/01_intro.html

#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>

#include <event.h>

#define MAX_LINE 1024
#define SERVER_PORT 40713

char rot13_char(char c)
{
	if((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
	{
		return c + 13;
	}
	else if((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z'))
	{
		return c - 13;
	}
	else
		return c;
}

void do_read(struct bufferevent ev_buffer, void *ctx)
{
	ssize_t n, left;

	struct evbuffer *input = bufferevent_get_input(ev_buffer);
	struct evbuffer *output = bufferevent_get_output(ev_buffer);

	n = evbuffer_read(input, , MAX_LINE);
	if(0 == n)
	{
		printf("peer client shut down\n");
		evutil_closesocket(fd);
		free_fd_data(fd_data);
		return ;
	}
	else if(n < 0)
	{
		perror("recv");
		evutil_closesocket(fd);
		free_fd_data(fd_data);
		return ;
	}

	for(int i = 0; i < n; i ++)
	{
		fd_data->buf[i] = rot13_char(fd_data->buf[i]);
	}
	fd_data->len = n;

	event_add(fd_data->ev_write, NULL);

	return ;
}

void do_accept(evutil_socket_t lfd, short event, void *arg)
{
	struct event_base *ev_base = (struct event_base *)arg;
	evutil_socket_t cfd = accept(lfd, NULL, NULL);
	if(cfd < 0)
	{
		perror("accept");
		return ;
	}
	else if(cfd > FD_SETSIZE)
	{
		fprintf(stderr, "cliend fd %d > FD_SETSIZE %d\n", cfd, FD_SETSIZE);
		return ;
	}
	evutil_make_socket_nonblocking(cfd);

	struct bufferevent *ev_buffer = bufferevent_socket_new(ev_base, cfd, BEV_OPT_CLOSE_ON_FREE);
	if(NULL == ev_buffer)
	{
		fprintf(stderr, "bufferevent_socket_new failed\n");
		evutil_closesocket(cfd);
		return ;
	}

	bufferevent_setcb(ev_buffer, do_read, NULL, do_error, NULL);
	bufferevent_setwatermark(ev_buffer, EV_READ, 0, MAX_LINE);
	bufferevent_enable(ev_buffer, EV_READ | EV_WRITE);

	return ;
}

void run(struct event_base *ev_base)
{
	evutil_socket_t lfd;
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(SERVER_PORT);

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd < 0)
	{
		perror("socket");
		return ;
	}
	evutil_make_socket_nonblocking(lfd);

	if(bind(lfd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
	{
		perror("bind");
		evutil_closesocket(lfd);
		return ;
	}

	if(listen(lfd, 2) < 0)
	{
		perror("listen");
		evutil_closesocket(lfd);
		return ;
	}

	struct event *ev_listener = event_new(ev_base, lfd, EV_READ | EV_PERSIST, do_accept, ev_base);
	if(NULL == ev_listener)
	{
		fprintf(stderr, "new event listener failed\n");
		evutil_closesocket(lfd);
		return ;
	}
	event_add(ev_listener, NULL);
	event_base_dispatch(ev_base);

	return ;
}

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);

	struct event_base *ev_base = event_base_new();
	if(NULL == ev_base)
	{
		fprintf(stderr, "new event base failure\n");
		return -1;
	}

	run(ev_base);

	event_base_free(ev_base);
	return 0;
}

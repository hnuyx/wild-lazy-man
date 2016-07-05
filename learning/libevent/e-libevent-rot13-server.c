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

void do_read(evutil_socket_t fd, short event, void *arg);
void do_write(evutil_socket_t fd, short event, void *arg);

typedef struct _FD_DATA
{
	char buf[MAX_LINE];
	int len;

	struct event *ev_read;
	struct event *ev_write;
} Fd_data;

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

Fd_data* new_fd_data(struct event_base *ev_base, evutil_socket_t cfd)
{
	Fd_data *fd_data = (Fd_data *)malloc(sizeof(Fd_data));
	if(NULL == fd_data)
	{
		fprintf(stderr, "malloc Fd_data failed\n");
		return NULL;
	}
	memset(fd_data, 0, sizeof(Fd_data));

	struct event *ev_read = event_new(ev_base, cfd, EV_READ | EV_PERSIST, do_read, fd_data);
	if(NULL == ev_read)
	{
		fprintf(stderr, "new read event failed\n");
		return NULL;
	}
	struct event *ev_write = event_new(ev_base, cfd, EV_WRITE | EV_PERSIST, do_write, fd_data);
	if(NULL == ev_write)
	{
		fprintf(stderr, "new write event failed\n");
		return NULL;
	}

	fd_data->ev_read = ev_read;
	fd_data->ev_write = ev_write;

	return fd_data;
}

void free_fd_data(Fd_data* fd_data)
{
	event_free(fd_data->ev_read);
	event_free(fd_data->ev_write);
	free(fd_data);
}

void do_read(evutil_socket_t fd, short event, void *arg)
{
	Fd_data *fd_data = (Fd_data *)arg;
	ssize_t n, left;

	// has data, return and wait next
	if(fd_data->len > 0)
	{
		return ;
	}

	n = recv(fd, fd_data->buf, MAX_LINE, 0);
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

void do_write(evutil_socket_t fd, short event, void *arg)
{
	Fd_data *fd_data = (Fd_data *)arg;
	ssize_t n, left, tmp;

	// no data to write
	if(fd_data->len <= 0)
	{
		event_del(fd_data->ev_write);
		return ;
	}

	n = left = fd_data->len;
	while(left > 0)
	{
		tmp = send(fd, fd_data->buf + n - left, left, 0);
		if(tmp < 0)
		{
			perror("send");
			evutil_closesocket(fd);
			free_fd_data(fd_data);
			return ;
		}
		left -= tmp;
	}
	fd_data->len = 0;

	event_del(fd_data->ev_write);
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
		evutil_closesocket(cfd);
		return ;
	}
	evutil_make_socket_nonblocking(cfd);

	Fd_data *fd_data = new_fd_data(ev_base, cfd);
	if(NULL == fd_data)
	{
		fprintf(stderr, "new Fd_data failed\n");
		evutil_closesocket(cfd);
		return ;
	}

	event_add(fd_data->ev_read, NULL);

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

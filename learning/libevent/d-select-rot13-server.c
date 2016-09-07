// a rot13 server written by select
// from: http://www.wangafu.net/~nickm/libevent-book/01_intro.html

#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>

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

int do_read(int fd)
{
	char buf[MAX_LINE];

	ssize_t n, left, tmp;

	n = recv(fd, buf, MAX_LINE, 0);
	if(0 == n)
	{
		printf("peer client shut down\n");
		return 0;
	}
	else if(n < 0)
	{
		perror("recv");
		return -1;
	}

	for(int i = 0; i < n; i ++)
	{
		buf[i] = rot13_char(buf[i]);
	}

	left = n;
	while(left > 0)
	{
		tmp = send(fd, buf + n - left, left, 0);
		if(tmp < 0)
		{
			perror("send");
			return -1;
		}
		left -= tmp;
	}

	return n;
}

int do_write(int fd)
{
	return 1;
}

void run(void)
{
	int lfd;
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(SERVER_PORT);

	fd_set read_set, write_set;
	int max_fd = -1;
	bool state[FD_SETSIZE];

	for(int i = 0; i < FD_SETSIZE; ++ i)
	{
		state[i] = false;
	}

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd < 0)
	{
		perror("socket");
		return ;
	}
	if(lfd >= FD_SETSIZE)
	{
		fprintf(stderr, "listen's fd %d is too big than %d\n", lfd, FD_SETSIZE);
		return ;
	}
	max_fd = lfd;
	state[lfd] = true;

	fcntl(lfd, F_SETFL, O_NONBLOCK);

	if(bind(lfd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
	{
		perror("bind");
		close(lfd);
		return ;
	}

	if(listen(lfd, 2) < 0)
	{
		perror("listen");
		close(lfd);
		return ;
	}

	while(1)
	{
		FD_ZERO(&read_set);
		FD_ZERO(&write_set);

		max_fd = lfd;
		for(int i = 0; i < FD_SETSIZE; ++ i)
		{
			if(state[i])
			{
				FD_SET(i, &read_set);
				FD_SET(i, &write_set);
				if(i > max_fd)
				{
					max_fd = i;
				}
			}
		}

		if(select(max_fd + 1, &read_set, &write_set, NULL, NULL) < 0)
		{
			perror("select");
			for(int i = 0; i < FD_SETSIZE; ++ i)
			{
				if(state[i])
				{
					close(i);
				}
			}
			return ;
		}

		if(FD_ISSET(lfd, &read_set))
		{
			int cfd = accept(lfd, NULL, NULL);
			if(cfd < 0)
			{
				perror("accept");
			}
			else if(cfd >= FD_SETSIZE)
			{
				fprintf(stderr, "client's fd %d is too big than %d\n", cfd, FD_SETSIZE);
				close(cfd);
			}
			else
			{
				fcntl(cfd, F_SETFL, O_NONBLOCK);
				state[cfd] = true;
			}
		}

		for(int i = 0; i < max_fd + 1; i ++)
		{
			int ret = 1;
			if(i == lfd)
			{
				continue;
			}

			if(FD_ISSET(i, &read_set))
			{
				ret = do_read(i);
			}

			if(FD_ISSET(i, &write_set))
			{
				ret = do_write(i);
			}

			if(ret <= 0)
			{
				state[i] = false;
				close(i);
			}
		}
	}

	return ;
}

int main()
{
	run();
	return 0;
}

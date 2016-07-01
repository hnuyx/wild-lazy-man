// a rot13 server written by froking
// from: http://www.wangafu.net/~nickm/libevent-book/01_intro.html

#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

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

void child(int fd)
{
	char buf[MAX_LINE];

	ssize_t n, left, tmp;

	while(1)
	{
		n = recv(fd, buf, MAX_LINE, 0);
		if(0 == n)
		{
			printf("peer client shut down\n");
			return ;
		}
		else if(n < 0)
		{
			perror("recv");
			break;
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
				return ;
			}
			left -= tmp;
		}
	}

	return ;
}

void run(void)
{
	int lfd;
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

	if(bind(lfd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
	{
		perror("bind");
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
		int cfd = accept(lfd, NULL, NULL);
		if(cfd < 0)
		{
			perror("accept");
		}
		else
		{
			if(0 == fork())
			{
				close(lfd);
				child(cfd);
				close(cfd);
				return ;
			}
			else
			{
				close(cfd);
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

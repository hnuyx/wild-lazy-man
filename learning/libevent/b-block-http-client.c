// a simple  blocking http client
// from: http://www.wangafu.net/~nickm/libevent-book/01_intro.html

#include <stdio.h>

#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
	const char *hn = "www.github.com";
	// const char *hn = "www.baidu.com";
	// const char *hn = "www.csdn.net";
	// const char *hn = "www.google.com";
	struct hostent *ht = gethostbyname(hn);
	if(ht)
	{
		printf("h_name: %s\n"
			   "h_addrtype: %d\n"
			   "h_length: %d\n", ht->h_name, ht->h_addrtype, ht->h_length);
		printf("h_aliases:\n");
		char *tmp;
		for(int i = 0; tmp = ht->h_aliases[i]; ++ i)
		{
			printf("%s\n", tmp);
		}
		printf("h_addr_list:\n");
		for(int i = 0; tmp = ht->h_addr_list[i]; ++ i)
		{
			printf("%s\n", tmp);
		}
	}
	else
	{
		fprintf(stderr, "gethostbyname %s faild: %s", hn, hstrerror(h_errno));
		return -1;
	}

	if(AF_INET != ht->h_addrtype)
	{
		fprintf(stderr, "no ipv4 support, sorry.\n");
		return -1;
	}

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd < 0)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(80);
	sin.sin_addr = *(struct in_addr *)ht->h_addr;
	if(connect(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
	{
		perror("connect");
		close(fd);
		return -1;
	}

	const char query[] = "GET / HTTP/1.0\r\n"
						 "Host: www.github.com\r\n"
						 "\r\n";
	const char *cp = query;
	ssize_t n, left;
	char buf[1024];

	cp = query;
	left = strlen(query);
	while(left > 0)
	{
		n = send(fd, cp, left, 0);
		if(n <= 0)
		{
			perror("send");
			close(fd);
			return -1;
		}
		left -= n;
		cp += n;
	}

	// get response
	while(1)
	{
		n = recv(fd, buf, sizeof(buf), 0);
		if(0 == n)
		{
			break;
		}
		if(n < 0)
		{
			perror("recv");
			close(fd);
			return -1;
		}
		fwrite(buf, 1, n, stdout);
	}
	
	close(fd);

	return 0;
}

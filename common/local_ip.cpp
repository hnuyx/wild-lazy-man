
/* File Name: local_ip.cpp
 *
 * Description: get local ip
 *
 * Created by henuyx on 2015-04-27
 *
 */

/*******************INCLUDE*******************************/
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include "local_ip.h"

/*******************GLOBAL********************************/

#define STORE_IP(ip, lip)\
        if(NULL != ip)\
        {\
                sprintf(ip, "%s", lip);\
        }\

/* get local ip string */
char* get_local_ip(char *ip)
{
        char hn[128];
        static char local_ip[64];
        struct hostent *hent;

        memset(hn, 0, 128);
        memset(local_ip, 0, 64);

        gethostname(hn, 128);
        hent=gethostbyname(hn);
        if(hent)
        {
                for(int i = 0; hent->h_addr_list[i] != NULL; i ++)
                {
                        snprintf(local_ip, 64, "%s", inet_ntoa(*(struct in_addr*)(hent->h_addr_list[0])));
                        if(0 == strcmp(local_ip, "127.0.0.1") || 0 == strcmp(local_ip, "::1"))
                        {
                                continue;
                        }
                        break;
                }
        }
        else
        {
                snprintf(local_ip, 64, "127.0.0.1");
        }

        STORE_IP(ip, local_ip);
        return local_ip;
}

/* get local ip string by socked */
char* get_local_ip_sock(char *ip)
{
        static char local_ip[64];

        int sockfd;
        struct ifreq ifq[16];
        struct ifconf ifc;
        int i = 0, count = 0;

        memset(local_ip, 0, 64);

        if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
                sprintf(local_ip, "127.0.0.1");
                STORE_IP(ip, local_ip);
                return local_ip;
        }

        ifc.ifc_len = sizeof(ifq);
        ifc.ifc_buf = (caddr_t)ifq;

        count = (ifc.ifc_len/sizeof(struct ifreq));
        if(ioctl(sockfd, SIOCGIFCONF, (char *)&ifc))
        {
                sprintf(local_ip, "127.0.0.1");
                STORE_IP(ip, local_ip);
                return local_ip;
        }
        close(sockfd);

        for(i = 0; i < count; i ++)
        {
                snprintf(local_ip, 64, "%s", inet_ntoa(((struct sockaddr_in*)&(ifq[i].ifr_addr))->sin_addr));
                if(0 == strcmp(local_ip, "127.0.0.1") ||
                        0 == strcmp(local_ip, "0.0.0.0"))
                {
                        continue;
                }
                break;
        }

        if(i == count)
        {
                sprintf(local_ip, "127.0.0.1");
                STORE_IP(ip, local_ip);
                return local_ip;
        }

        STORE_IP(ip, local_ip);
        return local_ip;
}

/* get local ip string by bash shell */
char* get_local_ip_bash(char *ip)
{
        static char local_ip[64];
        FILE *fp;

        memset(local_ip, 0, 64);

        if((fp = popen("/sbin/ifconfig | grep \"inet addr\" | head -1 | awk -F: '{print $2}'| awk '{print $1}'", "r")) == NULL)
        {
                sprintf(local_ip, "127.0.0.1");
                STORE_IP(ip, local_ip);
                return local_ip;
        }

        if(NULL == fgets(local_ip, 64, fp))
        {
                sprintf(local_ip, "127.0.0.1");
        }
        pclose(fp);

        int len = strlen(local_ip);
        if('\n' == local_ip[len - 1])
        {
                local_ip[len - 1] = '\0';
        }
        STORE_IP(ip, local_ip);
        return local_ip;
}

/*******************EOF***********************************/

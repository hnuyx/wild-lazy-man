
/* File Name: local_ip.h
 *
 * Description: get local ip
 *
 * Created by henuyx on 2015-04-27
 *
 */

#ifndef __LOCAL_IP_H__
#define __LOCAL_IP_H__

/*******************INCLUDE*******************************/

/*******************GLOBAL********************************/

/* Function Name: get_local_ip
 *
 * Description: get local ip string
 *
 * Parameter:
 * ip: if ip is not NULL, the local ip will be stored in it.
 *      you should give ip a enough buffer, otherwise, may it out of memory.
 *
 * Return Value: return local ip
 *
 */
char* get_local_ip(char *ip = NULL);
char* get_local_ip_sock(char *ip = NULL);
char* get_local_ip_bash(char *ip = NULL);

#endif

/*******************EOF***********************************/

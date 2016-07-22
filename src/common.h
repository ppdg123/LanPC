#ifndef _COMMON_H_
#define _COMMON_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


#define VPS_IP "168.235.72.188"
#define PORT "12345"
#define LAN_MAC "fc:aa:14:74:13:df"
#define STR_SZ 256
#define TM_OT 70
extern int sockfd, newsockfd, portno;
extern int openflag;
extern socklen_t clilen;
extern char buffer[STR_SZ],pcmd[STR_SZ];
extern struct sockaddr_in serv_addr, cli_addr;
extern int n;
extern int id; // 1: server; 2: lanclient; 3: localclient
extern struct hostent * server;

void error(const char * msg);
void vps_server_init();
void client_init(int tid);
void commandParse(char * cmd);
void beforeQuit();

#endif

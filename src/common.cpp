#include "common.h"
#include <time.h>
int id;
int sockfd, newsockfd, portno;
int openflag,rebootflag,poweroffflag;
socklen_t clilen;
char buffer[STR_SZ],pcmd[STR_SZ];
struct sockaddr_in serv_addr, cli_addr;
struct hostent * server;
int n;
int lanlive,tarlive;
time_t lantime,tartime;

void error(const char * msg){
   perror(msg);
   exit(1);
}

void vps_server_init(){
   sockfd = socket(AF_INET, SOCK_STREAM,0);
   if(sockfd<0){
   	error("ERROR: init socket");
   }
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = atoi(PORT);
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   if(bind(sockfd, (struct sockaddr *) &serv_addr,
			   sizeof(serv_addr))<0){
   	error("ERROR: binding");
   }
   openflag = 0;
   rebootflag = 0;
   poweroffflag = 0;
   lanlive = 0;
   tarlive = 0;
   id = 1;
}

void client_init(int tid){
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if(sockfd<0){
   	error("ERROR: init socket");
   }
   portno = atoi(PORT);
   server = gethostbyname(VPS_IP);
   if(server==NULL){
   	error("ERROR: VPS host");
   }
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr,
	(char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
   if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
   	error("ERROR: connect to vps");
   }
   id = tid;
}


void commandParse(char * cmd){
	// server received command
	if(id==1){
		time_t tt = time(NULL);
		if((tt-lantime)>TM_OT) lanlive = 0;
		if((tt-tartime)>TM_OT) tarlive = 0;
	}
		//user send command
	if(id==1&&0==strncmp(cmd,"ping",strlen("ping"))){
		sprintf(pcmd,"Lan_%s;Tar_%s",lanlive?"On":"Off",tarlive?"On":"Off");
		n = write(newsockfd,pcmd,strlen(pcmd)+1);
		return;
	}

	if(id==1&&0==strncmp(cmd,"openpc",strlen("openpc"))){
		openflag = 1;
		n = write(newsockfd,"openpc_received",strlen("openpc_received")+1);
		return;
	}
	if(id==1&&0==strncmp(cmd,"poweroff",strlen("poweroff"))){
		poweroffflag = 1;
		n = write(newsockfd,"poweroff_received",strlen("poweroff_received")+1);
		return;
	}
		//lan client send command
	if(id==1&&0==strncmp(cmd,"lancommand?",strlen("lancommand?"))){
		lantime = time(NULL);
		lanlive = 1;
		if(openflag){
			n = write(newsockfd,"open",strlen("open")+1);
			openflag = 0;
			return;
		}
		n = write(newsockfd,"nothing",strlen("nothing")+1);
		return;
	}
		//local PC send command
	if(id==1&&0==strncmp(cmd,"tarcommand?",strlen("tarcommand?"))){
		tartime = time(NULL);
		tarlive = 1;
		if(rebootflag){
			n = write(newsockfd,"reboot",strlen("reboot")+1);
			rebootflag = 0;
			return;
		}
		if(poweroffflag){
			n = write(newsockfd,"poweroff",strlen("poweroff")+1);
			poweroffflag = 0;
			return;
		}
		n = write(newsockfd,"nothing",strlen("nothing")+1);
		return;
	}

	// lan client received command
	if(id==2&&0==strncmp(cmd,"open",strlen("open"))){
		sprintf(pcmd,"wakeonlan %s",LAN_MAC);
		system(pcmd);
		return;
	}

	// local PC received command
	if(id==3&&0==strncmp(cmd,"reboot",strlen("reboot"))){
		system("reboot");
		return;
	}
	if(id==3&&0==strncmp(cmd,"poweroff",strlen("poweroff"))){
		system("poweroff");
		return;
	}

	if(id==4){
		printf("%s\n",cmd);
		return;
	}
}

void beforeQuit(){
	close(sockfd);
}

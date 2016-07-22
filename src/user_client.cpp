#include "common.h"

int main(int argc , char * argv[]){
	if(argc!=2){
		printf("./user_client [1-3] \n 1 : ping\n 2 : open\n 3 : poweroff\n");
		return 0;
	}
	client_init(4);
	bzero(buffer,STR_SZ);
	switch(atoi(argv[1])){
		case 1 : strcpy(buffer,"ping"); break;
		case 2 : strcpy(buffer,"openpc"); break;
		case 3 : strcpy(buffer,"poweroff"); break;
	}
	n = write(sockfd,buffer,strlen(buffer));
	bzero(buffer,STR_SZ);
	n = read(sockfd,buffer,STR_SZ-1);
	commandParse(buffer);
	beforeQuit();
	return 0;
}

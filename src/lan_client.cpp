#include "common.h"

int main(){
	client_init(2);
	bzero(buffer,STR_SZ);
	strcpy(buffer,"lancommand?");
	n = write(sockfd,buffer,strlen(buffer));
	bzero(buffer,STR_SZ);
	n = read(sockfd,buffer,STR_SZ-1);
	commandParse(buffer);
	beforeQuit();
	return 0;
}

#include "common.h"

int main(){
	client_init(3);
	bzero(buffer,STR_SZ);
	strcpy(buffer,"tarcommand?");
	n = write(sockfd,buffer,strlen(buffer));
	bzero(buffer,STR_SZ);
	n = read(sockfd,buffer,STR_SZ-1);
	commandParse(buffer);
	beforeQuit();
	return 0;
}

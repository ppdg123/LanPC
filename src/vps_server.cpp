#include "common.h"

int main(){
	vps_server_init();
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	while(1){
		newsockfd = accept(sockfd,
				(struct sockaddr *) &cli_addr,
				&clilen);
		if(newsockfd < 0){
			error("ERROR: Accept");
		}
		bzero(buffer,STR_SZ);
		n = read(newsockfd,buffer,STR_SZ-1);
		commandParse(buffer);
		close(newsockfd);
	}
	beforeQuit();	
	return 0;
}

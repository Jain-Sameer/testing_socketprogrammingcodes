#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    int sockfd;

    char str[100];

    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(servaddr);
    memset(&servaddr, 0,sizeof(servaddr));
    memset(&cliaddr, 0,sizeof(cliaddr));

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Client started : ");
    while(1){
        memset(str, 0, 100);
        fgets(str, 100, stdin);
        sendto(sockfd, str, 100, 0, (struct sockaddr *) &servaddr,  len);
        printf("Client (You) : %s", str);
        memset(str, 0, 100);
        recvfrom(sockfd, str,100, 0,(struct sockaddr *) &servaddr, &len);
        printf("Server : %s\n", str);
    }
    
        
}
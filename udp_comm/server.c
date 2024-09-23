#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int main() {
    char str[100];
    
    int sockfd, commfd;
    struct sockaddr_in serveraddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    
    memset(&serveraddr, 0,sizeof(serveraddr));
    memset(&cliaddr,0, sizeof(cliaddr));

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0) {
        perror("Socket creation failed!");
        exit(1);
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(22000);
    serveraddr.sin_addr.s_addr = (INADDR_ANY);

    if(bind(sockfd, (struct sockaddr*) &serveraddr, sizeof(serveraddr)) < 0 ){
        perror("Error in BIND");
        exit(1);
    }
    printf("Server Started: \n");
    while(1){
        memset(str, 0, sizeof(str));

        recvfrom(sockfd, str, 100, 0, (struct sockaddr*) &cliaddr, &len);
        printf("Client : %s\n", str);

        printf("Reply : ");
        fgets(str, 100, stdin);
        sendto(sockfd, str, strlen(str), 0, (struct sockaddr *) &cliaddr, len);
        printf("Server (You) : %s\n", str);
    }

    

}
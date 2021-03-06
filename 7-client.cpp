/* client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 80
#define SERV_PORT 8000

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    int sockfd, n;
    char str[500];

    // if (argc != 2)
    // {
    //     fputs("usage:./client message\n", stderr);
    //     exit(1);
    // }
    
    for (int i = 0;; i++){
        
        // str = argv[1];
        puts("Input String:");
        scanf("%s", str);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
        servaddr.sin_port = htons(SERV_PORT);

        connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

        write(sockfd, str, strlen(str));

        n = read(sockfd, buf, MAXLINE);
        printf("Response from server:\n");
        write(STDOUT_FILENO, buf, n);
        printf("\n");
    }
    

    close(sockfd);
    return 0;
}
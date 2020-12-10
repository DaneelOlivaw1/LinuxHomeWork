/* server.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <signal.h>

#define MAXLINE 80
#define SERV_PORT 8000



int main(void)
{
    signal(SIGTTOU,SIG_IGN); 
    signal(SIGTTIN,SIG_IGN); 
    signal(SIGTSTP,SIG_IGN); 
    signal(SIGHUP ,SIG_IGN);
    int pid;
    if( pid = fork() ){
		exit(0); 	   
	}
    setsid();
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;
    char buf[MAXLINE];
    char buf2[MAXLINE];
    char str[INET_ADDRSTRLEN];
    int i, n;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, 20);

    printf("Acceptingconnections ...\n");
    while (1)
    {
        cliaddr_len = sizeof(cliaddr);
        connfd = accept(listenfd,
                        (struct sockaddr *)&cliaddr, &cliaddr_len);

        n = read(connfd, buf, MAXLINE);
        inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str));
        ntohs(cliaddr.sin_port);
        for (i = 0; i < n; i++)
            buf2[i] = buf[i];
        write(connfd, buf2, n);
        close(connfd);
    }
}
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
    int server_sockfd, client_sockfd;
    int server_len;
    unsigned int client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = 9734;
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    listen(server_sockfd, 5);
    while(1){
        char ch[100];

        printf("server waiting\n");
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
        read(client_sockfd, &ch, 100);
        printf("%s\n", ch);
        FILE *fp;
        if(NULL == (fp = fopen(ch, "r")))  
        {  
            char rep[2048] = "ERROR!";
            printf("Request ERROR\n");
            write(client_sockfd, &rep, 2048);
        }else {
            char rep[100] = "hello!";
            printf("Got request: %s\n", ch);
            char f[2048];
            char t;
            int i = 0; 
            while(EOF != (t=fgetc(fp)))  
            {  
                f[i] = t;
                i++;
            }
            printf("%s\n", f);
            write(client_sockfd, &f, 2048);
            printf("Send success\n");
        }  
        close(client_sockfd);
    }

}
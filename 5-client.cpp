#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9734;
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1){
        perror("oops:client2");
        _exit(1);
    }

    //system("top -n 1 > a.out");
    FILE *fp;  
    if(NULL == (fp = fopen("a.out", "r")))  
    {  
        exit(1);  
    }  
  
    char ch[2048];
    char t;
    int i = 0; 
    while(EOF != (t=fgetc(fp)))  
    {  
        ch[i] = t;
        i++;
    }  
    //printf("%s", ch);
    
    write(sockfd, &ch, 2048);
    // read(sockfd, &ch, 2048);
    printf("sent to server \n");
    close(sockfd);
    _exit(0);
    fclose(fp);
}
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch[100] = "AB";
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
    write(sockfd, &ch, 100);
    read(sockfd, &ch, 100);
    printf("char from server = %s\n", ch);
    close(sockfd);
    _exit(0);
}
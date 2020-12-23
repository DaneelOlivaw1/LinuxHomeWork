#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define N 512
#define port 1024

void int_to_char(int x, char* s2){               //int 转 char
    char s1[10];
    int t = 0;
    while(x){
        s1[t++] = '0' + x % 10;
        x /= 10; 
    }
    for(int i = 0; i < t; ++ i){
        s2[i] = s1[t - i - 1];
    }
}

int get_Request(int fd){                         // GET
    int messlen = 0;
    char buf[N];
    if((messlen = recv(fd, buf, N, 0)) < 0){
        perror("Error handling incoming request");
        return -1;
    }
    //准备要发送的信息
    char statusCode[N] = "200 OK";
    char contentType[N] = "text/html";
    char content[N] = "<html>\n<head>\n<title>my simple httpserver</title>\n</head>\n<h1>Hello World</h1>\n</body>\n</html>\n";
    int len = strlen(content);
    char contentSize[N];
    int_to_char(len, contentSize);
    char head[N] = "\r\nHTTP/1.1 ";
    char ContentType[N] = "\r\nContent-Type: ";
    char ServerHead[N] = "\r\nServer: localhost";
    char ContentLength[N] =  "\r\nContent-Length: ";
    char Date[N] = "\r\nDate: ";
    char Newline[N] = "\r\n";
    time_t rawtime;
    time(&rawtime);
    char message[N + N] = "\0";


    //将发送信息存入message数组
    strcat(message, head);
    strcat(message, statusCode);
    strcat(message, ContentType);
    strcat(message, contentType);
    strcat(message, ServerHead);
    strcat(message, ContentLength);
    strcat(message, contentSize);
    strcat(message, Date);
    strcat(message, (char*)ctime(&rawtime));
    strcat(message, Newline);
    

    int n;
    n=send(fd,message,strlen(message),0);
    n=send(fd,content,strlen(content),0);

    return n;
}

int main(int argc, char **argv)
{
    int Serverfd;
    struct sockaddr_in ServerAddr;

    if((Serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket error");
        return -1;
    }  

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = INADDR_ANY;
    ServerAddr.sin_port = htons(port);

    if((bind(Serverfd, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr))) < 0){
        perror("bind error");
        return -1;
    }

    if(listen(Serverfd, 5) < 0){        //
        perror("listen error");
        return -1;
    }
    
    int Clientfd;
    struct sockaddr_in ClientAddr;
    socklen_t ClientLen = sizeof(ClientAddr); 
    while(1){
        Clientfd = accept(Serverfd, (struct sockaddr*)&ClientAddr, &ClientLen);
        if(get_Request(Clientfd) < 0){
            perror("http request get error");
            exit(-1);
        }
        close(Clientfd);
    }
}
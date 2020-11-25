#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    
    //system("top -n 1 > a.out");
    FILE *fp;  
    if(NULL == (fp = fopen("a.out", "r")))  
    {  
        exit(1);  
    }  
  
    char ch[2048];
    int i = 0; 
    while(EOF != (ch[i]=fgetc(fp)))  
    {  
        i++; 
    }  
    printf("%s", ch);
    fclose(fp);  
}
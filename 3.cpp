#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>

int getRAND(char a, char b){
    // unsigned seed = time(0);
    // srand(seed);
    return (rand() % ((int)b-(int)a+1))+ (int)a;
}
void sig_handler(int signo)
{
  if (signo == SIGINT);
    //printf("received SIGINT\n");
}
int main(){
    if (signal(SIGINT, sig_handler) == SIG_ERR);
    unsigned seed = time(0);
    srand(seed);
    char *message;
    char buffer[BUFSIZ + 1];
    char s[20];
    int data_processed;
    int file_pipes[2];
    
    // printf("fork program starting\n");
    pid_t pid;
    if (pipe(file_pipes) == 0){
        pid = fork();
        switch (pid)
        {
        case -1:
            perror("fork failed");
            exit(1);
            break;
        case 0:
            message = "This is the child";
            for (int i = 0;; i++){
                data_processed = read(file_pipes[0], buffer, BUFSIZ);
                printf("Child:\tread %dth: %s\n", i, buffer);
                char t[20];
                for (int i = 11; i >= 0;i--){
                    t[i] = buffer[11-i];
                }
                printf("Child:\treversed string: %s\n", t);
                sleep(1);
            }
            break;
        default:
            message = "This is the parent";
            pid = fork();
            if (pid == 0){
                
                char c = getchar();
                if (c == 'q' || c == 'Q'){
                    printf("quit");
                    kill(getppid(), SIGKILL);
                    exit(0);
                }
            }
            for (int i = 0;; i++){
                for (int i = 0; i < 12; i++){
                    s[i] = (char)(rand() % ((int)'z'-(int)'a'+1))+ (int)'a';
                }
                memset(buffer, '\0', sizeof(buffer));
                data_processed = write(file_pipes[1], s, strlen(s));
                printf("Parent:\twrote %dth\n", i);
                
                sleep(1);
            }
            
            break;
        }
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
    
    exit(0);
}
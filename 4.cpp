#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>
int n;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int getRAND(int a, int b){
    // unsigned seed = time(0);
    // srand(seed);
    return (rand() % (b-a+1))+a;
}

void * func(void * arg)
{
    pthread_mutex_lock(&mutex);
    int *threadno = (int *)arg;
    n += threadno[0];
    printf("%d thread %d\n",n, threadno[0]);
    
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main()
{
    unsigned seed = time(0);
    srand(seed);
    pthread_t t[10];
    int num[10];
    pid_t pid;
    pid = fork();
    if (pid == 0){
        char c = getchar();
        if (c == 'q' || c == 'Q'){
            printf("quit");
            kill(getppid(), SIGKILL);
            exit(0);
        }

    }else{
        for (int j = 0;; j++){
            n = getRAND(50,150);
            printf("generate num :%d\n", n);
            for (int i = 1; i <= 4; i++){
                num[i] = i;
                int err = pthread_create(&t[i],NULL,func, &num[i]);
            }
            sleep(1);
        }

    }

    
    
    return EXIT_SUCCESS;
}
/*
if [ -f "a" ];then
    echo "清理可执行文件..."
    rm a
fi
echo "编译："
g++ 4.cpp -o a
echo "运行："
./a
*/
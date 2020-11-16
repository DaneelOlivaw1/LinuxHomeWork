#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <ctime>

void inputmode(char* s, char (&fs)[5]){
    
    for (int i = 0; i < 4; i++)fs[i] = '0';
    for (int p = 1; s[p] != '\0'; p++){
        // printf("%c\n", mode[p]);
        if (s[p] == 'l'){
            fs[0] = '1';
        }
        else if (s[p] == 'c'){
            fs[1] = '1';
        }
        else if (s[p] == 'w'){
            fs[2] = '1';
        }
        else if (s[p] == 'm'){
            fs[3] = '1';
        }
        else if (s[p] == 'L'){
            fs[4] = '1';
        }
    }
}

void wc(const char *filename, const char *mode, int (&res)[5]){
    
    FILE *fp = fopen(filename, "r");
    int flag = 0;
    char ch;
    int length = 0;
    while((ch = fgetc(fp))!=EOF){	//一直读到文件尾
        res[3]++;		//字符数加1 wc -m

        if(ch != '\n'){
            length++;	//记录当前行的长度 wc -L
        }
        if(ch == '\n'){
            res[0]++;	//行数加1 wc -l
            if(length>res[4]){
                res[4] = length;    //更新最大长度
            }
            length = 0;
        }
        if(ch == '\t' || ch == ' ' || ch == '\n'){
            flag = 0;		//计算单词数 wc -w
            continue;
        }
        else{
            if(flag == 0){
                res[2]++;	//计算单词数 wc -w
                flag = 1;
            }
        }
    }  
    return;
}

int main(int argc, char* argv[])
{
    char *mode;
    char *dir = ".";
    int f = 0;
    if (argc == 2){
        if (argv[1][0] != '-'){
            dir = argv[1];
        }
        else {
            mode = argv[1];
            f = 1;
        }
    }else if(argc == 3){
        
        if (argv[1][0] != '-'){
            dir = argv[1];
            mode = argv[2];
            
        }
        else {
            dir = argv[2];
            mode = argv[1];
            f = 1;
        }
    }
   
    if (f){
        char fs[5];
        inputmode(mode, fs);
        int res[5];
        for (int i = 0; i < 5; i++)res[i] = 0;
        
        wc(dir, fs, res);
        // for (int i = 0; i < 5; i++){
        //     printf("%d ", res[i]);
        // }
        // printf("\n");
        if (fs[0] == '1')printf("%d ", res[0]);
        if (fs[2] == '1')printf("%d ", res[2]);
        if (fs[1] == '1')printf("%d ", res[3]);
        printf("%s\n", dir);
    }  
}
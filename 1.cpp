#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <ctime>

void get_fir(struct stat s)  //得到文件属性字段和权限位
{
    char str[50];
    strcpy(str, "----------");
    if(S_ISDIR(s.st_mode)) str[0] = 'd';
    else if(S_ISCHR(s.st_mode)) str[0] = 'c';
    else if(S_ISBLK(s.st_mode)) str[0] = 'b';
    if((s.st_mode & S_IRUSR) == S_IRUSR) str[1] = 'r';
    if((s.st_mode & S_IWUSR) == S_IWUSR) str[2] = 'w';
    if((s.st_mode & S_IXUSR) == S_IXUSR) str[3] = 'x';
    if((s.st_mode & S_IRGRP) == S_IRGRP) str[4] = 'r';
    if((s.st_mode & S_IWGRP) == S_IWGRP) str[5] = 'w';
    if((s.st_mode & S_IXGRP) == S_IXGRP) str[6] = 'x';   
    if((s.st_mode & S_IROTH) == S_IROTH) str[7] = 'r';
    if((s.st_mode & S_IWOTH) == S_IWOTH) str[8] = 'w';
    if((s.st_mode & S_IXOTH) == S_IXOTH) str[9] = 'x'; 
    printf("%s ", str);
    printf("%hu ", s.st_nlink);
    printf("%s ", getpwuid(s.st_uid)->pw_name);
    printf("%s ", getgrgid(s.st_gid)->gr_name);
    printf("%lld ", s.st_size);
    printf("%ld ", s.st_birthtimespec.tv_sec);

    
}


void printdir(char *dir, int depth, char f[])
{
    // printf("%d\n\n", f);
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if((dp = opendir(dir)) == NULL)
    {
        fprintf(stderr, "cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    
    while((entry = readdir(dp)) != NULL)
    {
        lstat(entry->d_name, &statbuf);
        if(S_ISDIR(statbuf.st_mode))
        {
            if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
                continue;
            if (entry->d_name[0] == '.' && (f[1] == '0')){
                continue;
            }
            if (f[3] == '1'){
                printf("%llu ", entry->d_ino);
            }
            if (f[0] == '1'){
                get_fir(statbuf);
            }
            printf("%*s%s/\n", depth, "", entry->d_name); // 输出目录
            if (f[2] == '1'){
                printdir(entry->d_name, depth+4, f); // 递归目录下的
            }
            
        }
        else {
            if (entry->d_name[0] == '.' && (f[1] == '0')){
                continue;
            }
            if (f[3] == '1'){
                printf("%llu ", entry->d_ino);
            }
            if (f[0] == '1'){
                get_fir(statbuf);
            }
            printf("%*s%s\n", depth, "", entry->d_name); // 输出文件
        }
        
    }
    
    chdir("..");
    closedir(dp);
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
        }
        else {
            mode = argv[2];
            f = 1;
        }
    }
    char fs[4];
    if (f){
        for (int i = 0; i < 4; i++)fs[i] = '0';
        for (int p = 1; mode[p] != '\0'; p++){
            // printf("%c\n", mode[p]);
            if (mode[p] == 'l'){
                fs[0] = '1';
            }
            else if (mode[p] == 'a'){
                fs[1] = '1';
            }
            else if (mode[p] == 'R'){
                fs[2] = '1';
            }
            else if (mode[p] == 'i'){
                fs[3] = '1';
            }
        }
    }
    
    // printf("%s\n", fs);
    // printf("%s\n", dir);
    printdir(dir, 0, fs);
    exit(0);
}
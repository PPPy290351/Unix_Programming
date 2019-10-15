#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
    if (argc >= 2)
    {
        DIR* pDir = opendir(argv[1]);
        if(pDir != NULL)
        {
            struct dirent* pEntry = NULL;
            while((pEntry = readdir(pDir)) != NULL)
            {
                printf("inode:%ld name:%s\n",pEntry->d_ino ,pEntry->d_name);
            }
        }
        closedir(pDir);
    }
    else
    {
        puts("process terminate");
    }
    exit(0);
}
/*
output:$
inode:2104032 name:hyper
inode:2100785 name:access
inode:2104030 name:hello
inode:2104040 name:access.c
inode:2104260 name:readdir.c
*/

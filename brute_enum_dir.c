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
        struct stat st;
        if(pDir != NULL)
        {
            struct dirent* pEntry = NULL;
            struct dirent* pSubtry = NULL;
            struct dirent* pSubFd = NULL;
            while((pEntry = readdir(pDir)) != NULL)
            {
                if(strcmp(pEntry->d_name, ".") != 0 && strcmp(pEntry->d_name, "..") != 0){
                    char directory[50] = ""; // set root dir
                    strcat(directory,pEntry->d_name);
                    stat(directory, &st);
                    if((st.st_mode & S_IFMT) == S_IFDIR){
                        DIR* subDir = opendir(directory);
                        char rbp_directory[50] = "";
                        strcpy(rbp_directory, directory);
                        // printf("1. Origin: %s, After: %s\n",directory,rbp_directory);
                        while((pSubtry = readdir(subDir)) != NULL)
                        {
                            // printf("2. Origin: %s, After: %s\n",directory,rbp_directory);
                            if(strcmp(pSubtry->d_name, ".") != 0 && strcmp(pSubtry->d_name, "..") != 0){
                                if(strcmp(pSubtry->d_name,"fd") == 0){
                                    strcat(directory,pSubtry->d_name);
                                    lstat(directory, &st);
                                    if((st.st_mode & S_IFMT) == S_IFDIR){
                                        DIR* tpDir = opendir(directory);
                                        while((pSubFd = readdir(tpDir)) != NULL)
                                        {
                                            if(strcmp(pSubFd->d_name, ".") != 0 && strcmp(pSubFd->d_name, "..") != 0){
                                                printf("inode:%ld name:%s\n",pSubFd->d_ino ,pSubFd->d_name);
                                            }
                                        }
                                    }
                                }
                            }
                            memset (directory, 0, 50);
                            strcpy(directory, rbp_directory);
                            strcat(directory, "/");
                        }
                    }
                }
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

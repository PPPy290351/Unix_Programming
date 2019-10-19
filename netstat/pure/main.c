#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

char* searchFd(char*, int);
struct ProcNet{
    int local_port;
    int remote_port;
    char* local_address;
    char* remote_address;
    int inode;
    char* process;
} tucdp4,tucdp6;
int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("%-40s%-40s%-40s%-40s%-40s%-40s\n","Type","Local Addr","Local Port","Remort Addr","Remote Port","PID/CMD");
        FILE* fd;
        struct in_addr sa; 
        size_t numbytes;
        DIR* pDir = opendir("/proc/net");
        if(pDir != NULL)
        {
            struct dirent* pEntry = NULL;
            while((pEntry = readdir(pDir)) != NULL)
            {
                if(strcmp(pEntry->d_name,"tcp") == 0 || strcmp(pEntry->d_name,"udp") == 0 || strcmp(pEntry->d_name,"tcp6") == 0 || strcmp(pEntry->d_name,"udp6") == 0)
                {
                    char prefix[] = "/proc/net/";
                    fd = fopen(strcat(prefix,pEntry->d_name), "r");
                    if(fd < 0){
                        perror("open()");
                        exit(EXIT_FAILURE);
                    }
                    ssize_t read;
                    char* line = NULL;
                    int ignore = 0;
                    while((read = getline(&line, &numbytes, fd)) != -1){
                        if(ignore == 0){
                            ignore++;
                            continue;
                        }
                        if(strcmp(pEntry->d_name,"tcp") == 0){
                            char * pch;
                            pch = strtok (line," :");
                            int index = 0;
                            while (pch != NULL)
                            {
                                switch(index){
                                    case 1:
                                        sa.s_addr = (int)strtol(pch, NULL, 16);
                                        char strA[20];
                                        inet_ntop(AF_INET, &sa.s_addr, strA, sizeof strA);
                                        tucdp4.local_address = strA;
                                        break;
                                    case 2:
                                        tucdp4.local_port = (int)strtol(pch, NULL, 16);
                                        break;
                                    case 3:
                                        sa.s_addr = (int)strtol(pch, NULL, 16);
                                        char strB[20];
                                        inet_ntop(AF_INET, &sa.s_addr, strB, sizeof strB);
                                        tucdp4.remote_address = strB;
                                        break;
                                    case 4:
                                        tucdp4.remote_port = (int)strtol(pch, NULL, 16);
                                        break;
                                    case 13:
                                        tucdp4.inode = (int)strtol(pch, NULL, 10);
                                        tucdp4.process = searchFd("/proc",tucdp4.inode);
                                        break;
                                }
                                pch = strtok (NULL, " :");
                                index++;
                            }
                            printf("%-40s%-40s%-40d%-40s%-40d%-40s\n","tcp",tucdp4.local_address,tucdp4.local_port,tucdp4.remote_address,tucdp4.remote_port,tucdp4.process);
                        }else if(strcmp(pEntry->d_name,"udp") == 0){
                            char * pch;
                            pch = strtok (line," :");
                            int index = 0;
                            while (pch != NULL)
                            {
                              switch(index){
                                    case 1:
                                        sa.s_addr = (int)strtol(pch, NULL, 16);
                                        char strA[20];
                                        inet_ntop(AF_INET, &sa.s_addr, strA, sizeof strA);
                                        tucdp4.local_address = strA;
                                        break;
                                    case 2:
                                        tucdp4.local_port = (int)strtol(pch, NULL, 16);
                                        break;
                                    case 3:
                                        sa.s_addr = (int)strtol(pch, NULL, 16);
                                        char strB[20];
                                        inet_ntop(AF_INET, &sa.s_addr, strB, sizeof strB);
                                        tucdp4.remote_address = strB;
                                        break;
                                    case 4:
                                        tucdp4.remote_port = (int)strtol(pch, NULL, 16);
                                        break;
                                    case 13:
                                        tucdp4.inode = (int)strtol(pch, NULL, 10);
                                        tucdp4.process = searchFd("/proc",tucdp4.inode);
                                        break;
                                }
                              pch = strtok (NULL, " :");
                              index++;
                            }
                            printf("%-40s%-40s%-40d%-40s%-40d%-40s\n","udp",tucdp4.local_address,tucdp4.local_port,tucdp4.remote_address,tucdp4.remote_port,tucdp4.process);
                        }else if(strcmp(pEntry->d_name,"tcp6") == 0){
                            char * pch;
                            pch = strtok (line," :");
                            int index = 0;
                            while (pch != NULL)
                            {
                              switch(index){
                                    case 1:
                                        sa.s_addr = (int)strtol(pch, NULL, 16);
                                        char strA[50];
                                        inet_ntop(AF_INET6, &sa.s_addr, strA, sizeof strA);
                                        tucdp6.local_address = strA;
                                        break;
                                    case 2:
                                        tucdp6.local_port = (int)strtol(pch, NULL, 16);
                                        break;
                                    case 3:
                                        sa.s_addr = (int)strtol(pch, NULL, 16);
                                        char strB[50];
                                        inet_ntop(AF_INET6, &sa.s_addr, strB, sizeof strB);
                                        tucdp6.remote_address = strB;
                                        break;
                                    case 4:
                                        tucdp6.remote_port = (int)strtol(pch, NULL, 16);
                                        break;
                                    case 13:
                                        tucdp6.inode = (int)strtol(pch, NULL, 10);
                                        tucdp6.process = searchFd("/proc",tucdp6.inode);
                                        break;
                                }
                              pch = strtok (NULL, " :");
                              index++;
                            }
                            printf("%-40s%-40s%-40d%-40s%-40d%-40s\n","tcp6",tucdp6.local_address,tucdp6.local_port,tucdp6.remote_address,tucdp6.remote_port,tucdp6.process);
                        }else if(strcmp(pEntry->d_name,"udp6") == 0){
                            char * pch;
                            pch = strtok (line," :");
                            int index = 0;
                            while (pch != NULL)
                            {
                              switch(index){
                                    case 1:
                                        sa.s_addr = (int)strtol(pch, NULL, 16);
                                        char strA[50];
                                        inet_ntop(AF_INET6, &sa.s_addr, strA, sizeof strA);
                                        tucdp6.local_address = strA;
                                        break;
                                    case 2:
                                        tucdp6.local_port = (int)strtol(pch, NULL, 16);
                                        break;
                                    case 3:
                                        sa.s_addr = (int)strtol(pch, NULL, 16);
                                        char strB[50];
                                        inet_ntop(AF_INET6, &sa.s_addr, strB, sizeof strB);
                                        tucdp6.remote_address = strB;
                                        break;
                                    case 4:
                                        tucdp6.remote_port = (int)strtol(pch, NULL, 16);
                                        break;
                                    case 13:
                                        tucdp6.inode = (int)strtol(pch, NULL, 10);
                                        tucdp6.process = searchFd("/proc",tucdp6.inode);
                                        break;
                                }
                              pch = strtok (NULL, " :");
                              index++;
                            }
                            printf("%-40s%-40s%-40d%-40s%-40d%-40s\n","udp6",tucdp6.local_address,tucdp6.local_port,tucdp6.remote_address,tucdp6.remote_port,tucdp6.process);
                        }
                    }
                    fclose (fd);
                }
            }
        }
        closedir(pDir);
    }
    else if(argc >= 2){
        if(strcmp(argv[1],"-t") == 0){
            FILE* fd;
            fd = fopen("/proc/net/tcp", "r");
            if(fd < 0){
                perror("open()");
                exit(EXIT_FAILURE);
            }
            struct in_addr sa; 
            size_t numbytes;
            ssize_t read;
            char* line = NULL;
            int ignore = 0;
            while((read = getline(&line, &numbytes, fd)) != -1){
                if(ignore == 0){
                    ignore++;
                    continue;
                }
                char * pch;
                pch = strtok (line," :");
                int index = 0;
                while (pch != NULL)
                {
                    switch(index){
                        case 1:
                            sa.s_addr = (int)strtol(pch, NULL, 16);
                            char strA[20];
                            inet_ntop(AF_INET, &sa.s_addr, strA, sizeof strA);
                            tucdp4.local_address = strA;
                            break;
                        case 2:
                            tucdp4.local_port = (int)strtol(pch, NULL, 16);
                            break;
                        case 3:
                            sa.s_addr = (int)strtol(pch, NULL, 16);
                            char strB[20];
                            inet_ntop(AF_INET, &sa.s_addr, strB, sizeof strB);
                            tucdp4.remote_address = strB;
                            break;
                        case 4:
                            tucdp4.remote_port = (int)strtol(pch, NULL, 16);
                            break;
                        case 13:
                            tucdp4.inode = (int)strtol(pch, NULL, 10);
                            tucdp4.process = searchFd("/proc",tucdp4.inode);
                            break;
                    }
                    pch = strtok (NULL, " :");
                    index++;
                }
                if(argv[2] != NULL){
                    char *loc = strstr(tucdp4.process, argv[2]);
                    if(loc == NULL){
                        pch = strtok (NULL, " :");
                        continue;
                    }
                }
                printf("%-40s%-40s%-40d%-40s%-40d%-40s\n","tcp",tucdp4.local_address,tucdp4.local_port,tucdp4.remote_address,tucdp4.remote_port,tucdp4.process);
            }
        }else if(strcmp(argv[1],"-u") == 0){
            FILE* fd;
            fd = fopen("/proc/net/udp", "r");
            if(fd < 0){
                perror("open()");
                exit(EXIT_FAILURE);
            }
            struct in_addr sa; 
            size_t numbytes;
            ssize_t read;
            char* line = NULL;
            int ignore = 0;
            while((read = getline(&line, &numbytes, fd)) != -1){
                if(ignore == 0){
                    ignore++;
                    continue;
                }
                char * pch;
                pch = strtok (line," :");
                int index = 0;
                while (pch != NULL)
                {
                    switch(index){
                        case 1:
                            sa.s_addr = (int)strtol(pch, NULL, 16);
                            char strA[20];
                            inet_ntop(AF_INET, &sa.s_addr, strA, sizeof strA);
                            tucdp4.local_address = strA;
                            break;
                        case 2:
                            tucdp4.local_port = (int)strtol(pch, NULL, 16);
                            break;
                        case 3:
                            sa.s_addr = (int)strtol(pch, NULL, 16);
                            char strB[20];
                            inet_ntop(AF_INET, &sa.s_addr, strB, sizeof strB);
                            tucdp4.remote_address = strB;
                            break;
                        case 4:
                            tucdp4.remote_port = (int)strtol(pch, NULL, 16);
                            break;
                        case 13:
                            tucdp4.inode = (int)strtol(pch, NULL, 10);
                            tucdp4.process = searchFd("/proc",tucdp4.inode);
                            break;
                    }
                    pch = strtok (NULL, " :");
                    index++;
                }
                if(argv[2] != NULL){
                    char *loc = strstr(tucdp4.process, argv[2]);
                    if(loc == NULL){
                        pch = strtok (NULL, " :");
                        continue;
                    }
                }
                printf("%-40s%-40s%-40d%-40s%-40d%-40s\n","udp",tucdp4.local_address,tucdp4.local_port,tucdp4.remote_address,tucdp4.remote_port,tucdp4.process);
            }
        }else{
            printf("Usage: [-t | -u][filter]\n");
        }
    }else{
        puts("process terminate");
    }
    exit(0);
}

char* searchFd(char* dir, int from_inode)
{
    char* pid;
    DIR* pDir = opendir(dir);
        char buf[30];
        struct stat st;
        if(pDir != NULL)
        {
            struct dirent* pEntry = NULL;
            struct dirent* pSubtry = NULL;
            struct dirent* pSubFd = NULL;
            while((pEntry = readdir(pDir)) != NULL)
            {
                if(strcmp(pEntry->d_name, ".") != 0 && strcmp(pEntry->d_name, "..") != 0){
                    char directory[30] = "/proc/";
                    strcat(directory,pEntry->d_name);
                    pid = pEntry->d_name;
                    stat(directory, &st);
                    if((st.st_mode & S_IFMT) == S_IFDIR){
                        DIR* subDir = opendir(directory);
                        char rbp_directory[30] = ""; 
                        strcpy(rbp_directory, directory);
                        while((pSubtry = readdir(subDir)) != NULL)
                        {
                            if(strcmp(pSubtry->d_name, ".") != 0 && strcmp(pSubtry->d_name, "..") != 0){
                                if(strcmp(pSubtry->d_name,"fd") == 0){
                                    strcat(directory,pSubtry->d_name);
                                    lstat(directory, &st);
                                    if((st.st_mode & S_IFMT) == S_IFDIR){
                                        DIR* tpDir = opendir(directory);
                                        char tmp[30];
                                        while((pSubFd = readdir(tpDir)) != NULL)
                                        {
                                            if(strcmp(pSubFd->d_name, ".") != 0 && strcmp(pSubFd->d_name, "..") != 0){
                                                memset (tmp, 0, 30);
                                                strcat(tmp,directory);
                                                strcat(tmp,"/");
                                                strcat(tmp,pSubFd->d_name);
                                                readlink(tmp,buf,sizeof(buf));
                                                char race[7];
                                                memcpy(race,buf,6);
                                                race[6] = '\0';
                                                if(strcmp(race,"socket") == 0){
                                                    char inode_buf[20];
                                                    sscanf(buf, "%*[^:]:%s", inode_buf);
                                                    char* tmp = inode_buf;
                                                    tmp++;
                                                    tmp[strlen(tmp)-1] = 0;
                                                    int inode = (int) strtol(tmp, (char **)NULL, 10);
                                                    if(from_inode == inode)
                                                    {
                                                        FILE* fp;
                                                        char cmdLLine[20] = "";
                                                        char retValue[30] = "";
                                                        strcat(cmdLLine,rbp_directory);
                                                        strcat(cmdLLine,"/cmdline");
                                                        fp = fopen(cmdLLine, "r");
                                                        if(fp < 0){
                                                            perror("open()");
                                                            exit(EXIT_FAILURE);
                                                        }
                                                        ssize_t output;
                                                        size_t numbytes;
                                                        char* cmd = NULL;
                                                        output = getline(&cmd, &numbytes, fp);
                                                        if(strlen(pid) + strlen(cmd) + sizeof(char) >= sizeof(retValue)){
                                                            cmd[strlen(cmd)-5] = 0;
                                                        }
                                                        strcat(retValue, pid);
                                                        strcat(retValue, cmd);
                                                        char* result = retValue;
                                                        fclose (fp);
                                                        return result;
                                                    }
                                                }
                                                memset (buf, 0, 30);
                                            }
                                        }
                                        closedir(tpDir);
                                    }
                                }
                            }
                            memset (directory, 0, 30);
                            strcpy(directory, rbp_directory);
                            strcat(directory, "/");
                        }
                        closedir(subDir);
                    }
                }
            }
        }
        closedir(pDir);
}

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXARGS 31

int main(int argc, char* argv[])
{
    int argNum = argc;
    int flag_mod = 0;
    int opt;
    char* libpath;
    char* restricPath;
    char buf[100];
    getcwd(buf, sizeof(buf));
    restricPath = buf;
    libpath = buf;
    printf("Current Work Dir: %s Len: %ld\n", restricPath, strlen(buf));
    argNum--;
    while((opt = getopt(argc, argv, "p:d:-::")) != -1)
    {
        switch(opt){
            case 'p':
                printf("set the path to sandbox.so, default = ./sandbox.so\n");
                printf("you want to set sandbox %s \n",optarg);
                libpath = optarg;
                flag_mod = 1;
                argNum-=2;
                printf("*** Libc location: %s ***\n",libpath);
                break;
            case 'd': // 檔案操作限制目錄
                printf("restrict directory, default = .\n");
                printf("you want to set restrict to %s \n",optarg);
                restricPath = optarg;
                argNum-=2;
                printf("*** Current restrict: %s ***\n",restricPath);
                break;
            default:
                printf("This is command\n");
                //FIXME: need to count down the argNum?
        }
    }
    char* arg[argNum+1];
    if(argNum != 0){
        int index = argc - argNum;
        if(strcmp(argv[index], "--") == 0){
            for(int i=0;i<argNum-1;i++){
                index++;
                arg[i] = argv[index];
            }
        }
    }
    arg[argNum] = NULL;
    //setenv("restrict",restricPath,1); // overwrite mode
    if(flag_mod == 0){
        strcat(libpath, "/sandbox.so\x00\x00");
    }
    char ldpreload[100] = "LD_PRELOAD=";
    char restrictEnv[100] = "restrict=";
    //TODO: use malloc to maintain performance
    strcat(ldpreload, libpath);
    strcat(restrictEnv, restricPath);
    char* envp[] = {ldpreload , restrictEnv, NULL};
    if(arg[0] != NULL){
        execvpe(arg[0], arg, envp);
    }
    return 0;
}

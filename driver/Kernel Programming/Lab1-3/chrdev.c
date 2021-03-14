#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

#define DEV_FILE_NAME "/dev/chishen"

int main(int argc, char const *argv[])
{
    int fd;
    fd = open(DEV_FILE_NAME, O_RDWR);
    if(fd == -1)
        perror("open");
    sleep(3);
    if(close(fd) != 0)
        perror("close");
    return 0;
}

















/* 

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
 
#define DEV_FILE_NAME "/dev/sample"
 
int main(void)
{
        int fd;
        fd = open(DEV_FILE_NAME, O_RDWR);
        if (fd == -1)
                perror("open");
        sleep(3);
        if (close(fd) != 0)
                perror("close");
        return 0;
}

*/
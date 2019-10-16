#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // for standard-IO
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char* argv[]){
    int fd;
    int numbytes;
    //char path[] = "path/to/file";
    char buf[256];

    if(argc < 2){
        exit(EXIT_FAILURE);
    }

    /*
     * O_CREAT: if file missing, create one
     * O_RDONLY: open file with read-only mode
     */
    fd = open(argv[1], O_CREAT | O_RDONLY, 0644);
    if(fd < 0){
        perror("open()");
        exit(EXIT_FAILURE);
    }

    memset(buf, 0x00, 256);
    while((numbytes = read(fd, buf, 255)) > 0){
        //printf("%d bytes read: %s", numbytes, buf);
        printf("%s", buf);
        memset(buf, 0x00, 256);
    }
    close (fd);
    exit(EXIT_SUCCESS);
}
/*
read some tcp/udp data
sl  local_address rem_address   st tx_queue rx_queue tr tm->when retrnsmt   uid  timeout inode ref pointer drops
[format like this]
*/

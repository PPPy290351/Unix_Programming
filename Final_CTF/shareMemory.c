#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXBUF 2048
#define PERMS 0600

int getflag() {
    key_t key;
    int shmid;
    char* shm;
    key = 0x12345678;
    if ((shmid = shmget(key, MAXBUF+1, 0400)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((shm = shmat(shmid, NULL, SHM_RDONLY)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }
    
    printf("%s ", shm);
    return 0;
}

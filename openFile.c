#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
   if (argc < 2) {
       printf("Usage: ./test filename\n");
       exit(1);
   }
   if (access(argv[1], F_OK) == -1) {
       puts("File not exists!");
       exit(2);
   }
   if (access(argv[1], R_OK) == -1)
       puts("You can't read the file!");
   else
       if (access(argv[1], R_OK | W_OK) != -1)
           puts("You can read and write the file");
       else
           puts("You can read the file");
   if(open(argv[1], O_RDONLY) < 0)
           puts("Open file failed");
   else
	puts("Open file success");

   exit(0);
}
/*
This Program > access and open files
-rw-r--r-- 1 root root    /etc/passwd
can read & open success
-rw-r----- 1 root shadow  /etc/shadow
can not read & open failed
*/

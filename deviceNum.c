#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <stdlib.h>
#include <sys/stat.h> // struct stat
#include <stdio.h>

int main(int argc, char *argv[]) {
    int i;
    struct stat buf;
    for (i = 1; i < argc; i++) {
        printf("%s: ", argv[i]);
        if (stat(argv[i], &buf) < 0) {
            puts("stat error");
            continue;
        }
        printf("EveryFile has st_dev= Major:%d/Minor:%d", major(buf.st_dev), minor(buf.st_dev));
        if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)) {
            printf("\nAlso is (%s) -> rdev = %d/%d", // Only device files have rdev numbers
            (S_ISCHR(buf.st_mode)) ? "character" : "block", // true: character , false: block
            major(buf.st_rdev), minor(buf.st_rdev));
        }
        printf("\n-------------\n");
    }
    exit(0);
}

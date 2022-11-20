#include <stdio.h>
#include <sys/stat.h>
#include "constants.h"

int main(int argc, char **argv) {
    if (argc < MIN_ARGS_REQUIRED) {
        printf("%s\n", NO_FILE_PATH_PROVIDED_MSG);
        return 1;
    }
    
    struct stat fileInfo;
    if (stat(argv[1], &fileInfo) < 0) {
        printf("%s\n", FILE_NOT_EXISTS_MSG);
        return 1;
    }

    if (!(fileInfo.st_mode & S_IXUSR)) {
        if (chmod(argv[1], fileInfo.st_mode | S_IXUSR) < 0) {
            fprintf(stderr, "Could not add \'+x\' mode to file \'%s\'\n", argv[1]);
        }
    } 

    return 0;
}
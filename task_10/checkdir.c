#include <stdio.h>
#include <sys/stat.h>
#include "constants.h"

void printDirectoryInfo(const char* path, const struct stat fileInfo);

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

    if (!(S_ISDIR(fileInfo.st_mode))) {
        printf("%s\n", FILE_NOT_DIR_MSG);
        return 1;
    }

    printDirectoryInfo(argv[1], fileInfo);

    if (!(fileInfo.st_mode & S_IWUSR)) {
        if (chmod(argv[1], fileInfo.st_mode | S_IWUSR) < 0) {
            fprintf(stderr, "Could not add \'+w\' mode to file \'%s\'\n", argv[1]);
        }
    } 

    return 0;
}

void printDirectoryInfo(const char* path, const struct stat fileInfo) {
    printf("Information for %s\n", path);
    printf("---------------------------\n");
    printf("File Size: \t\t%lu bytes\n", fileInfo.st_size);
    printf("Number of Links: \t%lu\n", fileInfo.st_nlink);
    printf("File inode: \t\t%lu\n", fileInfo.st_ino);

    printf("File Permissions: \t");
    printf("d");
    printf( (fileInfo.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileInfo.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileInfo.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileInfo.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileInfo.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileInfo.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileInfo.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileInfo.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileInfo.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");
}
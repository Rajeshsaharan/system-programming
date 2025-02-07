#include <stdio.h>
#include "error_function.h"
#include <sys/types.h> //system type defined
#include <fcntl.h>     // system call for open and close read and write
#include <sys/stat.h>  //for file premission rw-rw-rw
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#define BUF_SIZE 500

int main(int argc, char *argv[])
{
    int inputFd, outputFd, openFlags;
    ssize_t numRead;
    char buf[BUF_SIZE];
    if (argc != 3 || strcmp(argv[1], "--help") == 0)
    {
        printf("%d\n", argc == 3);
        // we are giving useage of this program
        usageError("%d old-file new-file copy command\n", argc);
    }

    // openflags for read write and truncate
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    // permission for file 0666;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
     inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
    {
        errExit("opening file %s", argv[1]);
    }
    outputFd = open(argv[2], openFlags, mode);
    if (outputFd == -1)
    {
        errExit("opening file %s", argv[2]);
    }
    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
    {
        if (write(outputFd, buf, numRead) != numRead)
        {
            fatal("couldn't write whole buffer");
        }
    }

    if (numRead == -1)
    {
        errExit("read");
    }

    if (close(inputFd) == -1)
    {
        errExit("close input");
    }

    if (close(outputFd) == -1)
    {
        errExit("close output");
    }
    exit(EXIT_SUCCESS);
    return 0;
}
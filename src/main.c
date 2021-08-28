#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../incl/commentmyccode.h"
#include <ctype.h>
#include <errno.h> // for errno
#include <string.h> // for strerror
#include <sys/stat.h> // for mkdir

/*
** Config file in home directory .CommentMyCCode/config
**
**/

int main(int argc, char **argv)
{
    int     fd;
    int     fd_extra;
    int     fd_commented;
    int     comment_ret;
    int     term;

    if (argc != 2)
    {
        printf("Error: Wrong amount of arguments supplied. Run the program as follows:\n./CommentMyCCode [file_to_comment.c]\n");
        return (-1);
    }
    // STEP 1: Open the file to be commented twice
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Error: %s (%s)\n", strerror(errno), argv[1]);
        return (-1);
    }

    fd_extra = open(argv[1], O_RDONLY);
    if (fd_extra == -1)
    {
        printf("Error: %s (%s)\n", strerror(errno), argv[1]);
        return (-1);
    }
    // STEP 2: Initialize the program, open new file to be commented
    fd_commented = init(argv[1]);
    if (fd_commented == -1)
        return (-1);

    // STEP 3: Find which lines contain function prototypes and comment them
    comment_ret = comment_file(fd, fd_extra, fd_commented);
    if (comment_ret == -1)
    {
        terminate(fd, fd_extra, fd_commented);
        return (-1);
    }
 
    // STEP 4: Terminate the program, close the open file desciptors
    term = terminate(fd, fd_extra, fd_commented);
    if (term == -1)
        return (-1);
    return (0);
}

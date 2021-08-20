#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../incl/commentmyccode.h"
#include <ctype.h>
#include <errno.h> // for errno
#include <string.h> // for strerror
//#include <sys/types.h>
#include <sys/stat.h> // for mkdir

/*
** Config file in home directory .CommentMyCCode/config
**
**/

int main(int argc, char **argv)
{
    char    *line;
    int     fd;
    int     result;

    // STEP 1: Parse the config file
    //  Parse the config file.
    //  Contains Info on which folder to comment all files.
    //  Also the comment format can be found there
    //  Only comment .c files
    //

    if (argc < 2)
    {
        printf("Error: No argument supplied\n");
        return (1);
    }

    // STEP 2: Open a file specified in the config
    fd = open(argv[1], O_RDONLY);

    // STEP 3: Create hidden directory if it doesn't exists yet
    if (mkdir(".commentmyccode/", 0775) == -1)
        printf("Error: %s %s\n", ".commentmyccode/ -->", strerror(errno));

    // STEP 4: Create a new file inside the hidden direcory to append the comments to.
    char *new_file_name = ft_strjoin(".commentmyccode/commented_",  argv[1]);
    printf("new_file_name = |%s|\n", new_file_name);
    int fd_commented = open(new_file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
    if (fd_commented == -1)
        printf("Opening %s failed: %s\n", new_file_name, strerror(errno));
    if (access(new_file_name, F_OK) == 0)
    {
        printf("%s already exists. Deleting and creating new one", new_file_name);
    }
    printf("fd_commented = %d\n", fd_commented);
    free(new_file_name);

    // STEP 5: Find which lines contain function prototypes
    comment_file(fd);
    
    // STEP 6: Append the comment in place

    result = get_next_line(fd, &line);
    //printf("line = %s\n", line);
    //printf("result = %d\n", result);
    free(line);
    close(fd);
    close(fd_commented);
    return (0);
}

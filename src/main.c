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
        return (-1);
    }

    // STEP 2: Check whether the config file exists
    //int acces = access("/home/hilmi/Desktop/codam/curriculum/CommentMyCCode/src/main.c", F_OK);
    char *home = getenv("HOME");
    if (home == NULL)
    {
        printf("Error: Can't find HOME environment variable\n");
        return (-1);
    }
    printf("HOME=%s\n", home);
    char *path_to_config = ft_strjoin(home, "/.commentmyccode/config");
    int access_ret = access(path_to_config, F_OK);
    printf("access = %d\n", access_ret);
    if (access_ret != 0)
    {
        printf("Error: ~/.commentmyccode/config doesn't exist\n");
        return (-1);
    }
    free(path_to_config);

    // STEP 3: Open a file specified in the config
    fd = open(argv[1], O_RDONLY);

    // STEP 4: Create hidden directory if it doesn't exists yet
    if (mkdir(".commentmyccode/", 0775) == -1)
        printf("Error: %s %s\n", ".commentmyccode/ -->", strerror(errno));

    // STEP 5: Create a new file inside the hidden directory to append the comments to.
    char *new_file_name = ft_strjoin(".commentmyccode/commented_",  argv[1]);
    printf("new_file_name = |%s|\n", new_file_name);
    int fd_commented = open(new_file_name, O_RDWR | O_TRUNC | O_CREAT | O_APPEND, 0644);
    if (fd_commented == -1)
        printf("Opening %s failed: %s\n", new_file_name, strerror(errno));
    printf("fd_commented = %d\n", fd_commented);
    free(new_file_name);

    // STEP 6: Find which lines contain function prototypes
    comment_file(fd, fd_commented);
    
    // STEP 7: Append the comment in place
    result = get_next_line(fd, &line);
    //printf("line = %s\n", line);
    //printf("result = %d\n", result);
    free(line);
    close(fd);
    close(fd_commented);
    return (0);
}

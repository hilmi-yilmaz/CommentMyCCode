#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../incl/commentmyccode.h"
#include <ctype.h>

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

    // STEP 3: Create a new file to append the comments to.
    char *new_file_name = ft_strjoin("commented_",  argv[1]);
    printf("new_file_name = |%s|\n", new_file_name);
    free(new_file_name);

    // STEP 3: Find which lines contain function prototypes
    comment_file(fd);
    
    // STEP 4: Append the comment in place

    result = get_next_line(fd, &line);
    //printf("line = %s\n", line);
    //printf("result = %d\n", result);
    free(line);
    close(fd);
    return (0);
}

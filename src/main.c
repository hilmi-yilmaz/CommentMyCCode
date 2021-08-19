#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../incl/get_next_line.h"
#include <ctype.h>

/*
** Config file in home directory .CommentMyCCode/config
**
**/


/*
** Function format:
** [type][spaces/tabs][dereference operator (*)][function name][ ( ][arguments][ ) ][\n][{]
** This function checks first whether the first character on the line is a letter.
** Afterwards is checks for ';'.
** If first character is a letter (not a space etc) AND no ';' present in line
** then that line is a function prototype.
*/

int     check_functions(char *line)
{
    int  i;

    i = 0;
    if (line[i] == '{')
        return (1);
    if (!(isalpha(line[i])))
        return (0);
    while (line[i] != '\0')
    {
        if (line[i] == ';')
            return (0);
        i++;
    }
    return (1);
}

int     comment_file(int fd)
{
    int     i;
    int     res;
    char    *line;
    int     check;
    int     flag;

    i = 1; // represents the line number in the file
    res = 1;
    line = NULL;
    flag = 0;
    check = 0;
    while (res > 0)
    {
        res = get_next_line(fd, &line);
        if (check == 1)
            flag = 1;
        check = check_functions(line);
        //printf("check = %d\n", check);
        if (check == 1)
        {
            //printf("%s\n", line);
            if (flag == 1)
            {
                printf("%s\n", line);
                flag = 0;
                check = 0;
                //if (line[0] == '{')
                    printf("line number = %d\n", i - 1);
            }
        }
        free(line);
        line = NULL;
        i++;
    }
    return (0);
}

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
        printf("Error: No argument supplied");
        return (1);
    }

    // STEP 2: Open a file specified in the config
    fd = open(argv[1], O_RDONLY);

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

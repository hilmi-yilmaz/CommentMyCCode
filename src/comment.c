#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for write
#include "../incl/commentmyccode.h"

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

int     comment_file(int fd, int fd_commented)
{
    int     i;
    int     res;
    int     write_res;
    char    *line;
    char    *function_name;
    int     check;
    int     flag;
    t_list  *list;

    i = 1; // represents the line number in the file
    res = 1;
    line = NULL;
    flag = 0;
    check = 0;
    while (res > 0)
    {
        res = get_next_line(fd, &line);
        write_res = write(fd_commented, line, ft_strlen(line));
        write_res = write(fd_commented, "\n", 1);
        if (check == 1)
            flag = 1;
        check = check_functions(line);
        //printf("check = %d\n", check);
        if (check == 1)
        {
            //printf("%s\n", line);
            if (flag == 1)
            {
                //printf("%s\n", line);
                flag = 0;
                check = 0;
                //printf("line number = %d\n", i - 1);
                list = parse_arguments(function_name);
                while (list != NULL)
                {
                    printf("name = |%s|\n", ((t_arguments *)(list->content))->name);
                    list = list->next;
                }
                free(function_name);
                //parse_return_value();
                //place_comment();
            }
            function_name = ft_strdup(line);
        }
        // Append the line to the newly created commented file
        //append_line();

        free(line);
        line = NULL;
        i++;
    }
    return (0);
}

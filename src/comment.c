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

int     check_return(char *line)
{
    int     i;
    char    *return_found;

    i = 0;
    return_found = 0;
    while (line[i] != '\0' && line[i] != 'r')
    {
        if (isspace(line[i]) == 0) // if not a space untill first letter of return ('r')
            return (-1);
        i++;
    }
    printf("(line + i) = |%s|\n", line + i);
    return_found = ft_strnstr(line + i, "return (", ft_strlen(line + i));
    if (return_found == NULL)
        return (-1);
    return (0);
}

int     check_function_line(char *line)
{
    int  i;

    i = 0;
    if (line == NULL)
        return (0);
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

int     check_curly_bracket(char *line)
{
    if (line[0] != '{')
        return (0);
    return (1);
}

int     comment_file(int fd_behind, int fd_ahead, int fd_commented)
{
    
    int         i;
    int         res_behind;
    int         res_ahead;
    char        *line_behind;
    char        *line_ahead;
    int         write_res;
    t_func_data *func_data;

    i = 1;
    res_behind = 1;
    res_ahead = 1;
    line_behind = NULL;
    line_ahead = NULL;
    while (res_behind > 0)
    {
        // Read both lines (line i, i + 1)
        res_ahead = get_next_line(fd_ahead, &line_ahead);
        if (i > 1)
            res_behind = get_next_line(fd_behind, &line_behind);

        // If function is found
        if (check_function_line(line_behind) == 1 && check_curly_bracket(line_ahead) == 1)
        {
            func_data = init_func_data();
            printf("\n%s\n", line_behind);
            parse_arguments(&func_data->args_list, line_behind);
            parse_function_name(&func_data->name, line_behind);
            printf("function_name = |%s|\n", func_data->name);
            print_llist(func_data->args_list);
            parse_return(&func_data->return_data, line_behind);
            printf("return_data type = |%s|\n", func_data->return_data->type);
            free_func_data(func_data);
        }

        if (i > 1)
        {
            write_res = write(fd_commented, line_behind, ft_strlen(line_behind));
            write_res = write(fd_commented, "\n", 1);
        }

        free(line_behind);
        free(line_ahead);
        line_behind = NULL;
        line_ahead = NULL;
        i++;
    }
    return (0);
}

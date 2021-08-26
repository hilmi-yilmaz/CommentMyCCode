#include "../incl/commentmyccode.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void    compress_spaces(char **return_type)
{
    int     i;
    int     len_str;
    char    **splits;

    i = 0;
    len_str = ft_strlen(*return_type);
    while ((*return_type)[i] != '\0')
    {
        if (isspace((*return_type)[i]) != 0) // if space
            (*return_type)[i] = ' ';
        i++;
    }
    splits = ft_split(*return_type, ' ');
    free(*return_type);
    *return_type = join_splits(splits, ' ', len_string_array(splits));
    free_string_array(splits);
}

void    parse_return_type(t_return **return_data, char *line)
{
    int i;
    int j;
    int space;
    int deref;

    i = 0;
    j = 0;
    space = -1;
    deref = -1;
    while (line[j] != '(')
    {
        if (isspace(line[j]) != 0)
            space = j;
        if (line[j] == '*')
            deref = j;
        j++;
    }
    if (deref > space)
        (*return_data)->type = ft_substr(line, 0, deref + 1);
    else
        (*return_data)->type = ft_substr(line, 0, space);
    compress_spaces(&(*return_data)->type);
}

void    parse_return_name(t_return **return_data, char *line)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (line[i] != '\0' && line[i] != '(')
        i++;
    while (line[i + j] != '\0' && line[i + j] != ')')
        j++;
    (*return_data)->name = ft_substr(line, i, j);
    printf("(*return_data)->name = |%s|\n", (*return_data)->name);
}

void    parse_return(t_return **return_data, char *line)
{
    int i;

    i = 0;
    parse_return_type(return_data, line);



}

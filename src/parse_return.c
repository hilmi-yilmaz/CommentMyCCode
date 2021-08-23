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
    *return_type = join_splits(splits, ' ');
    free_string_array(splits);
}

void    parse_return(t_return **return_data, char *line)
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

#include "../incl/commentmyccode.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

int     compress_spaces(char **return_type)
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
    if (splits == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return (-1);
    }
    free(*return_type);
    *return_type = join_splits(splits, ' ', len_string_array(splits));
    if (*return_type == NULL)
    {
        free_string_array(splits);
        return (-1);
    }
    free_string_array(splits);
    return (0);
}

int     parse_return_type(t_return **return_data, char *line)
{
    int i;
    int j;
    int space;
    int deref;
    int ret;

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
    if ((*return_data)->type == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return (-1);
    }
    ret = compress_spaces(&(*return_data)->type);
    if (ret == -1)
        return (-1);
    return (0);
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

int     parse_return(t_return **return_data, char *line)
{
    int ret;

    ret = parse_return_type(return_data, line);
    if (ret == -1)
        return (-1);
    return (0);
}

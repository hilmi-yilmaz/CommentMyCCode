#include "../incl/commentmyccode.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int     get_name(t_arguments *args, char **splits, int total_splits)
{
    args->name = ft_strtrim(splits[total_splits - 1], "*"); // trim allocates new memory, so split can be freed
    if (args->name == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return (-1);
    }
    return (0);
}

int     get_type(t_arguments *args, char **splits, int total_splits)
{
    args->type = join_splits(splits, ' ', total_splits - 1);
    if (args->type == NULL)
        return (-1);
    return (0);
}

void    get_deref_operators(t_arguments *args, char **splits, int total_splits)
{
    while (splits[total_splits - 1][args->deref_operators] == '*')
        args->deref_operators++;
}

int     append_deref_operators_to_type(char **type, int deref_operators)
{
    int     i;
    char    *tmp;
    char    *tmp_type;

    i = 1;
    tmp = malloc(sizeof(*tmp) * (deref_operators + 2));
    if (tmp == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return (-1);
    }
    tmp[0] = ' ';
    tmp_type = *type;
    while (i < deref_operators + 1)
    {
        tmp[i] = '*';
        i++;
    }
    tmp[i] = '\0';
    *type = ft_strjoin(tmp_type, tmp);
    if (*type == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        free_data(2, tmp_type, tmp);
        return (-1);
    }
    free_data(2, tmp_type, tmp);
    return (0);
}


int     get_argument_type_and_name(t_list *args_list, char *line, int len, int count)
{
    char        *arg;
    char        **splits;
    int         total_splits;
    int         ret;
    t_arguments *args;
    t_list      *tmp;

    tmp = NULL;
    args = malloc(sizeof(*args));
    if (args == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return (-1);
    }
    init_args_struct(args);
    arg = ft_substr(line, 0, len);
    if (arg == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        free_data(1, args);
        return (-1);
    }
    splits = ft_split(arg, ' ');
    if (splits == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        //free(args);
        //free(arg);
        free_data(2, args, arg);
        return (-1);
    }
    total_splits = 0;
    while (splits[total_splits] != NULL)
        total_splits++;
    get_deref_operators(args, splits, total_splits);
    ret = get_name(args, splits, total_splits);
    if (ret == -1)
    {
        //free(args);
        //free(arg);
        free_data(2, args, arg);
        free_string_array(splits);
        return (-1);
    }
    ret = get_type(args, splits, total_splits);
    if (ret == -1)
    {
        //free(args);
        //free(arg);
        free_data(2, args, arg);
        free_string_array(splits);
        return (-1);
    }
    if (args->deref_operators > 0)
    {
        ret = append_deref_operators_to_type(&args->type, args->deref_operators);
        if (ret == -1)
        {
            //free(args);
            //free(arg);
            free_data(2, args, arg);
            free_string_array(splits);
            return (-1);
        }
    }
    if (count == 0)
        args_list->content = args;
    else
    {
        tmp = ft_lstnew(args);
        if (tmp == NULL)
        {
            printf("Error: %s\n", strerror(errno));
            //free(arg);
            //free(args);
            free_data(2, args, arg);
            free_string_array(splits);
            return (-1);
        }
        ft_lstadd_back(&args_list, tmp);
    }
    free_string_array(splits);
    free(arg);
    return (0);
}

int     parse_arguments(t_list **args_list, char *line)
{
    int         i;
    int         j;
    int         left_bracket_idx;
    int         right_bracket_idx;
    int         count;
    int         ret;

    i = 0;
    j = 0;
    count = 0;
    left_bracket_idx = -1;
    right_bracket_idx = -1;
    *args_list = ft_lstnew(NULL);
    if (*args_list == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return (-1);
    }
    while (line[i] != '\0' && line[i] != '(')
        i++;
    left_bracket_idx = i;
    i++;
    while (*(line + i + j) != '\0') // loops until the commas
    {
        if (*(line + i + j) == ',' || *(line + i + j) == ')')
        {
            if (*(line + i + j) == ')')
                right_bracket_idx = i + j;
            if ((right_bracket_idx != -1 || left_bracket_idx != -1) && ft_abs(right_bracket_idx - left_bracket_idx) > 1)
            {
                ret = get_argument_type_and_name(*args_list, line + i, j, count);
                if (ret == -1)
                    return (-1);
            }
            i += (j + 1);
            j = 0;
            count++;
            continue ;
        }
        j++;
    }
    return (0);
}

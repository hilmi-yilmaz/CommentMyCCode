#include "../incl/commentmyccode.h"
#include <stdio.h>
#include <stdlib.h>

void    get_name(t_arguments *args, char **splits, int total_splits)
{
    args->name = ft_strtrim(splits[total_splits - 1], "*"); // trim allocates new memory, so split can be freed
}

void    get_type(t_arguments *args, char **splits, int total_splits)
{
    args->type = join_splits(splits, ' ', total_splits - 1);
}

void    get_deref_operators(t_arguments *args, char **splits, int total_splits)
{
    while (splits[total_splits - 1][args->deref_operators] == '*')
        args->deref_operators++;
}

void    append_deref_operators_to_type(char **type, int deref_operators)
{
    int     i;
    char    *tmp;
    char    *tmp_type;

    i = 1;
    tmp = malloc(sizeof(*tmp) * (deref_operators + 2));
    tmp[0] = ' ';
    tmp_type = *type;
    while (i < deref_operators + 1)
    {
        tmp[i] = '*';
        i++;
    }
    tmp[i] = '\0';
    *type = ft_strjoin(tmp_type, tmp);
    free(tmp_type);
    free(tmp);
}


void    get_argument(t_list *args_list, char *line, int len, int count)
{
    char        *arg;
    char        **splits;
    int         total_splits;
    t_arguments *args;

    args = malloc(sizeof(*args));
    init_args_struct(args);

    // Create a substring
    arg = ft_substr(line, 0, len);

    // Split the data by spaces
    splits = ft_split(arg, ' ');

    // Get the latest split, this is the name of the argument
    total_splits = 0;
    while (splits[total_splits] != NULL)
        total_splits++;
    get_deref_operators(args, splits, total_splits);
    get_name(args, splits, total_splits);
    get_type(args, splits, total_splits);
    if (args->deref_operators > 0)
        append_deref_operators_to_type(&args->type, args->deref_operators);

    // Put the struct inside the linked list
    if (count == 0)
        args_list->content = args;
    else
        ft_lstadd_back(&args_list, ft_lstnew(args));
    free_string_array(splits);
    free(arg);
}

void    parse_arguments(t_list **args_list, char *line)
{
    int         i;
    int         j;
    int         left_bracket_idx;
    int         right_bracket_idx;
    int         count;

    i = 0;
    j = 0;
    count = 0;
    left_bracket_idx = -1;
    right_bracket_idx = -1;
    *args_list = ft_lstnew(NULL);
    while (*(line + i) != '(')
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
                get_argument(*args_list, line + i, j, count);
            i += (j + 1);
            j = 0;
            count++;
            continue ;
        }
        j++;
    }
}

#include "../incl/commentmyccode.h"
#include <stdio.h>
#include <ctype.h> //isspace
#include <stdlib.h>

void    get_argument(t_list *list, char *line, int len)
{
    printf("\n-------------------------\nline = |%s|\n", line);
    printf("len = %d\n", len);

    int         i;
    char        *arg;
    char        **splits;
    int         total_splits;
    t_list      *list_element;
    t_arguments *args;

    args = malloc(sizeof(*args));
    init_args_struct(args);

    // find the length of this argument
    i = 0;
    while (line[i] != ',' && line[i] != ')')
        i++;

    // Create a substring
    arg = ft_substr(line, 0, i);
    printf("arg = |%s|\n", arg);

    // Split the data by spaces
    splits = ft_split(arg, ' ');

    // Get the latest split, this is the name of the argument
    total_splits = 0;
    while (splits[total_splits] != NULL)
        total_splits++;

    // Check whether there are dereference operators (*) in the name
    while (splits[total_splits - 1][args->deref_operators] == '*')
        args->deref_operators++;

    args->name = ft_strtrim(splits[total_splits - 1], "*"); // trim allocates new memory, so split can be freed
    

    i = 1;
    args->type = splits[0];
    while (i < total_splits - 1)
    {
        args->type = ft_strjoin(args->type, splits[i]);
        i++;
    }

    printf("Amount of dereference operators = %d\n", args->deref_operators);

    printf("Argument name = |%s|\n", args->name);
    printf("Argument type = |%s|\n", args->type);
    //printf("Address args[0]->name             = %p\n", args->name);
    //printf("Address splits[total_splits - 1] = %p\n", splits[total_splits - 1]);

    int j = 0;
    while (splits[j] != NULL)
    {
        //printf("|%s|\n", splits[j]);
        free(splits[j]);
        j++;
    }
    free(splits);

    // Put the struct inside the linked list
    list_element = ft_lstnew(args);
    ft_lstadd_back(&list, list_element);

    //t_arguments *tester = list_element->content;

    printf("((t_arguments *)list_element->content)->name = %s\n", ((t_arguments *)list_element->content)->name);

    free(arg);
}

t_list *parse_arguments(char *line)
{
    int         i;
    int         j;
    int         k;
    t_list      *list;

    //printf("line = %s\n", line);
    i = 0;
    j = 0;
    k = 0;
    list = ft_lstnew(NULL);
    while (*(line + i) != '(')
        i++;
    i++;
    while (*(line + i + j) != '\0') // loops until the commas
    {
        if (*(line + i + j) == ',' || *(line + i + j) == ')')
        {
            get_argument(list, line + i, j);
            i += (j + 1);
            j = 0;
            continue ;
        }
        j++;
    }
    return (list);
}

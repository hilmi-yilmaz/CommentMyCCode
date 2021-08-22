#include "../incl/commentmyccode.h"
#include <stdio.h>
#include <ctype.h> //isspace
#include <stdlib.h>

void    get_argument(t_list *list, char *line, int len, int count)
{
    int         i;
    char        *arg;
    char        *tmp;        // this will store temp values when joining the splits together for the type
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

    // Check whether there are dereference operators (*) in the name
    while (splits[total_splits - 1][args->deref_operators] == '*')
        args->deref_operators++;

    args->name = ft_strtrim(splits[total_splits - 1], "*"); // trim allocates new memory, so split can be freed
    
    i = 0;
    while (i < total_splits - 1)
    {
        if (i == 0)
            tmp = ft_strdup(splits[i]);
        if (i == total_splits - 2) // if i is equal to last word in type, append nothing
            args->type = ft_strjoin(tmp, "");
        else
            args->type = ft_strjoin(tmp, splits[i + 1]); // else append next
        free(tmp);
        tmp = NULL;
        if (i != total_splits - 2)
            tmp = args->type;
        i++;
    }
    //free(tmp);

    i = 0;
    while (splits[i] != NULL)
    {
        //printf("|%s|\n", splits[j]);
        free(splits[i]);
        i++;
    }
    free(splits);

    // Put the struct inside the linked list
    if (count == 0)
        list->content = args;
    else
        ft_lstadd_back(&list, ft_lstnew(args));

    free(arg);
}

t_list *parse_arguments(char *line)
{
    int         i;
    int         j;
    int         count;
    t_list      *list;

    //printf("line = %s\n", line);
    i = 0;
    j = 0;
    count = 0;
    list = ft_lstnew(NULL);
    while (*(line + i) != '(')
        i++;
    i++;
    while (*(line + i + j) != '\0') // loops until the commas
    {
        if (*(line + i + j) == ',' || *(line + i + j) == ')')
        {
            get_argument(list, line + i, j, count);
            i += (j + 1);
            j = 0;
            count++;
            continue ;
        }
        j++;
    }
    return (list);
}

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
    //printf("arg = |%s|\n", arg);

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
    

    // ATTENTION: this while loop contains leaks because each time new
    // memory allocated but not freed
    i = 1;
    tmp = ft_strdup(splits[0]);
    while (i < total_splits - 1)
    {
        args->type = ft_strjoin(tmp, splits[i]); //strjoin allocates new memory
        free(tmp);
        tmp = NULL;
        tmp = args->type;
        i++;
    }

    int j = 0;
    while (splits[j] != NULL)
    {
        //printf("|%s|\n", splits[j]);
        free(splits[j]);
        j++;
    }
    free(splits);

    // Put the struct inside the linked list
    if (count == 0)
        list->content = args;
    else
        ft_lstadd_back(&list, ft_lstnew(args));

    //print_llist(list);

    //t_arguments *tester = list_element->content;

    //printf("((t_arguments *)list_element->content)->name = %s\n", ((t_arguments *)list_element->content)->name);

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

#include "../incl/commentmyccode.h"
#include <stdio.h>
#include <ctype.h> //isspace
#include <stdlib.h>

void    get_argument(t_arguments *args, char *line, int len)
{
    printf("line = |%s|\n", line);
    printf("len = %d\n", len);

    // find the length of this argument
    int i;

    i = 0;
    while (line[i] != ',' && line[i] != ')')
        i++;

    // Create a substring
    char *arg = ft_substr(line, 0, i);
    printf("arg = |%s|\n", arg);

    // Split the data by spaces
    char **splits = ft_split(arg, ' ');

    // Get the latest split, this is the name of the argument
    int total_splits = 0;
    while (splits[total_splits] != NULL)
        total_splits++;

    args[0].name = splits[total_splits - 1];
    
    // Check whether there are dereference operators (*) in the name
    i = 0;
    while (args[0].name[i] == '*')
        i++;

    printf("Amount of dereference operators = %d\n", i);

    printf("First argument name = |%s|\n", args[0].name);
    printf("Address args[0].name             = %p\n", args[0].name);
    printf("Address splits[total_splits - 1] = %p\n", splits[total_splits - 1]);

    int j = 0;
    while (splits[j] != NULL)
    {
        printf("|%s|\n", splits[j]);
        j++;
    }

    j = 0;
    while (splits[j] != NULL)
    {
        free(splits[j]);
        j++;
    }
    free(splits);

    free(arg);
}

void    parse_arguments(char *line)
{
    int         i;
    int         j;
    int         k;
    t_arguments args[10]; //Max 10 arguments

    //printf("line = %s\n", line);
    i = 0;
    j = 0;
    k = 0;
    while (*(line + i) != '(')
        i++;
    i++;
    while (*(line + i + j) != '\0')
    {
        if (*(line + i + j) == ',' || *(line + i + j) == ')')
        {
            get_argument(args, line + i, j);
            i += (j + 1);
            j = 0;
            continue ;
        }
        j++;
    }
}

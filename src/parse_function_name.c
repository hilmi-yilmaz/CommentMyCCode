#include "../incl/commentmyccode.h"
#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int parse_function_name(char **name, char *line)
{
    int i;
    int j;
    int space;
    int deref;
    int deref_index;

    i = 0;
    j = 0;
    space = -1;
    deref_index = -1;
    deref = 0;
    while (line[i] != '\0' && line[i] != '(')
    {
        if (isspace(line[i]) != 0)
            space = i;
        if (line[i] == '*')
        {
            deref++;
            deref_index = i;
        }
        i++;
    }
    if (space > deref_index)
        *name = ft_substr(line, space + 1, i - space - 1);
    else
        *name = ft_substr(line, deref_index + 1, i - deref_index - 1);
    if (*name == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return (-1);
    }
    return (0);
}

#include "../incl/commentmyccode.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void    parse_return(t_return *return_data, char *line)
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
        return_data->type = ft_substr(line, 0, deref + 1);
    else
        return_data->type = ft_substr(line, 0, space);
}

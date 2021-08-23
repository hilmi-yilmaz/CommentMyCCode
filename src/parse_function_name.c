#include "../incl/commentmyccode.h"
#include <ctype.h>

void    parse_function_name(char **name, char *line)
{
    int i;
    int j;
    int space;

    i = 0;
    j = 0;
    space = -1;
    while (line[i] != '(')
        i++;
    while (j < i)
    {
        if (isspace(line[j]) != 0)
            space = j;
        j++;
    }
    if (space != -1)
        *name = ft_substr(line, space + 1, i - space - 1);
}

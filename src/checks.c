#include <stdlib.h>
#include <ctype.h>
#include "../incl/commentmyccode.h"

int     check_return(char *line)
{
    int     i;
    char    *return_found;

    i = 0;
    return_found = 0;
    while (line[i] != '\0' && line[i] != 'r')
    {
        if (isspace(line[i]) == 0) // if not a space untill first letter of return ('r')
            return (-1);
        i++;
    }
    return_found = ft_strnstr(line + i, "return (", ft_strlen(line + i));
    if (return_found == NULL)
        return (-1);
    return (0);
}

int     check_function_line(char *line)
{
    int  i;

    i = 0;
    if (line == NULL)
        return (0);
    if (!(isalpha(line[i])))
        return (0);
    while (line[i] != '\0')
    {
        if (line[i] == ';')
            return (0);
        i++;
    }
    return (1);
}

int     check_curly_bracket(char *line)
{
    if (line == NULL)
        return (0);
    if (line[0] != '{')
        return (0);
    return (1);
}

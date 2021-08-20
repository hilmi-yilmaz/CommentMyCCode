#include "../incl/commentmyccode.h"
#include <stdio.h>
#include <ctype.h> //isspace

void    get_argument(char *line, int len)
{
    printf("line = |%s|\n", line);
    printf("len = %d\n", len);
}

void    parse_arguments(char *line)
{
    int         i;
    int         j;
    int         k;
   // t_arguments args[10]; //Max 10 arguments

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
            get_argument(line + i, j);
            i += (j + 1);
            j = 0;
            continue ;
        }
        j++;
    }
}

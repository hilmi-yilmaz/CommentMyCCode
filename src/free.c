#include <stdlib.h>
#include <stdarg.h>

void    free_data(int amount, ...)
{
    int     i;
    va_list ap;
    char    *to_be_freed;

    i = 0;
    va_start(ap, amount);
    while (i < amount)
    {
        to_be_freed = va_arg(ap, char *);
        free(to_be_freed);
        i++;
    }
    va_end(ap);
}

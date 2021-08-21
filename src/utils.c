#include <stddef.h>
#include "../incl/commentmyccode.h"

void    init_args_struct(t_arguments *args)
{
    args->type = NULL;
    args->name = NULL;
    args->deref_operators = 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "../incl/commentmyccode.h"

void    init_args_struct(t_arguments *args)
{
    args->type = NULL;
    args->name = NULL;
    args->deref_operators = 0;
}

void    print_llist(t_list *list)
{
    while (list != NULL)
    {
        printf("--------------------------------------------------\n");
        printf("name  = |%s|\n", ((t_arguments *)(list->content))->name);
        printf("type  = |%s|\n", ((t_arguments *)(list->content))->type);
        printf("deref = |%d|\n", ((t_arguments *)(list->content))->deref_operators);
        list = list->next;
    }
}

void    free_arguments(void *args)
{
    free(((t_arguments *)args)->name);
    free(((t_arguments *)args)->type);
    free((t_arguments *)args);
}

void    free_llist(t_list *list)
{
    ft_lstclear(&list, free_arguments);
}

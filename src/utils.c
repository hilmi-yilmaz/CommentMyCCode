#include <stdio.h>
#include <stdlib.h>
#include "../incl/commentmyccode.h"

char    *join_splits(char **splits, char c, int len)
{
    int     i;
    //int     amount_splits;
    char    *joined;
    char    *tmp_space;
    char    *tmp;
    char    c_str[2];

    i = 1;
    //amount_splits = len_string_array(splits);
    c_str[0] = c;
    c_str[1] = '\0';
    tmp = ft_strdup(splits[0]);
    while (i < len)
    {
        tmp_space = ft_strjoin(tmp, c_str);
        free(tmp);
        joined = ft_strjoin(tmp_space, splits[i]);
        free(tmp_space);
        tmp = ft_strdup(joined);
        if (i != len - 1)
            free(joined);
        i++;
    }
    if (len == 1 || len == 0) //len = 0 is the case that we have (...) variadic, in that case also put that in the type
        joined = ft_strdup(splits[0]);
    free(tmp);
    return (joined);
}

void    print_string_array(char **str)
{
    int i;

    i = 0;
    while (str[i] != NULL)
    {
        printf("|%s|\n", str[i]);
        i++;
    }
}

int     len_string_array(char **str)
{
    int i;

    i = 0;
    while (str[i] != NULL)
        i++;
    return (i);
}

void    init_args_struct(t_arguments *args)
{
    args->type = NULL;
    args->name = NULL;
    args->deref_operators = 0;
}

t_return    *init_return_struct(void)
{
    t_return    *return_data;

    return_data = malloc(sizeof(*return_data));
    return_data->name = NULL;
    return_data->type = NULL;
    return_data->deref_operators = 0;
    return (return_data);
}

t_func_data *init_func_data(void)
{
    t_func_data *func_data;

    func_data = malloc(sizeof(*func_data));
    func_data->name = NULL;
    func_data->args_list = NULL;
    func_data->return_data = init_return_struct();
    return (func_data);
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

void    free_func_data(t_func_data *func_data)
{
    free(func_data->name);
    free_llist(func_data->args_list);
    free_return_data(func_data->return_data);
    free(func_data);
}

void    free_return_data(t_return *return_data)
{
    free(return_data->name);
    free(return_data->type);
    free(return_data);
}

void    free_string_array(char **str_arr)
{
    int i;

    i = 0;
    while (str_arr[i] != NULL)
    {
        free(str_arr[i]);
        i++;
    }
    free(str_arr);
}

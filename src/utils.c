#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> //strerror
#include "../incl/commentmyccode.h"

int ft_abs(int a)
{
    if (a < 0)
        return (-a);
    return (a);
}

char    *join_splits(char **splits, char c, int len)
{
    int     i;
    char    *joined;
    char    *tmp_space;
    char    *tmp;
    char    c_str[2];

    i = 1;
    c_str[0] = c;
    c_str[1] = '\0';
    tmp = ft_strdup(splits[0]);
    if (tmp == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return (NULL);
    }
    while (i < len)
    {
        tmp_space = ft_strjoin(tmp, c_str);
        if (tmp_space == NULL)
        {
            printf("Error: %s\n", strerror(errno));
            free(tmp);
            return (NULL);
        }
        free(tmp);
        joined = ft_strjoin(tmp_space, splits[i]);
        if (joined == NULL)
        {
            printf("Error: %s\n", strerror(errno));
            free(tmp_space);
            return (NULL);
        }
        free(tmp_space);
        tmp = ft_strdup(joined);
        if (tmp == NULL)
        {
            printf("Error: %s\n", strerror(errno));
            free(joined);
            return (NULL);
        }
        if (i != len - 1)
            free(joined);
        i++;
    }
    if (len == 1 || len == 0) //len = 0 is the case that we have (...) variadic, in that case also put that in the type
    {    
        joined = ft_strdup(splits[0]);
        if (joined == NULL)
        {
            printf("Error: %s\n", strerror(errno));
            free(tmp);
            return (NULL);
        }
    }
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
    if (return_data == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return (NULL);
    }
    return_data->name = NULL;
    return_data->type = NULL;
    return_data->deref_operators = 0;
    return (return_data);
}

t_func_data *init_func_data(void)
{
    t_func_data *func_data;

    func_data = malloc(sizeof(*func_data));
    if (func_data == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return (NULL);
    }
    func_data->name = NULL;
    func_data->args_list = NULL;
    func_data->return_data = init_return_struct();
    if (func_data->return_data == NULL)
        return (NULL);
    return (func_data);
}

void    print_llist(t_list *list)
{
    while (list != NULL && list->content != NULL)
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
    if (list->content != NULL) // this is the case when no arguments are supplied like this ()
        ft_lstclear(&list, free_arguments);
    else
        free(list);
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

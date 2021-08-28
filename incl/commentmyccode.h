#ifndef COMMENTMYCCODE_H
# define COMMENTMYCCODE_H

# include "../src/libft/libft.h"

typedef struct s_arguments
{
    char    *type;
    char    *name;
    int     deref_operators;

}   t_arguments;

typedef struct s_return
{
    char    *name;
    char    *type;
    int     deref_operators;

}   t_return;

typedef struct s_func_data
{
    char        *name;
    t_return    *return_data;
    t_list      *args_list; //linked list for arguments

}   t_func_data;


/* Initialize */
int     init(char *src_file);
int     check_config(void);
int     create_hidden_dir(void);
int     create_commented_file(char *src_file);


int     check_function_line(char *line);
int     check_curly_bracket(char *line);
int     check_return(char *line);
int     comment_file(int fd_behind, int fd_ahead, int fd_commented);

int     parse_function_name(char **name, char *line);

int     parse_return(t_return **return_data, char *line);
int     parse_return_type(t_return **return_data, char *line);
void    parse_return_name(t_return **return_data, char *line);
int     compress_spaces(char **str);

int     parse_arguments(t_list **args_list, char *line);
int     get_argument(t_list *args, char *line, int len, int count);
int     get_name(t_arguments *args, char **splits, int total_splits);
int     get_type(t_arguments *args, char **splits, int total_splits);
void    get_deref_operators(t_arguments *args, char **splits, int total_splits);
int     append_deref_operators_to_type(char **type, int deref_operators);

/* Terminate */
int     terminate(int fd, int fd_extra, int fd_commented);

/* Utils */
int         ft_abs(int a);
int         len_string_array(char **str);
char        *join_splits(char **splits, char c, int len);
void        print_string_array(char **str);
void        init_args_struct(t_arguments *args);
t_return    *init_return_struct(void);
t_func_data *init_func_data(void);
void        print_llist(t_list *list);
void        free_arguments(void *args);
void        free_llist(t_list *list);
void        free_string_array(char **str_arr);
void        free_func_data(t_func_data *func_data);
void        free_return_data(t_return *return_data);

#endif

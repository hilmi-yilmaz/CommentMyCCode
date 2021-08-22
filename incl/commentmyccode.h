#ifndef COMMENTMYCCODE_H
# define COMMENTMYCCODE_H

# include "../src/libft/libft.h"

typedef struct s_arguments
{
    char    *type;
    char    *name;
    int     deref_operators;

}   t_arguments;


/* Initialize */
int     init(char *src_file);
int     check_config(void);
int     create_hidden_dir(void);
int     create_commented_file(char *src_file);


int     check_functions(char *line);
int     comment_file(int fd, int fd_commented);
t_list  *parse_arguments(char *line);
void    get_argument(t_list *args, char *line, int len, int count);
void    get_name(t_arguments *args, char **splits, int total_splits);
void    get_type(t_arguments *args, char **splits, int total_splits);
void    get_deref_operators(t_arguments *args, char **splits, int total_splits);

/* Terminate */
int     terminate(int fd, int fd_commented);

/* Utils */
void    init_args_struct(t_arguments *args);
void    print_llist(t_list *list);
void    free_arguments(void *args);
void    free_llist(t_list *list);
void    free_string_array(char **str_arr);

#endif

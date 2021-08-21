#ifndef COMMENTMYCCODE_H
# define COMMENTMYCCODE_H

# include "../src/libft/libft.h"

typedef struct s_arguments
{
    char *type;
    char *name;

}   t_arguments;


/* Initialize */
int     init(char *src_file);
int     check_config(void);
int     create_hidden_dir(void);
int     create_commented_file(char *src_file);


int check_functions(char *line);
int comment_file(int fd, int fd_commented);
void parse_arguments(char *line);
void get_argument(t_arguments *args, char *line, int len);

/* Terminate */
int terminate(int fd, int fd_commented);

#endif

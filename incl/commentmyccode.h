#ifndef COMMENTMYCCODE_H
# define COMMENTMYCCODE_H

# include "../src/libft/libft.h"

typedef struct s_arguments
{
    char *type;
    char *name;

}   t_arguments;

int check_functions(char *line);
int comment_file(int fd, int fd_commented);
void parse_arguments(char *line);
void get_argument(char *line, int len);

#endif

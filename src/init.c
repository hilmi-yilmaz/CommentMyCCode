#include <stdlib.h>     //free
#include <sys/stat.h>   //mkdir
#include <errno.h>      //errno
#include <string.h>     //strerror
#include <stdio.h>
#include <unistd.h>     //access
#include <fcntl.h>      //open
#include <sys/types.h>  //opendir

#include "../incl/commentmyccode.h"

/*
** The init program does the following:
** 1: Check for the existence of the .commentmyccode/config file.
** 2: Create .commentmyccode inside the project folder if it doesn't exists yet.
** 3: Create inside the .commentmyccode directory a new file prefixed with commented_.
*/

int init(char *src_file)
{
    int config;
    int hidden_dir;
    int commented_file;

    config = check_config();
    if (config == -1)
        return (-1);

    hidden_dir = create_hidden_dir();
    if (hidden_dir == -1)
        return (-1);

    commented_file = create_commented_file(src_file);
    if (commented_file == -1)
        return (-1);

    return (commented_file); //file descriptor of .commentmyccode/commeted_test.c
}

int check_config(void)
{
    char    *home;
    char    *path_to_config;
    int     access_ret;

    home = getenv("HOME");
    if (home == NULL)
    {
        printf("Error: Can't find HOME environment variable\n");
        printf("HOME is used to check for the existence of your config file inside ~/.commentmyccode/\n");
        return (-1);
    }
    path_to_config = ft_strjoin(home, "/.commentmyccode/config");
    access_ret = access(path_to_config, F_OK);
    if (access_ret != 0)
    {
        printf("Error: %s/.commentmyccode/config doesn't exist\n", home);
        return (-1);
    }
    free(path_to_config);
    return (0);
}

int create_hidden_dir(void)
{
    int mkdir_ret;

    mkdir_ret = mkdir(".commentmyccode/", 0755); // no error message, because when return -1, mkdir creates new directory
    if (mkdir_ret == -1 && errno != EEXIST)
    {
        printf("Error: %s (%s)\n", strerror(errno), ".commentmyccode/");
        return (-1);
    }
    return (0);
}

int create_commented_file(char *src_file)
{
    char    **split_src_file;
    char    *commented_file;
    int     fd_commented;

    split_src_file = ft_split(src_file, '/');
    if (split_src_file == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return (-1);
    }
    commented_file = ft_strjoin(".commentmyccode/commented_", split_src_file[len_string_array(split_src_file) - 1]); 
    if (commented_file == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        free_string_array(split_src_file);
        return (-1);
    }
    fd_commented = open(commented_file, O_RDWR | O_TRUNC | O_CREAT | O_APPEND, 0644);
    if (fd_commented == -1)
    {
        printf("Error: %s (%s)\n", strerror(errno), commented_file);
        free(commented_file);
        free_string_array(split_src_file);
        return (-1);
    }
    free(commented_file);
    free_string_array(split_src_file);
    return (fd_commented);
}

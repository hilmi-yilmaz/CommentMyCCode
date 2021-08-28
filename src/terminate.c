#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int terminate(int fd, int fd_extra, int fd_commented)
{
    int close_ret;

    close_ret = close(fd);
    if (close_ret == -1)
    {
        printf("Error: %s (file descriptor = %d)\n", strerror(errno), fd);
        return (-1);
    }
    close_ret = close(fd_extra);
    if (close_ret == -1)
    {
        printf("Error: %s (file descriptor = %d)\n", strerror(errno), fd);
        return (-1);
    }
    close_ret = close(fd_commented);
    if (close_ret == -1)
    {
        printf("Error: %s (file descriptor = %d)\n", strerror(errno), fd_commented);
        return (-1);
    }
    return (0);
}

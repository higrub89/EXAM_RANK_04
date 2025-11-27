#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int ft_popen(const char *file, const char *av[], char type)
{
    int fd[2];
    pid_t pid;
    if (!file || !av || (type != 'r' && type != 'w'))
        return -1;
        if (pipe(fd) == -1)
            return -1;
        pid = fork();
}
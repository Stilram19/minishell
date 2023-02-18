#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
        // int	i = 0;
        // int	y = 0;
        // int	fds[2];
        // char    *cmd = strdup("/usr/bin/wc");
        // char    **args = (char **)malloc(sizeof(char*) * 2);

        // args[0] = strdup("wc");
        // args[1] = NULL;
        // pipe(fds);

        // i = fork();
        // if (i == 0)
        // {
        //         dup2(fds[0], 0);
        //         close(fds[1]);
        //         if (execve(cmd, args, NULL))
        //                 perror("execve");
        // }
        // // y = fork();
        // // if (y == 0)
        // // {
        // //         close(fds[1]);
        // //         sleep(1);
        // //         write(1, "blah blah", 9);
        // //         exit(0);
        // // }
        // close(fds[0]);
        // close(fds[1]);
        // waitpid(i, 0, 0);
        if (open("a", O_CREAT | O_WRONLY, 0666) == -1)
                perror("open");
        printf("I'm Here\n");
        return (0);
}

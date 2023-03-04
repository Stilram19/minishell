#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>

// void    signal_handler(int sig)
// {
//         signal(SIGINT, SIG_IGN);
//         if (sig == SIGINT)
//                 printf("CTRL_C\n");
// }

// int main(void)
// {
//         int     pid;
//         int     status;

//         signal(SIGINT, signal_handler);
//         pid = fork();
//         if (!pid)
//         {
//                 signal(SIGINT, SIG_DFL);
//                 char *line = readline("> ");
//                 while (line)
//                         line = readline("> ");
//         }
//         waitpid(pid, &status, 0);
//         if (WIFEXITED(status))
//                 printf("EXIT NORMALLY %d\n", WEXITSTATUS(status));
//         sleep(5);
//         printf("I'm Here\n");
//         return (0);
// }

int main(void)
{
        struct termios orig;

        
        return (0);
}

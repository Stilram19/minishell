#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
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

void    signal_handler(int sig)
{
        if (sig == SIGINT)
                printf("CTRL_C\n");
}

int main(void)
{
        int     pid;
        int     status;
        struct sigaction action;

        action.sa_handler = signal_handler;
        sigaction(SIGINT, &action, NULL);
        pid = fork();
        if (!pid)
        {
                action.sa_handler = SIG_DFL;
                sigaction(SIGINT, &action, NULL);
                char *line = readline("> ");
                while (line)
                        line = readline("> ");
        }
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
                printf("EXIT NORMALLY %d\n", WEXITSTATUS(status));
        sleep(5);
        printf("I'm Here\n");
        return (0);
}

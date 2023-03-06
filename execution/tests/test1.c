#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

void	child1(int out)
{
	int		pid;
	int		status;
	char	*cmd;
	char	*args[2] = {"wdsgc", NULL};

	cmd = "dsgs";
	pid = fork();
	if (!pid)
	{
		// signal(SIGPIPE, SIG_DFL);
		dup2(out, 1);
		if (execve(cmd, args, NULL))
			perror("execve");
	}
	waitpid(pid, 0, 0);
	exit(122);
}

void	child2(int in)
{
	int		pid;
	int		status;
	char	*cmd;
	char	*args[3] = {"wc", NULL};

	cmd = "/usr/bin/wc";
	pid = fork();
	if (!pid)
	{
		dup2(in, 0);
		if (execve(cmd, args, NULL))
			perror("execve");
	}
	waitpid(pid, 0, 0);
	// exit(0);
}

void	handle_sigpipe(int sig)
{
	dprintf(2, "SIGPIPE: %d\n", sig);
}

int main(void)
{
	int	pid;
	int	fds[2];
	int	status;

	signal(SIGPIPE, SIG_DFL);
	pipe(fds);
	pid = fork();
	if (!pid)
	{
		close(fds[0]);
		child1(fds[1]);
	}
	close(fds[1]);
	child2(fds[0]);
	close(fds[0]);
	waitpid(pid, &status, 0);
	printf("%d\n", WEXITSTATUS(status));
	return (0);
}
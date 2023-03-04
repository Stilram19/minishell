# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>


// int	main(void)
// {
// 	int	pid;
// 	int	pid1;
// 	int fds[2];
// 	char	*args[4] = {"/usr/bin/head", "head", "-n1", NULL};

// 	pipe(fds);
// 	pid = fork();
// 	if (!pid)
// 	{
// 		close(fds[0]);
// 		write(fds[1], "hello\n", 6);
// 		write(fds[1], "world\n", 6);
// 		exit(0);
// 	}
// 	waitpid(pid, 0, 0);
// 	close(fds[1]);
// 	pid1 = fork();
// 	if (!pid1)
// 	{
// 		dup2(fds[0], 0);
// 		if (execve(args[0], args + 1, NULL))
// 			printf("execve failed");
// 		exit(0);
// 	}
// 	waitpid(pid1, 0, 0);
// 	char	buf[7];
// 	read(fds[0], buf, 6);
// 	buf[6] = 0;
// 	printf("parent:: %s\n", buf);
// 	return (0);
// }

int	main(void)
{
	char	buff[10];
	int	i;

	i = read(0, buff, 9);
	buff[i] = 0;
	printf("%s\n", buff);
	return (0);
}
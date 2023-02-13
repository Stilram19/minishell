#include <unistd.h>

int main(void)
{
	int	i = 0;
	int	fds[2];

	while (i < 2)
	{
		if (i == 1)
		{
			pipe(fds);
			write(fds[1], "kjgsk\n", 6);
		}
		i++;
	}
	printf("I'm Here\n");
	return (0);
}

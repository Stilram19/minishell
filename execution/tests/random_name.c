#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>

void random_name(void)
{
	char	name[11];
	char	buff[101];
	int		fd;
	int		i;
	int		j;
	int		sys_ret;

	i = 0;
	fd = open("/dev/random", O_RDONLY);
	while (i < 10)
	{
		j = 0;
		sys_ret = read(fd, buff, 100);
		buff[sys_ret] = '\0';
		while (buff[j] && i < 10)
		{
			if (isalnum(buff[j]))
				name[i++] = buff[j];
			j++;
		}
	}
	name[i] = '\0';
	printf("%d %s\n", i, name);
}

int	main(void)
{
	char	*name;

	random_name();
	return (0);
}
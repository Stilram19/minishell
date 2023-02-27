#include <unistd.h>

int	main(void)
{
	char p[2];

	p[0] = -40;
	p[1] = -88;
	write(1, p, 1);
	write(1, p + 1, 1);
	return (0);
}

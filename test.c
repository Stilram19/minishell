#include <unistd.h>

int main(void)
{
	dup2(0, 0);
	printf("%d\n", getpid()); 
	while (1);
	return (0);
}

#include <unistd.h>
#include <dirent.h>
#include <stdio.h>

int  main(void)
{
	DIR *dir;
	struct dirent *de;

	dir = opendir(".");
	de = readdir(dir);
	while (de)
	{
		printf("%s %llu %llu %llu \n", de->d_name, de->d_ino, de->d_reclen, de->d_namlen);
		de = readdir(dir);
	}
	return (0);
}
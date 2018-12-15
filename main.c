
#include "ft_ls.h"

int main(int ac, char *av[])
{
	DIR				*d;
	struct dirent	*dp;

	d = opendir(".");
	while ((dp = readdir(d)))
	{
		ft_printf("%s\n", dp->d_name);
	}
	closedir(d);
	return (0);
}

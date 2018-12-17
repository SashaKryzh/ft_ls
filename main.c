
#include "ft_ls.h"

void	parse_flags(char *s)
{
	int i;

	if (!s[1])
		exit(0);
	i = 0;
	while (s[++i])
	{
		if (!ft_contains(OPTS, s[i]))
			exit(0);
	}
}

void	parse(int ac, char *av[])
{
	int i;

	i = 0;
	while (++i < ac && av[i][0] == '-')
		parse_flags(av[i]);
}

int main(int ac, char *av[])
{
	DIR				*d;
	struct dirent	*dp;
	struct stat		st;

	parse(ac, av);
	d = opendir(".");
	while ((dp = readdir(d)))
	{
		if (dp->d_name[0] != '.')
		{
			if (stat(dp->d_name, &st) == -1)
				exit(1);
			ft_printf("%s %d\n", dp->d_name, st.st_nlink);
		}
		else
			ft_printf("%s\n", dp->d_name);
	}
	closedir(d);
	return (0);
}

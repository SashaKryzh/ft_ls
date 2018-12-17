
#include "ft_ls.h"

void	exit_func(char *msg)
{
	ft_printf("[ERROR]: %s\n", msg);
	exit(0);
}

void	parse_flags(t_flags *flags, char *s)
{
	int i;

	if (!s[1])
		exit_func("Invalid option");
	i = 0;
	while (s[++i])
	{
		if (!ft_contains(OPTS, s[i]))
			exit_func("Invalid option");
		if (s[i] == '1')
			flags->one = 1;
		if (s[i] == 'R')
			flags->rec = 1;
		if (s[i] == 'a')
			flags->a = 1;
		if (s[i] == 'r')
			flags->rev = 1;
		if (s[i] == 't')
			flags->t = 1;
	}
}

void	parse_names(char *s)
{
	return ;
}

void	get_args(int ac, char *av[], t_flags *flags)
{
	int i;

	i = 0;
	ft_bzero(flags, sizeof(*flags));
	while (++i < ac && av[i][0] == '-')
		parse_flags(flags, av[i]);
	while (++i < ac)
		parse_names(av[i]);
}

int main(int ac, char *av[])
{
	t_flags			*flags;
	DIR				*d;
	struct dirent	*dp;
	struct stat		st;

	get_args(ac, av, flags);
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

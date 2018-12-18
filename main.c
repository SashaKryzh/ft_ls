
#include "ft_ls.h"

void	exit_func(char *msg)
{
	ft_printf("ft_ls: %s\n", msg);
	exit(0);
}

void	add_directory()
{
	t_dir	*new;

	new = (t_dir *)malloc(sizeof(t_dir));
	ft_bzero(new, sizeof(t_dir));
}

void	print_files(t_flags flags, t_names *names)
{
	DIR				*d;
	struct dirent	*dp;
	struct stat		st;

	d = opendir(".");
	while ((dp = readdir(d)))
	{
		if (dp->d_name[0] != '.')
		{
			if (stat(dp->d_name, &st) == -1)
				exit(1);
			if (S_ISDIR(st.st_mode))
				add_directory();
			ft_printf("%s\n", dp->d_name);
		}
	}
	closedir(d);
}

int		main(int ac, char *av[])
{
	t_flags			flags;
	t_names			*names;

	get_args(ac, av, &flags, &names);
	print_files(flags, names);
	return (0);
}

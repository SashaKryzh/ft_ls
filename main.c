
#include "ft_ls.h"

t_flags			g_flags;

void	exit_func(char *msg)
{
	ft_printf("ft_ls: %s\n", msg);
	exit(0);
}

void	print_file(t_file file)
{
	ft_printf("%s\n", file.name);
}

void	print_files(t_file	*files)
{
	while (files)
	{
		print_file(*files);
		files = files->next;
	}
	ft_printf("\n");
}

void	add_directory(t_dir **dirs, struct dirent *dp, char *path)
{
	t_dir	*new;

	new = (t_dir *)malloc(sizeof(t_dir));
	ft_bzero(new, sizeof(t_dir));
	ft_strcpy(new->name, dp->d_name);
	ft_strcpy(new->path, path);
	ft_strcat(new->path, dp->d_name);
	ft_strcat(new->path, "/");
	new->next = *dirs;
	*dirs = new;
}

void	add_file(t_file **files, struct dirent *dp, struct stat st)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	ft_bzero(new, sizeof(t_file));
	ft_strcpy(new->name, dp->d_name);
	new->st = st;
	new->next = *files;
	*files = new;
}

void	print_subdirs(t_dir	*dirs)
{
	while (dirs)
	{
		print_current(dirs->path);
		dirs = dirs->next;
	}
}

void	print_current(char	*path)
{
	t_dir			*dirs;
	t_file			*files;
	DIR				*d;
	struct dirent	*dp;
	struct stat		st;

	dirs = NULL;
	files = NULL;
	if (!(d = opendir(path)))
		exit_func("d == 0");
	ft_printf("%.*s:\n", ft_strlen(path) - 1, path);
	while ((dp = readdir(d)))
	{
		if (dp->d_name[0] != '.')
		{
			if (stat(ft_strjoin(path, dp->d_name), &st) == -1)
				exit_func("stat == -1");
			if (S_ISDIR(st.st_mode))
				add_directory(&dirs, dp, path);
			add_file(&files, dp, st);
		}
	}
	closedir(d);
	print_files(files);
	// t_print_files(files); //
	// t_print_dirs(dirs); //
	if (g_flags.rec)
		print_subdirs(dirs);
}

int		main(int ac, char *av[])
{
	t_names			*names;

	get_args(ac, av, &names);
	ft_printf("--- --- --- --- --- --- --- --- ---\n");
	print_current("./");
	return (0);
}

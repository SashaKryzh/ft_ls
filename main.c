/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:52:56 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/19 13:52:57 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	add_file(t_file **files, struct dirent *dp, struct stat st, char *path)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	ft_bzero(new, sizeof(t_file));
	ft_strcpy(new->name, dp->d_name);
	new->st = st;
	new->path = path;
	new->next = *files;
	*files = new;
}

void	print_files(t_file *files)
{
	t_file *tmp;

	tmp = files;
	while (tmp)
	{
		print_file(*tmp);
		tmp = tmp->next;
	}
	if (g_flags.rec)
	{
		while (files)
		{
			if (files->path)
			{
				ft_printf("\n");
				print_current(files->path);
			}
			files = files->next;
		}
	}
}

void	print_current(char *path)
{
	DIR				*d;
	struct dirent	*dp;
	struct stat		st;
	t_file			*files;
	char			*to_file;

	files = NULL;
	if (!(d = opendir(path)))
		exit_func("d == 0");
	ft_printf("%s:\n", path);
	while ((dp = readdir(d)))
	{
		if (dp->d_name[0] != '.')
		{
			to_file = ft_build_path(path, dp->d_name);
			if (stat(to_file, &st) == -1)
				exit_func("stat == -1");
			if (!S_ISDIR(st.st_mode))
				ft_strdel(&to_file);
			add_file(&files, dp, st, to_file);
		}
	}
	closedir(d);
	sort_files(files);
	print_files(files);
}

int		main(int ac, char *av[])
{
	t_names			*names;

	get_args(ac, av, &names);
	ft_printf("--- --- --- --- --- --- --- --- ---\n");
	print_current(".");
	return (0);
}

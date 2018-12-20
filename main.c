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
int				g_blocks;
int				g_lwidth;
int				g_nwidth;
int				g_gwidth;
int				g_swidth;
int				g_ac;

void	exit_func(char *msg)
{
	ft_printf("ft_ls: %s\n", msg);
	exit(0);
}

void	add_file(t_file **files, char *name, struct stat st, char *path)
{
	t_file	*new;

	new = (t_file *)ft_memalloc(sizeof(t_file));
	new->name = ft_strdup(name);
	new->st = st;
	new->path = path;
	new->next = *files;
	*files = new;
}

void	print_files(t_file *files)
{
	t_file *tmp;

	tmp = files;
	calc_width(files);
	if (g_flags.one || g_flags.l)
		print_files_col(files);
	else
		print_files_row(files);
	while (g_flags.rec && tmp)
	{
		if (tmp->path)
		{
			ft_printf("\n");
			if (g_flags.l)
				ft_printf("total: %d\n", g_blocks);
			print_current(tmp->path, 1);
		}
		tmp = tmp->next;
	}
	free_files(files);
}

int		print_current(char *path, int show)
{
	DIR				*d;
	struct dirent	*dp;
	struct stat		st;
	t_file			*files;
	char			*to_file;

	files = NULL;
	if (!(d = opendir(path)))
		return (0);
	if (show)
		ft_printf("%s:\n", path);
	while ((dp = readdir(d)))
	{
		if (dp->d_name[0] == '.' && !g_flags.a)
			continue ;
		to_file = ft_build_path(path, dp->d_name);
		if (lstat(to_file, &st) == -1)
			exit_func("stat == -1");
		if (!S_ISDIR(st.st_mode) || IS_DOT)
			ft_strdel(&to_file);
		add_file(&files, dp->d_name, st, to_file);
	}
	closedir(d);
	sort_files(files);
	print_files(files);
	return (1);
}

void	print_dirs(t_file *dirs)
{
	int	check;

	check = 0;
	while (dirs)
	{
		print_current(dirs->name, g_ac > 2 || check);
		if (dirs->next)
			ft_printf("\n");
		dirs = dirs->next;
		check = 1;
	}
}

void	print_ls_arg(t_ls_arg *args)
{
	t_file			*files;
	t_file			*dirs;
	struct stat		st;

	files = NULL;
	dirs = NULL;
	while (args)
	{
		if (lstat(args->arg, &st) == -1)
			ft_printf("!!!\n");
		else
		{
    		if (!S_ISDIR(st.st_mode))
				add_file(&files, args->arg, st, NULL);
			else
				add_file(&dirs, args->arg, st, NULL);
		}
		args = args->next;
	}
	print_files(files);
	print_dirs(dirs);
}

int		main(int ac, char *av[])
{
	t_ls_arg			*args;

	g_ac = ac;
	get_ls_arg(ac, av, &args);
	ft_printf("--- --- --- --- --- --- --- --- ---\n");
	if (args)
		print_ls_arg(args);
	else
		print_current(".", 0);
	// system("leaks ft_ls"); //
	return (0);
}

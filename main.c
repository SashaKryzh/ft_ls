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
int				g_mawidth;
int				g_miwidth;
int				g_cnt_args;

void	exit_func(char *msg)
{
	ft_printf("ft_ls: %s\n", msg);
	exit(0);
}

void	print_files(t_file *files, int show_total)
{
	t_file *tmp;

	tmp = files;
	calc_width(files);
	if (g_flags.one || g_flags.l)
		print_files_col(files, show_total);
	else
		print_files_row(files);
	while (g_flags.rec && tmp)
	{
		if (tmp->is_dir)
		{
			ft_printf("\n");
			parse_dir(tmp->path, 1);
		}
		tmp = tmp->next;
	}
	free_files(files);
}

void	print_dirs(t_file *dirs, t_file *files)
{
	t_file	*start;

	start = dirs;
	if (files && dirs)
		ft_printf("\n");
	while (dirs)
	{
		parse_dir(dirs->name, g_cnt_args > 1);
		if (dirs->next)
			ft_printf("\n");
		dirs = dirs->next;
	}
	free_files(start);
}

void	print_ls_arg(t_ls_arg *args)
{
	t_file			*files;
	t_file			*dirs;
	struct stat		st;

	files = NULL;
	dirs = NULL;
	sort_args(args);
	while (args)
	{
		if (lstat(args->arg, &st) == -1)
			ft_printf("ft_ls: %s: No such file or directory\n", args->arg);
		else
		{
			if (!S_ISDIR(st.st_mode))
				add_file(&files, args->arg, st, args->arg);
			else
				add_file(&dirs, args->arg, st, args->arg);
		}
		args = args->next;
	}
	print_files(sort_files(files), 0);
	print_dirs(sort_files(dirs), files);
}

int		main(int ac, char *av[])
{
	t_ls_arg			*args;

	get_ls_arg(ac, av, &args);
	if (args)
		print_ls_arg(args);
	else
		parse_dir(".", 0);
	// system("leaks ft_ls"); //
	return (0);
}

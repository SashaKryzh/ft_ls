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
int				g_cnt_args;
int				g_show_total;

void	exit_func(char *msg)
{
	ft_printf("ft_ls: %s\n", msg);
	exit(0);
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
		if (tmp->is_dir)
		{
			ft_printf("\n");
			g_show_total = 1;
			parse_dir(tmp->path, 1);
		}
		tmp = tmp->next;
	}
	free_files(files);
}

void	print_dirs(t_file *dirs, t_file *files)
{
	int	check;

	check = 0;
	if (files && dirs)
		ft_printf("\n");
	g_show_total = 1;
	while (dirs)
	{
		parse_dir(dirs->name, g_cnt_args > 1 || check);
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
			ft_printf("lstat in args == -1\n");
		else
		{
    		if (!S_ISDIR(st.st_mode))
				add_file(&files, args->arg, st, NULL);
			else
				add_file(&dirs, args->arg, st, args->arg);
		}
		args = args->next;
	}
	print_files(files);
	print_dirs(dirs, files);
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

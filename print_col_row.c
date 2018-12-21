/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 09:04:52 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/20 09:04:53 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		show_pwgr(t_file *files)
{
	if (!g_flags.g)
	{
		ft_printf("%-*s", g_nwidth + 1, files->pw_name);
		ft_printf("%s", !g_flags.o ? " " : "");
	}
	if (!g_flags.o)
		ft_printf("%-*s", g_gwidth + 1, files->gr_name);
	if (g_flags.g && g_flags.o)
		ft_printf(" ");
}

void		show_size(t_file *files)
{
	static int	check;

	if (S_ISCHR(files->st.st_mode) || S_ISBLK(files->st.st_mode))
	{
		ft_printf(" %*d,", g_mawidth + 1, major(files->st.st_rdev));
		ft_printf("%*d", g_miwidth, minor(files->st.st_rdev));
		check = g_mawidth + g_miwidth;
	}
	else
		ft_printf("%*d", check ? check + 3 : g_swidth + 1, files->st.st_size);
	check = !files->next ? 0 : check;
}

void		print_files_col(t_file *files, int show_total)
{
	char	dst[1025];

	if (show_total && files)
		ft_printf("total %d\n", g_blocks);
	while (files)
	{
		dst[0] = '\0';
		if (g_flags.l)
		{
			show_filetype(files->st, files->name, (char *)&dst);
			show_permission(files->st, files->path);
			ft_printf("%*d ", g_lwidth + 1, files->st.st_nlink);
			show_pwgr(files);
			show_size(files);
			show_time(files->st);
		}
		ft_printf("%s%s\n", files->name, dst);
		files = files->next;
	}
}

void		print_comma(t_file *files)
{
	while (files)
	{
		ft_printf("%s", files->name);
		if ((files = files->next))
			ft_printf(", ");
	}
	ft_printf("\n");
}

void		print_files_row(t_file *files)
{
	if (!files)
		return ;
	if (g_flags.m)
	{
		print_comma(files);
		return ;
	}
	while (files->next)
	{
		ft_printf("%s\t", files->name);
		files = files->next;
	}
	ft_printf("%s\n", files->name);
}

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
			ft_printf("%-*s %-*s", g_nwidth + 1, files->pw_name, g_gwidth,
				files->gr_name);
			ft_printf(" %*d", g_swidth + 1, files->st.st_size);
			show_time(files->st);
		}
		ft_printf("%s%s\n", files->name, dst);
		files = files->next;
	}
}

void		print_files_row(t_file *files)
{
	if (!files)
		return ;
	while (files->next)
	{
		ft_printf("%s\t", files->name);
		files = files->next;
	}
	ft_printf("%s\n", files->name);
}

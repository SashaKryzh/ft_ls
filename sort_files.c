/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:50:20 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/19 13:50:20 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		swap_files(t_file *file)
{
	t_file	tmp;

	ft_memcpy(&tmp, file, sizeof(t_file) - sizeof(t_file *));
	ft_memcpy(file, file->next, sizeof(t_file) - sizeof(t_file *));
	ft_memcpy(file->next, &tmp, sizeof(t_file) - sizeof(t_file *));
	return (1);
}

void			sort_files(t_file *files)
{
	t_file	*tmp;
	time_t	t1;
	time_t	t2;
	int		swapped;

	if (!files)
		return ;
	swapped = 1;
	// t1 = time(&files->st.st_mtime);
	// t2 = time(&files->next->st.st_mtime);
	// ft_printf("%d\n", t1);
	// ft_printf("%d", t2);
	while (swapped)
	{
		swapped = 0;
		tmp = files;
		while (tmp->next)
		{
			if (!g_flags.t &&
				(ft_strcmp(tmp->name, tmp->next->name) > 0) != g_flags.rev)
				swapped = swap_files(tmp);
			else if (g_flags.t && (time(&tmp->st.st_mtime) > time(&tmp->next->st.st_mtime)) != g_flags.rev)
				swapped = swap_files(tmp);
			tmp = tmp->next;
		}
	}
}

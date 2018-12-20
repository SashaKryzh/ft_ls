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

static int		check_time(t_file *files)
{
	if (!g_flags.t)
		return (0);
	if (!g_flags.rev && files->st.st_mtime < files->next->st.st_mtime)
		return (1);
	if (g_flags.rev && files->st.st_mtime > files->next->st.st_mtime)
		return (1);
	if (files->st.st_mtime == files->next->st.st_mtime)
	{
		if ((ft_strcmp(files->name, files->next->name) > 0) != g_flags.rev)
			return (1);
	}
	return (0);
}

t_file			*sort_files(t_file *files)
{
	t_file	*tmp;
	int		swapped;

	if (!files)
		return (NULL);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		tmp = files;
		while (tmp->next)
		{
			if (!g_flags.t &&
				(ft_strcmp(tmp->name, tmp->next->name) > 0) != g_flags.rev)
				swapped = swap_files(tmp);
			else if (check_time(tmp))
				swapped = swap_files(tmp);
			tmp = tmp->next;
		}
	}
	return (files);
}

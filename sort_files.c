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

int				check_name(t_file *files, t_file *new)
{
	if (!files || (ft_strcmp(files->name, new->name) > 0) != g_flags.rev)
		return (1);
	return (0);
}

int				check_time(t_file *files, t_file *new)
{
	if (!files)
		return (1);
	if (!g_flags.rev && files->st.st_mtime < new->st.st_mtime)
		return (1);
	else if (g_flags.rev && files->st.st_mtime > new->st.st_mtime)
		return (1);
	else if (files->st.st_mtime == new->st.st_mtime)
		return (check_name(files, new));
	return (0);
}

int				check_size(t_file *files, t_file *new)
{
	if (!files)
		return (1);
	if (!g_flags.rev && files->st.st_size < new->st.st_size)
		return (1);
	else if (g_flags.rev && files->st.st_size > new->st.st_size)
		return (1);
	else if (files->st.st_size == new->st.st_size)
		return (check_name(files, new));
	return (0);
}

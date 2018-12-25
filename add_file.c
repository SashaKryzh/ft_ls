/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 09:40:29 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/25 09:40:30 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*create_file(char *name, struct stat st, char *path)
{
	t_file	*new;

	new = (t_file *)ft_memalloc(sizeof(t_file));
	new->name = ft_strdup(name);
	new->is_dir = S_ISDIR(st.st_mode) && !(IS_DOT) ? 1 : 0;
	new->st = st;
	new->path = path;
	calc_width(new);
	return (new);
}

void	add_file(t_file **files, t_file *new, int (*f)())
{
	t_file	*tmp;

	if ((*f) && (*f)(*files, new))
	{
		new->next = *files;
		*files = new;
	}
	else
	{
		tmp = *files;
		while (tmp->next)
		{
			if ((*f) && (*f)(tmp->next, new))
			{
				new->next = tmp->next;
				tmp->next = new;
				return ;
			}
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

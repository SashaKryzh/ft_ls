/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 16:05:59 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/20 16:05:59 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_file(t_file **files, char *name, struct stat st, char *path)
{
	t_file	*new;

	new = (t_file *)ft_memalloc(sizeof(t_file));
	new->name = ft_strdup(name);
	new->is_dir = S_ISDIR(st.st_mode) && !(IS_DOT) ? 1 : 0;
	new->st = st;
	new->path = path;
	new->next = *files;
	*files = new;
}

void	parse_dir(char *path, int show)
{
	DIR				*d;
	struct dirent	*dp;
	struct stat		st;
	t_file			*files;
	char			*to_file;

	files = NULL;
	if (!(d = opendir(path)))
		exit_func("d == 0");
	if (show)
		ft_printf("%s:\n", path);
	while ((dp = readdir(d)))
	{
		if (dp->d_name[0] == '.' && !g_flags.a)
			continue ;
		to_file = ft_build_path(path, dp->d_name);
		if (lstat(to_file, &st) == -1)
			exit_func("stat == -1");
		add_file(&files, dp->d_name, st, to_file);
	}
	closedir(d);
	print_files(sort_files(files));
}

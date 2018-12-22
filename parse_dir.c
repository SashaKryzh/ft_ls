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

t_file	*creat_file(char *name, struct stat st, char *path)
{
	t_file	*new;

	new = (t_file *)ft_memalloc(sizeof(t_file));
	new->name = ft_strdup(name);
	new->is_dir = S_ISDIR(st.st_mode) && !(IS_DOT) ? 1 : 0;
	new->st = st;
	new->path = path;
	return (new);
}

void	add_file(t_file **files, char *name, struct stat st, char *path)
{
	t_file	*tmp;

	if (!*files)
		*files = creat_file(name, st, path);
	else
	{
		tmp = *files;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = creat_file(name, st, path);
	}
}

void	check_d_error(char *path)
{
	if (ft_strequ(path, "/dev/fd/3"))
		ft_printf("ft_ls: 3: Not a directory\n");
	else
		ft_printf("ft_ls: %s: Permission dinied\n", ft_strrchr(path, '/') + 1);
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
	{
		check_d_error(path);
		return ;
	}
	if (show)
		ft_printf("%s:\n", path);
	while ((dp = readdir(d)))
	{
		if (dp->d_name[0] == '.' && !g_flags.a)
			continue ;
		to_file = ft_build_path(path, dp->d_name);
		if (lstat(to_file, &st) == -1)
			continue ;
		add_file(&files, dp->d_name, st, to_file);
	}
	closedir(d);
	print_files(sort_files(files), g_flags.l);
}

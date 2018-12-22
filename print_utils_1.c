/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 17:29:39 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/20 17:29:39 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		show_filetype(struct stat st, char *path, char *dst)
{
	char	c;

	if (S_ISREG(st.st_mode))
		c = '-';
	else if (S_ISDIR(st.st_mode))
		c = 'd';
	else if (S_ISBLK(st.st_mode))
		c = 'b';
	else if (S_ISCHR(st.st_mode))
		c = 'c';
	else if (S_ISFIFO(st.st_mode))
		c = 'p';
	else if (S_ISLNK(st.st_mode))
	{
		get_link_path(path, dst);
		c = 'l';
	}
	else if (S_ISSOCK(st.st_mode))
		c = 's';
	else
		c = '?';
	ft_printf("%c", c);
}

void		show_other_permission(struct stat st, char *path)
{
	if (st.st_mode & S_ISVTX)
		ft_printf((st.st_mode & S_IXOTH) ? "t" : "T");
	else
		ft_printf((st.st_mode & S_IXOTH) ? "x" : "-");
	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		ft_printf("@");
	else
		ft_printf(" ");
}

void		show_third(struct stat st, int owner)
{
	if (owner)
	{
		if (st.st_mode & S_ISUID)
			ft_printf((st.st_mode & S_IXUSR) ? "s" : "S");
		else
			ft_printf((st.st_mode & S_IXUSR) ? "x" : "-");
	}
	else
	{
		if (st.st_mode & S_ISGID)
			ft_printf((st.st_mode & S_IXGRP) ? "s" : "S");
		else
			ft_printf((st.st_mode & S_IXGRP) ? "x" : "-");
	}
}

void		show_permission(struct stat st, char *path)
{
	ft_printf((st.st_mode & S_IRUSR) ? "r" : "-");
	ft_printf((st.st_mode & S_IWUSR) ? "w" : "-");
	show_third(st, 1);
	ft_printf((st.st_mode & S_IRGRP) ? "r" : "-");
	ft_printf((st.st_mode & S_IWGRP) ? "w" : "-");
	show_third(st, 0);
	ft_printf((st.st_mode & S_IROTH) ? "r" : "-");
	ft_printf((st.st_mode & S_IWOTH) ? "w" : "-");
	show_other_permission(st, path);
}

void		show_size(t_file *files)
{
	static int	check;

	if (S_ISCHR(files->st.st_mode) || S_ISBLK(files->st.st_mode))
	{
		ft_printf(" %*d,", g_mawidth + 1, major(files->st.st_rdev));
		ft_printf("%*d", g_miwidth + 1, minor(files->st.st_rdev));
		check = g_mawidth + g_miwidth;
	}
	else
		ft_printf("%*d", check ? check + 4 : g_swidth + 1, files->st.st_size);
	check = !files->next ? 0 : check;
}

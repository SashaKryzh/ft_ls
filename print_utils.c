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

void	get_path(char *path, char *dst)
{
	ssize_t	ret;

	ft_strcpy(dst, " -> ");
	if ((ret = readlink(path, &dst[4], 1025)) == -1)
		ft_printf("readlink == -1\n");
	dst[ret + 4] = '\0';
}

void	show_filetype(struct stat st, char *path, char *dst)
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
		get_path(path, dst);
		c = 'l';
	}
	else if (S_ISSOCK(st.st_mode))
		c = 's';
	else
		c = '?';
	ft_printf("%c", c);
}

void	show_permission(struct stat st, char *path)
{
	ft_printf((st.st_mode & S_IRUSR) ? "r" : "-");
	ft_printf((st.st_mode & S_IWUSR) ? "w" : "-");
	ft_printf((st.st_mode & S_IXUSR) ? "x" : "-");
	ft_printf((st.st_mode & S_IRGRP) ? "r" : "-");
	ft_printf((st.st_mode & S_IWGRP) ? "w" : "-");
	ft_printf((st.st_mode & S_IXGRP) ? "x" : "-");
	ft_printf((st.st_mode & S_IROTH) ? "r" : "-");
	ft_printf((st.st_mode & S_IWOTH) ? "w" : "-");
	if (st.st_mode & S_ISVTX)
		ft_printf("t");
	else
		ft_printf((st.st_mode & S_IXOTH) ? "x" : "-");
	if (listxattr(path, NULL, 0, 0))
		ft_printf("@");
	else
		ft_printf(" ");
}

void	show_time(struct stat st)
{
	char	*tm;

	tm = ctime(&(st.st_mtime));
	if (time(NULL) - st.st_mtime < LS_YEAR)
		ft_printf(" %.12s ", &tm[4]);
	else
		ft_printf(" %.6s %5.4s ", &tm[4], &tm[20]);
}

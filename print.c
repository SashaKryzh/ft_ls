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

static void	get_path(char *path, char *dst)
{
	ssize_t	ret;

	ft_strcpy(dst, " -> ");
	if ((ret = readlink(path, &dst[4], 1025)) == -1)
		exit(1);
	dst[ret + 4] = '\0';
}

static void	show_filetype(struct stat st, char *path, char *dst)
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

static void	show_permission(struct stat st)
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
		ft_printf("t ");
	else
		ft_printf((st.st_mode & S_IXOTH) ? "x " : "- ");
}

void		show_time(struct stat st)
{
	char	*tm;

	tm = ctime(&(st.st_mtime));
	if (time(NULL) - st.st_mtime < LS_YEAR)
		ft_printf(" %.12s ", &tm[4]);
	else
		ft_printf(" %.6s %5.4s ", &tm[4], &tm[20]);
}

void		print_files_col(t_file *files)
{
	char	dst[1025];

	if (g_show_total && files)
		ft_printf("total %d\n", g_blocks);
	while (files)
	{
		dst[0] = '\0';
		if (g_flags.l)
		{
			show_filetype(files->st, files->name, (char *)&dst);
			show_permission(files->st);
			ft_printf("%*d ", g_lwidth + 1, files->st.st_nlink);
			ft_printf("%-*s %*s", g_nwidth, files->pw_name, g_gwidth + 1,
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

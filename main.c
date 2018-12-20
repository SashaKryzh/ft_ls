/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:52:56 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/19 13:52:57 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flags			g_flags;
int				g_lwidth;
int				g_nwidth;
int				g_gwidth;
int				g_swidth;

void	exit_func(char *msg)
{
	ft_printf("ft_ls: %s\n", msg);
	exit(0);
}

void	show_filetype(struct stat st)
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
        c = 'l';
    else if (S_ISSOCK(st.st_mode))
        c = 's';
    // else if (S_ISDOOR(st.st_mode))
    //     c = 'D';
    else
        c = '?';
    ft_printf("%c", c);
}

void	show_permission(struct stat st)
{
    ft_printf((st.st_mode & S_IRUSR) ? "r" : "-");
    ft_printf((st.st_mode & S_IWUSR) ? "w" : "-");
    ft_printf((st.st_mode & S_IXUSR) ? "x" : "-");
    ft_printf((st.st_mode & S_IRGRP) ? "r" : "-");
    ft_printf((st.st_mode & S_IWGRP) ? "w" : "-");
    ft_printf((st.st_mode & S_IXGRP) ? "x" : "-");
    ft_printf((st.st_mode & S_IROTH) ? "r" : "-");
    ft_printf((st.st_mode & S_IWOTH) ? "w" : "-");
    ft_printf((st.st_mode & S_IXOTH) ? "x " : "- ");
}

void	print_file(t_file file)
{
	show_filetype(file.st);
	show_permission(file.st);
	ft_printf("%*d ", g_lwidth + 1, file.st.st_nlink);
	ft_printf("%-*s %*s", g_nwidth, file.pw_name, g_gwidth + 1, file.gr_name);
	ft_printf(" %*d", g_swidth + 1, file.st.st_size);
	ft_printf(" %.12s ", &ctime(&(file.st.st_mtime))[4]);
	ft_printf("%s\n", file.name);
}

void	add_file(t_file **files, struct dirent *dp, struct stat st, char *path)
{
	t_file	*new;

	new = (t_file *)ft_memalloc(sizeof(t_file));
	ft_strcpy(new->name, dp->d_name);
	new->st = st;
	new->path = path;
	new->next = *files;
	*files = new;
}

void	print_files(t_file *files)
{
	t_file *tmp;

	tmp = files;
	calc_width(files);
	while (tmp)
	{
		print_file(*tmp);
		tmp = tmp->next;
	}
	if (g_flags.rec)
	{
		while (files)
		{
			if (files->path)
			{
				ft_printf("\n");
				print_current(files->path, 1);
			}
			files = files->next;
		}
	}
}

void	print_current(char *path, int show)
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
		if (!S_ISDIR(st.st_mode) || IS_DOT)
			ft_strdel(&to_file);
		add_file(&files, dp, st, to_file);
	}
	closedir(d);
	sort_files(files);
	print_files(files);
}

int		main(int ac, char *av[])
{
	t_names			*names;

	get_args(ac, av, &names);
	ft_printf("--- --- --- --- --- --- --- --- ---\n");
	print_current(".", 0);
	return (0);
}

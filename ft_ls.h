/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 08:05:24 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/18 08:05:25 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

# include <dirent.h>
# include <time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <stdio.h>

# define OPTS "Rartl1"
# define USAGE "usage: ft_ls [-Rartl1] [file ...]"
# define LS_YEAR 31536000

# define IS_DOT ft_strequ(name, ".") || ft_strequ(name, "..")

# define WD_NLINK ft_nbrlen(files->st.st_nlink, 10)
# define WD_NAME ft_strlen(pw->pw_name)
# define WD_GROUP ft_strlen(gr->gr_name)
# define WD_SIZE ft_nbrlen(files->st.st_size, 10)

typedef struct		s_flags
{
	unsigned char	one:	1;
	unsigned char	rec:	1;
	unsigned char	a:		1;
	unsigned char	rev:	1;
	unsigned char	t:		1;
	unsigned char	l:		1;
}					t_flags;

extern t_flags		g_flags;

typedef struct		s_ls_arg
{
	char			*arg;
	struct s_ls_arg	*next;
}					t_ls_arg;

typedef struct		s_file
{
	char			*name;
	char			*path;
	int				is_dir;
	char			*pw_name;
	char			*gr_name;
	struct stat		st;
	struct s_file	*next;
}					t_file;

extern int			g_blocks;
extern int			g_lwidth;
extern int			g_nwidth;
extern int			g_gwidth;
extern int			g_swidth;

extern int			g_cnt_args;

void				get_ls_arg(int ac, char *av[], t_ls_arg **args);
void				parse_dir(char *path, int show);

/*
**	Print
*/

void				print_files(t_file *files, int show_total);
void				print_files_col(t_file *files, int show_total);
void				print_files_row(t_file *files);

/*
**	Print utils
*/


void		get_path(char *path, char *dst);
void		show_filetype(struct stat st, char *path, char *dst);
void		show_permission(struct stat st, char *path);
void		show_time(struct stat st);

/*
**	Utils
*/

void				exit_func(char *msg);
char				*ft_build_path(char *path, char *file_name);
void				calc_width(t_file *files);
void				add_file(t_file **files, char *name, struct stat st, char *path);
void				free_files(t_file *files);
t_file				*sort_files(t_file *files);
t_ls_arg			*sort_args(t_ls_arg *args);

/*
**	Tests
*/

void				t_print_flags(void);
void				t_print_ls_arg(t_ls_arg *args);
void				t_print_files(t_file *files);

#endif

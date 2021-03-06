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

# define LS_OPTS "Rartl1UogmS"
# define LS_USAGE "usage: ft_ls [-Rartl1UogmS] [file ...]"
# define LS_HALF_YEAR 15768000

# define CREATE_ARG create_file(args->name, st, args->name)
# define IS_DOT ft_strequ(name, ".") || ft_strequ(name, "..")

# define WD_NLINK ft_nbrlen(files->st.st_nlink, 10)
# define WD_NAME ft_strlen(pw->pw_name)
# define WD_GROUP ft_strlen(gr->gr_name)
# define WD_SIZE ft_nbrlen(files->st.st_size, 10)
# define WD_MAJOR ft_nbrlen(major(files->st.st_rdev), 10)
# define WD_MINOR ft_nbrlen(minor(files->st.st_rdev), 10)

typedef struct		s_flags
{
	unsigned char	one:	1;
	unsigned char	rec:	1;
	unsigned char	a:		1;
	unsigned char	rev:	1;
	unsigned char	l:		1;
	unsigned char	no_sort:1;
	unsigned char	o:		1;
	unsigned char	g:		1;
	unsigned char	m:		1;
	int				(*f_sort)();
}					t_flags;

extern t_flags		g_flags;

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
extern int			g_mawidth;
extern int			g_miwidth;

extern int			g_cnt_args;

void				get_ls_arg(int ac, char *av[], t_file **args);
void				parse_dir(char *path, int show);

void				add_file(t_file **files, t_file *new, int (*f)());
t_file				*create_file(char *name, struct stat st, char *path);

/*
**	Check stat
*/

int					check_name(t_file *files, t_file *new);
int					check_time(t_file *files, t_file *new);
int					check_size(t_file *files, t_file *new);

/*
**	Print
*/

void				print_files(t_file *files, int show_total);
void				print_files_col(t_file *files, int show_total);
void				print_files_row(t_file *files);

/*
**	Print utils
*/

void				get_link_path(char *path, char *dst);
void				show_permission(struct stat st, char *path, char *dst);
void				show_pwgr(t_file *files);
void				show_size(t_file *files);
void				show_time(struct stat st);
void				show_pwgr(t_file *files);

/*
**	Utils
*/

char				*ft_build_path(char *path, char *file_name);
void				init_globals(void);
void				calc_width(t_file *files);
void				free_files(t_file *files);

#endif

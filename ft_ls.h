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

# define OPTS "Rart1l"
# define USAGE "usage: ft_ls [-Rart1] [file ...]"

# define IS_DOT ft_strequ(dp->d_name, ".") || ft_strequ(dp->d_name, "..")

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

typedef struct		s_names
{
	char			name[1025];
	struct s_names	*next;
}					t_names;

typedef struct		s_file
{
	char			name[1025];
	char			*path;
	char			*pw_name;
	char			*gr_name;
	struct stat		st;
	struct s_file	*next;
}					t_file;

extern int			g_lwidth;
extern int			g_nwidth;
extern int			g_gwidth;
extern int			g_swidth;

void				get_args(int ac, char *av[], t_names **names);
void				print_current(char *path, int show);

/*
**	Print
*/

void				print_file_col(t_file *files);
void				print_file_row(t_file *files);

/*
**	Utils
*/

void				exit_func(char *msg);
char				*ft_build_path(char *path, char *file_name);
void				calc_width(t_file *files);

void				sort_files(t_file *files);

/*
**	Tests
*/

void				t_print_flags(void);
void				t_print_names(t_names *names);
// void				t_print_dirs(t_dir *dirs);
void				t_print_files(t_file *files);

#endif

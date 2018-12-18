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
# include <sys/stat.h>
# include <sys/types.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>

# define OPTS "Rart1"
# define USAGE "usage: ft_ls [-Rart1] [file ...]"

typedef struct		s_flags
{
	unsigned char	one:	1;
	unsigned char	rec:	1;
	unsigned char	a:		1;
	unsigned char	rev:	1;
	unsigned char	t:		1;
}					t_flags;

typedef struct		s_names
{
	char			name[256];
	struct s_names	*next;
}					t_names;

typedef struct		s_dir
{
	char			name[256];
	char			path[100000];
	struct s_dir	*next;
}					t_dir;

typedef struct		s_file
{
	char			name[256];
	struct stat		st;
	struct s_file	*next;
}					t_file;

extern t_flags			g_flags;

void				get_args(int ac, char *av[], t_names **names);
void				print_current(char	*path);

/*
**	Utils
*/

void				exit_func(char *msg);

/*
**	Tests
*/

void				t_print_flags(void);
void				t_print_names(t_names *names);
void				t_print_dirs(t_dir *dirs);
void				t_print_files(t_file *files);

#endif

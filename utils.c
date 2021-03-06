/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:15:50 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/19 13:15:50 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_build_path(char *path, char *file_name)
{
	char	*to_file;

	to_file = ft_strnew(ft_strlen(path) + ft_strlen(file_name) + 1);
	ft_strcat(to_file, path);
	ft_strcat(to_file, "/");
	ft_strcat(to_file, file_name);
	return (to_file);
}

void	get_link_path(char *path, char *dst)
{
	ssize_t	ret;

	ft_strcpy(dst, " -> ");
	if ((ret = readlink(path, &dst[4], 2496)) == -1)
		dst[0] = '\0';
	dst[ret + 4] = '\0';
}

void	init_globals(void)
{
	g_blocks = 0;
	g_lwidth = 0;
	g_nwidth = 0;
	g_gwidth = 0;
	g_swidth = 0;
	g_mawidth = 0;
	g_miwidth = 0;
}

void	calc_width(t_file *files)
{
	struct passwd	*pw;
	struct group	*gr;

	pw = getpwuid(files->st.st_uid);
	gr = getgrgid(files->st.st_gid);
	g_lwidth = WD_NLINK > g_lwidth ? WD_NLINK : g_lwidth;
	g_nwidth = (int)WD_NAME > g_nwidth ? WD_NAME : g_nwidth;
	g_gwidth = (int)WD_GROUP > g_gwidth ? WD_GROUP : g_gwidth;
	g_swidth = WD_SIZE > g_swidth ? WD_SIZE : g_swidth;
	if (S_ISCHR(files->st.st_mode) || S_ISBLK(files->st.st_mode))
	{
		g_mawidth = WD_MAJOR > g_mawidth ? WD_MAJOR : g_mawidth;
		g_miwidth = WD_MINOR > g_miwidth ? WD_MINOR : g_miwidth;
	}
	files->pw_name = ft_strdup(pw->pw_name);
	files->gr_name = ft_strdup(gr->gr_name);
	g_blocks += files->st.st_blocks;
}

void	free_files(t_file *files)
{
	if (!files)
		return ;
	free_files(files->next);
	free(files->name);
	free(files->path);
	free(files->pw_name);
	free(files->gr_name);
	free(files);
}

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

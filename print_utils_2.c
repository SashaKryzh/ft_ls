/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 18:41:58 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/21 18:41:59 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		show_pwgr(t_file *files)
{
	if (!g_flags.g)
	{
		ft_printf("%-*s", g_nwidth + 1, files->pw_name);
		ft_printf("%s", !g_flags.o ? " " : "");
	}
	if (!g_flags.o)
		ft_printf("%-*s", g_gwidth + 1, files->gr_name);
	if (g_flags.g && g_flags.o)
		ft_printf(" ");
}

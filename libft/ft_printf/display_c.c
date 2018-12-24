/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 08:43:27 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/13 08:43:27 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				display_c(t_arg *arg, va_list ap, int percent)
{
	int				i;
	unsigned char	c;

	i = 0;
	c = percent ? '%' : (unsigned char)va_arg(ap, int);
	if (arg->width && !arg->left_adj)
		padding(arg, arg->zero_pad ? '0' : ' ', 1);
	write(1, &c, 1);
	if (arg->width && arg->left_adj)
		padding(arg, ' ', 1);
	return (arg->width > 0 ? arg->width : 1);
}

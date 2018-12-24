/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 18:13:50 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/19 18:13:50 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			display_b(t_arg *arg, va_list ap)
{
	unsigned char	octet;
	int				ret;

	ret = 8;
	arg->length = hh;
	octet = get_unsinged(arg, ap);
	arg->pref = '\0';
	ret += arg->alter ? 1 : 0;
	if (arg->width > ret && !arg->left_adj)
		ret += padding(arg, ' ', ret);
	arg->pref = arg->alter ? 'b' : '\0';
	ft_putchar(arg->pref);
	ft_print_bits(octet);
	if (arg->width > ret && arg->left_adj)
		ret += padding(arg, ' ', 8);
	return (ret);
}

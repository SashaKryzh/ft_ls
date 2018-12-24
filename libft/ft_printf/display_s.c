/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:03:29 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/12 13:03:29 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		display_s(t_arg *arg, va_list ap)
{
	int		ret;
	int		to_print;
	char	*s;
	char	*null;

	null = "(null)";
	if (!(s = (char *)va_arg(ap, const char *)))
		s = null;
	ret = ft_strlen(s);
	ret = arg->precision < ret && arg->precision != -1 ? arg->precision : ret;
	to_print = ret;
	if (arg->width > ret && !arg->left_adj)
		ret += padding(arg, arg->pad, ret);
	ft_putnstr(s, to_print);
	if (arg->width > ret && arg->left_adj)
		ret += padding(arg, ' ', to_print);
	return (ret);
}

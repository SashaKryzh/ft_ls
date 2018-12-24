/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 14:39:42 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/17 14:39:42 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	get_f(t_arg *arg, va_list ap)
{
	long double n;

	n = 0;
	if (arg->length == no_lenght || arg->length == l)
		n = va_arg(ap, double);
	else if (arg->length == L)
		n = va_arg(ap, long double);
	return (n);
}

char		*f_sign(t_arg *arg, char *s)
{
	char *tmp;

	if (*s == '-')
	{
		MALCH((tmp = ft_strsub(s, 1, ft_strlen(s) - 1)));
		free(s);
		s = tmp;
	}
	if ((arg->blank || arg->pref) && (!arg->zero_pad))
		s = d_pref(arg, s, 0);
	return (s);
}

int			display_f(t_arg *arg, va_list ap)
{
	long double	n;
	char		*s;
	int			ret;

	n = get_f(arg, ap);
	arg->precision = arg->precision == -1 ? 6 : arg->precision;
	MALCH((s = ft_dtoa(n, arg->precision)));
	arg->pref = arg->sign ? '+' : arg->pref;
	arg->pref = n < 0 ? '-' : arg->pref;
	s = f_sign(arg, s);
	ret = ft_strlen(s);
	if (arg->width > ret && !arg->left_adj)
		ret += padding(arg, arg->pad, ret);
	ft_putstr(s);
	if (arg->width > ret && arg->left_adj)
		ret += padding(arg, ' ', ret);
	free(s);
	return (ret);
}

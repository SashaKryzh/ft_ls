/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 19:13:20 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/14 19:13:20 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*o_alter(char *s, int len)
{
	char	*tmp;
	int		i;

	MALCH((tmp = ft_strnew(len + 1)));
	i = 0;
	while (i < len)
	{
		tmp[i + 1] = s[i];
		i++;
	}
	tmp[0] = '0';
	free(s);
	return (tmp);
}

int			display_o(t_arg *arg, va_list ap)
{
	uintmax_t	n;
	char		*s;
	int			ret;

	n = get_unsinged(arg, ap);
	MALCH((s = u_itoa_base(n, 8)));
	*s = arg->precision == 0 && n == 0 ? '\0' : *s;
	arg->alter = arg->precision != 0 && n == 0 ? 0 : arg->alter;
	s = arg->alter ? o_alter(s, ft_strlen(s)) : s;
	s = unsigned_precision(s, arg->precision);
	ret = ft_strlen(s);
	if (arg->width > arg->precision && !arg->left_adj)
		ret += padding(arg, arg->pad, ret);
	ft_putstr(s);
	if (arg->width > ret && arg->left_adj)
		ret += padding(arg, ' ', ft_strlen(s));
	free(s);
	return (ret);
}

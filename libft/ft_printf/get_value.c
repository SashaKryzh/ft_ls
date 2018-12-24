/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_unsigned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:13:35 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/15 13:13:35 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	get_unsinged(t_arg *arg, va_list ap)
{
	uintmax_t n;

	n = va_arg(ap, uintmax_t);
	if (arg->length == hh)
		n = (unsigned char)n;
	if (arg->length == h)
		n = (unsigned short)n;
	if (arg->length == ll)
		n = (unsigned long long)n;
	if (arg->length == l)
		n = (unsigned long)n;
	if (arg->length == j)
		n = (uintmax_t)n;
	if (arg->length == z)
		n = (size_t)n;
	if (arg->length == no_lenght)
		n = (unsigned int)n;
	return (n);
}

intmax_t	get_signed(t_arg *arg, va_list ap)
{
	intmax_t n;

	n = va_arg(ap, intmax_t);
	if (arg->length == hh)
		n = (char)n;
	if (arg->length == h)
		n = (short)n;
	if (arg->length == ll)
		n = (long long)n;
	if (arg->length == l)
		n = (long)n;
	if (arg->length == j)
		n = (intmax_t)n;
	if (arg->length == z)
		n = (ssize_t)n;
	if (arg->length == no_lenght)
		n = (int)n;
	return (n);
}

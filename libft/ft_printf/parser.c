/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 07:52:01 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/13 07:52:02 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_flags(t_arg *arg, char **format)
{
	while (**format == '#' || **format == '0' || **format == '-'
	|| **format == '+' || **format == ' ')
	{
		if (**format == '#')
			arg->alter = 1;
		if (**format == '0')
			arg->zero_pad = 1;
		if (**format == '-')
			arg->left_adj = 1;
		if (**format == '+')
			arg->sign = 1;
		if (**format == ' ')
		{
			arg->blank = 1;
			arg->pref = ' ';
		}
		*format += 1;
	}
}

void	get_width(t_arg *arg, char **format, va_list ap)
{
	if (**format == '0')
		return ;
	if (**format == '*')
	{
		arg->width = va_arg(ap, int);
		*format += 1;
		return ;
	}
	while (ft_isdigit(**format))
	{
		arg->width = arg->width * 10 + (**format - '0');
		*format += 1;
	}
}

void	get_precision(t_arg *arg, char **format, va_list ap)
{
	if (**format != '.')
		return ;
	*format += 1;
	if (**format == '*')
	{
		arg->precision = va_arg(ap, int);
		*format += 1;
		return ;
	}
	arg->precision = 0;
	while (ft_isdigit(**format))
	{
		arg->precision = arg->precision * 10 + (**format - '0');
		*format += 1;
	}
}

void	get_length(t_arg *arg, char **format)
{
	if (**format == 'h' && format[0][1] == 'h')
	{
		arg->length = hh;
		*format += 2;
	}
	else if (**format == 'l' && format[0][1] == 'l')
	{
		arg->length = ll;
		*format += 2;
	}
	else if (**format == 'h' || **format == 'l' || **format == 'L'
	|| **format == 'j' || **format == 'z')
	{
		if (**format == 'h')
			arg->length = h;
		if (**format == 'l')
			arg->length = l;
		if (**format == 'j')
			arg->length = j;
		if (**format == 'z')
			arg->length = z;
		if (**format == 'L')
			arg->length = L;
		*format += 1;
	}
}

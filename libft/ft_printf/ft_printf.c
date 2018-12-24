/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 14:33:27 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/11 14:33:28 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	initialize(t_arg *arg)
{
	arg->alter = 0;
	arg->zero_pad = 0;
	arg->left_adj = 0;
	arg->sign = 0;
	arg->blank = 0;
	arg->pref = '\0';
	arg->width = 0;
	arg->precision = -1;
	arg->length = no_lenght;
}

static int	print_arg(t_arg *arg, char spec, va_list ap)
{
	if (spec == 'c' || spec == '%')
		return (display_c(arg, ap, spec == '%' ? 1 : 0));
	if (spec == 's')
		return (display_s(arg, ap));
	if (spec == 'd' || spec == 'i')
		return (display_d(arg, ap));
	if (spec == 'u')
		return (display_u(arg, ap));
	if (spec == 'o')
		return (display_o(arg, ap));
	if (spec == 'x' || spec == 'X')
		return (display_x(arg, ap, spec));
	if (spec == 'p')
		return (display_p(arg, ap));
	if (spec == 'f')
		return (display_f(arg, ap));
	if (spec == 'b')
		return (display_b(arg, ap));
	return (-1);
}

static int	assemble_arg(char **format, va_list ap)
{
	int		ret;
	t_arg	arg;

	initialize(&arg);
	get_flags(&arg, format);
	get_width(&arg, format, ap);
	get_precision(&arg, format, ap);
	get_length(&arg, format);
	arg.zero_pad = arg.precision >= 0 && **format != 'f'
	&& **format != 'c' && **format != 's' && **format != '%'
	? 0 : arg.zero_pad;
	arg.zero_pad = arg.left_adj ? 0 : arg.zero_pad;
	arg.pad = arg.zero_pad ? '0' : ' ';
	arg.blank = arg.sign ? 0 : arg.blank;
	if ((ret = print_arg(&arg, **format, ap)) == -1)
		return (0);
	*format += 1;
	return (ret);
}

static int	print(char *format, va_list ap)
{
	int ret;

	ret = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ret += assemble_arg(&format, ap);
		}
		else
		{
			write(1, format, 1);
			format++;
			ret++;
		}
	}
	return (ret);
}

int			ft_printf(const char *format, ...)
{
	int		ret;
	va_list	ap;

	va_start(ap, format);
	ret = print((char *)format, ap);
	va_end(ap);
	return (ret);
}

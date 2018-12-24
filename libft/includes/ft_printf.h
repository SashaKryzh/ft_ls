/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 14:33:06 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/11 14:33:07 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct	s_arg
{
	int		alter;
	int		zero_pad;
	char	pad;
	int		left_adj;
	int		sign;
	int		blank;
	char	pref;
	int		width;
	int		precision;
	int		nlen;
	enum	e_length
	{
		no_lenght,
		hh,
		h,
		l,
		ll,
		j,
		z,
		L
	}		length;
}				t_arg;

int				ft_printf(const char *format, ...);

/*
** Parser
*/

void			get_flags(t_arg *arg, char **format);
void			get_width(t_arg *arg, char **format, va_list ap);
void			get_precision(t_arg *arg, char **format, va_list ap);
void			get_length(t_arg *arg, char **format);

/*
** Display
*/

int				display_d(t_arg *arg, va_list ap);
int				display_c(t_arg *arg, va_list ap, int percent);
int				display_s(t_arg *arg, va_list ap);
int				display_o(t_arg *arg, va_list ap);
int				display_u(t_arg *arg, va_list ap);
int				display_x(t_arg *arg, va_list ap, char spec);
int				display_p(t_arg *arg, va_list ap);
int				display_f(t_arg *arg, va_list ap);
int				display_b(t_arg *arg, va_list ap);

/*
** Get value
*/

uintmax_t		get_unsinged(t_arg *arg, va_list ap);
intmax_t		get_signed(t_arg *arg, va_list ap);

int				padding(t_arg *arg, char pad, int ret);
char			*d_pref(t_arg *arg, char *s, int start);
void			to_lowercase(char *s);

char			*u_itoa_base(uintmax_t nbr, int base);
char			*ft_dtoa(long double n, int after);

char			*unsigned_precision(char *s, int prec);

#endif

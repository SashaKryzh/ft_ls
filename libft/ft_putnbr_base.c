/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:03:05 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/21 13:03:05 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr_base(intmax_t n, char *base_chars)
{
	int base;
	int ret;

	ret = 0;
	base = ft_strlen(base_chars);
	if (n < 0 && base == 10)
		ft_putchar('-');
	ret += n < 0 && base == 10 ? 1 : 0;
	if (n > base - 1 || n < -base + 1)
		ret += ft_putnbr_base(ft_abs(n / base), base_chars);
	ft_putchar(base_chars[ft_abs(n % base)]);
	ret += 1;
	return (ret);
}

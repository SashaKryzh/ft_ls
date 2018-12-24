/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 19:12:29 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/14 19:12:30 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*unsigned_precision(char *s, int prec)
{
	char	*tmp;
	int		len;
	int		i;

	len = ft_strlen(s);
	if (prec < len)
		return (s);
	tmp = ft_strnew(prec);
	i = 0;
	while (i < prec - len)
	{
		tmp[i] = '0';
		i++;
	}
	ft_strcpy(&tmp[i], s);
	free(s);
	return (tmp);
}

int			padding(t_arg *arg, char pad, int ret)
{
	int i;

	i = 0;
	if (arg->pref)
	{
		write(1, &arg->pref, 1);
		i++;
	}
	while (i < arg->width - ret)
	{
		write(1, &pad, 1);
		i++;
	}
	return (i);
}

void		to_lowercase(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		s[i] = ft_tolower(s[i]);
		i++;
	}
}

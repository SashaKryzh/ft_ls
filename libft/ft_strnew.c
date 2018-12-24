/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 11:10:28 by okryzhan          #+#    #+#             */
/*   Updated: 2018/10/23 11:10:29 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *res;

	if ((res = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	while (size > 0)
	{
		res[size] = '\0';
		size--;
	}
	res[size] = '\0';
	return (res);
}

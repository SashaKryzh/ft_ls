/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 09:43:57 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/18 09:43:58 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		parse_flags(char *s)
{
	int i;

	if (!s[1])
		return (0);
	i = 0;
	while (s[++i])
	{
		if (!ft_contains(OPTS, s[i]))
			exit_func("Invalid option");
		if (s[i] == 'R')
			g_flags.rec = 1;
		if (s[i] == 'a')
			g_flags.a = 1;
		if (s[i] == 'r')
			g_flags.rev = 1;
		if (s[i] == 't')
			g_flags.t = 1;
		if (s[i] == '1')
			g_flags.one = 1;
	}
	return (1);
}

void	parse_names(t_names **names, char *s)
{
	t_names	*new;

	new = (t_names *)malloc(sizeof(t_names));
	ft_bzero(new, sizeof(t_names));
	ft_strcpy(new->name, s);
	new->next = *names;
	*names = new;
}

void	get_args(int ac, char *av[], t_names **names)
{
	int		i;

	i = 0;
	*names = NULL;
	while (++i < ac && av[i][0] == '-')
		if (!parse_flags(av[i]))
			break ;
	t_print_flags(); //
	while (i < ac)
		parse_names(names, av[i++]);
	t_print_names(*names); //
}

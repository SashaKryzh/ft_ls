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
		if (s[i] == 'l')
			g_flags.l = 1;
	}
	return (1);
}

void	parse_args(t_ls_arg **args, char *s)
{
	t_ls_arg	*new;

	new = (t_ls_arg *)ft_memalloc(sizeof(t_ls_arg));
	new->arg = ft_strdup(s);
	new->next = *args;
	*args = new;
}

void	get_ls_arg(int ac, char *av[], t_ls_arg **args)
{
	int		i;

	i = 0;
	*args = NULL;
	while (++i < ac && av[i][0] == '-')
		if (!parse_flags(av[i]))
			break ;
	t_print_flags(); //
	while (i < ac)
		parse_args(args, av[i++]);
	t_print_ls_arg(*args); //
}

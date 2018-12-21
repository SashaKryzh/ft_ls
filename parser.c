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

static void	illegal_option(char opt)
{
	ft_printf("ft_ls: illegal option -- %c\n", opt);
	ft_printf("%s\n", USAGE);
	exit(0);
}

static void	parse_flags_2(char opt)
{
	if (opt == 'U')
		g_flags.U = 1;
	if (opt == 'o')
		g_flags.o = 1;
	if (opt == 'g')
		g_flags.g = 1;
	if (opt == 'm')
		g_flags.m = 1;
}

int			parse_flags(char *s)
{
	int i;

	if (!s[1])
		return (0);
	i = 0;
	while (s[++i])
	{
		if (!ft_contains(OPTS, s[i]))
			illegal_option(s[i]);
		if (s[i] == 'R')
			g_flags.rec = 1;
		if (s[i] == 'a')
			g_flags.a = 1;
		if (s[i] == 'r')
			g_flags.rev = 1;
		if (s[i] == 't')
			g_flags.t = 1;
		if (s[i] == 'l')
			g_flags.l = 1;
		if (s[i] == '1')
			g_flags.one = 1;
		parse_flags_2(s[i]);
	}
	return (1);
}

void		parse_args(t_ls_arg **args, char *s)
{
	t_ls_arg	*new;

	new = (t_ls_arg *)ft_memalloc(sizeof(t_ls_arg));
	new->arg = ft_strdup(s);
	new->next = *args;
	*args = new;
	g_cnt_args += 1;
}

void		get_ls_arg(int ac, char *av[], t_ls_arg **args)
{
	int		i;

	i = 0;
	*args = NULL;
	while (++i < ac && av[i][0] == '-')
		if (!parse_flags(av[i]))
			break ;
	while (i < ac)
		parse_args(args, av[i++]);
}

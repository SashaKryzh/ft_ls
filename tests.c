
#include "ft_ls.h"

void	t_print_flags(void)
{
	ft_printf("[R: %d], [a: %d], [r: %d], [t: %d], [1: %d] [l: %d]\n", g_flags.rec, g_flags.a, g_flags.rev, g_flags.t, g_flags.one, g_flags.l);
}

void	t_print_ls_arg(t_ls_arg *args)
{
	while (args)
	{
		ft_printf("%s\n", args->arg);
		args = args->next;
	}
}

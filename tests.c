
#include "ft_ls.h"

void	print_flags(t_flags *flags)
{
	ft_printf("[R: %d], [a: %d], [r: %d], [t: %d], [1: %d]\n", flags->rec, flags->a, flags->rev, flags->t, flags->one);
}

void	print_names(t_names *names)
{
	while (names)
	{
		ft_printf("%s\n", names->name);
		names = names->next;
	}
	ft_printf("\n");
}

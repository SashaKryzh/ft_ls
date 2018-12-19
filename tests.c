
#include "ft_ls.h"

void	t_print_flags(void)
{
	ft_printf("[R: %d], [a: %d], [r: %d], [t: %d], [1: %d]\n", g_flags.rec, g_flags.a, g_flags.rev, g_flags.t, g_flags.one);
}

void	t_print_names(t_names *names)
{
	while (names)
	{
		ft_printf("%s\n", names->name);
		names = names->next;
	}
	ft_printf("\n");
}

// void	t_print_dirs(t_dir *dirs)
// {
// 	ft_printf("\n!!! DIRS !!!\n");
// 	while (dirs)
// 	{
// 		ft_printf("%s\n", dirs->name);
// 		dirs = dirs->next;
// 	}
// }

void	t_print_files(t_file *files)
{
	ft_printf("\n!!! FILES !!!\n");
	while (files)
	{
		ft_printf("%10s %d\n", files->name, S_ISDIR(files->st.st_mode));
		files = files->next;
	}
}
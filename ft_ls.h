
#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

# include <dirent.h>
# include <sys/stat.h>

# define OPTS "1Rart"

typedef struct		s_flags
{
	int one;
	int	rec;
	int	a;
	int rev;
	int t;
}					t_flags;

#endif
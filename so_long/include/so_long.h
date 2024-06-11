
#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_map
{
	int	len;
	int height;
	char **map;
	int player_x;
	int player_y;
	int goal;
	int score; //has to be initialized to 0
	
}		t_map;

#endif

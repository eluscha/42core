
#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_map
{
	int	width;
	int height;
	char **map;
	int player[2]; //init to 0,0
	int exit[2]; //init to 0,0
	int goal;
	int score; //has to be initialized to 0
}		t_map;

void get_map(t_map *mapdata, char *oldline, int fd, int size);
void    close_free_exit(int fd, char **map, char *line, int excode);
int valid_map(t_map *mapdata);
void init_mapdata(t_map *mapdata);

#endif

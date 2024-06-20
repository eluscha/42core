
#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>
#include "MLX42.h"
#include <memory.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"


# define UNIT_SIZE 50

typedef struct s_map
{
	char **map;
	int width;
	int height;
	int px; //init to 0
	int py;
	int ex;
	int ey;
	bool exit; //init to 0
	int goal;
	int score; //has to be initialized to 0
	size_t moves;
	mlx_t*    mlx;
	mlx_image_t	*img_wall;
	mlx_image_t	*img_exit;
	mlx_image_t	*img_pl1;
	mlx_image_t	*img_pl2;
	mlx_image_t	*img_cllct;
	mlx_image_t	*img_enemy;
	size_t time;
}		t_map;

typedef struct s_pos
{
	int	x;
	int y;
	struct s_pos *next; 
}		t_pos;

void get_map(t_map *mapdata, char *oldline, int fd, int size);
void    close_free_exit(int fd, char **map, char *line, int excode);
int valid_map(t_map *mapdata);
void init_mapdata(t_map *mapdata);
void free_map(char **map);
int valid_path(t_map mapdata);
t_pos *create_node(int x, int y);
char **copy_map(t_map *mapdatat);
t_pos *add_nbs(char **map, int x, int y, t_pos* tail);
int32_t	draw_map(t_map *mapdata);
void	key_hook(mlx_key_data_t keydata, void* param);
void	hook(void* param);

#endif

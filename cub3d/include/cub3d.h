
/*credits for sprite graphics:
- docokogo.itch.io/ for the background
- caz-creates-games.itch.io/ducky-2 for the duck 
- wall ?
- bdragon1727.itch.io/pixel-holy-spell-effect-32x32-pack-3 black hole*/

#ifndef CUB3D_H
# define CUB3D_H


# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "MLX42.h"
# include "libft.h"
# include <float.h>
# include <math.h>

# define screenWidth 640
# define screenHeight 480

typedef struct s_tx
{
	mlx_texture_t	*n;
	mlx_texture_t	*s;
	mlx_texture_t	*e;
	mlx_texture_t	*w;
}		t_tx;

typedef struct s_map
{
	char			**map;
	int				width;
	int				height;
	double			px;
	double			py;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_tx			*txtr;
}		t_map;

/*main.c*/
int		open_mapfile(char *path);
void	init_mapdata(t_map *mapdata);
void	get_map(t_map *mapdata, char *oldline, int fd, int size);
void	close_free_exit(int fd, char **map, char *line, int excode);
/*map_helpers.c*/
void	free_map(char **map);
/*check_map.c*/
int		check_valid_map(t_map *mapdata);
int		check_other_lines(t_map *mapdata);
int		check_char(t_map *mapdata, char *line, int idx, int lnum);
int		check_last_line(t_map *mapdata, int num);

/*draw_map.c*/
void	error_exit(t_map *mapdata);
int32_t	draw_map(t_map *mapdata);
//void	key_hook(mlx_key_data_t keydata, void *param);
void	hook(void *param);

/*txtr_img_utils.c*/
void	init_txtr(t_map *md, t_tx *t);
void	make_images(t_map *md);
void	delete_textures(t_tx *t);
void	delete_images(t_map *md);
/*draw_fts.c*/
void	draw_line(t_map *md, int x, int height, int side, int hit);
/*move_player.c*/
void	move_left(t_map *md);
void	move_up(t_map *md);
void	move_right(t_map *md);
void	move_down(t_map *md);

#endif


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
	int enx;
	int eny;
	bool exit; //init to 0
	int goal;
	int score; //has to be initialized to 0
	int go;
	size_t moves;
	mlx_t*    mlx;
	mlx_image_t	*img_bckgr;
	mlx_image_t	*img_wall;
	mlx_image_t	*img_exit[4];
	mlx_image_t	*img_pl[2];
	mlx_image_t *img_go;
	mlx_image_t	*img_cllct;
	mlx_image_t	*img_enemy;
	size_t time;
}		t_map;

typedef struct s_pos
{
	int	x;
	int y;
	char	val;
	struct s_pos *next; 
}		t_pos;

typedef struct s_textures
{
	mlx_texture_t* bckgr;
	mlx_texture_t* wall;
	mlx_texture_t* cllct;
    mlx_texture_t* pl1;
	mlx_texture_t* pl2;
	mlx_texture_t* pl3;
	mlx_texture_t* e1;
	mlx_texture_t* e2;
	mlx_texture_t* e3;
	mlx_texture_t* e4;
	mlx_texture_t* enemy;
}		t_textures;

int open_mapfile(char *path);
void get_map(t_map *mapdata, char *oldline, int fd, int size);
void    close_free_exit(int fd, char **map, char *line, int excode);
int check_valid_map(t_map *mapdata);
int check_other_lines(t_map *mapdata);
int check_char(t_map *mapdata, char *line, int idx, int lnum);
int check_last_line(t_map *mapdata, int num);
void init_mapdata(t_map *mapdata);
void free_map(char **map);
int check_valid_path(t_map mapdata);
int check_current_head(t_map *md, t_pos **h_adr, t_pos **t_adr);
t_pos *create_node(int x, int y, char c);
t_pos *list_pop(t_pos *head);
char **copy_map(t_map *mapdatat);
t_pos *add_nbs(char **map, int x, int y, t_pos* tail);
int32_t	draw_map(t_map *mapdata);
void	key_hook(mlx_key_data_t keydata, void* param);
void	hook(void* param);
int dist(int x1, int y1, int x2, int y2);

void init_txtr(t_map *md, t_textures *t);
void make_images(t_map *md, t_textures *txtr);
void	delete_textures(t_textures *t);
void	delete_images(t_map *md);

void	move_enemy(t_map *md, int intrvl);
void	collect_item(t_map *md);
void	exit_animation(t_map *md);
void check_exiting(t_map *md);

void	draw_player(t_map *md);
void	draw_10CE(t_map *md);
void draw_exit(t_map *md, int idx, int lnum);
void	place_enemy(t_map *md);

void	move_left(t_map *md);
void	move_up(t_map *md);
void	move_right(t_map *md);
void	move_down(t_map *md);
void	move_player(t_map *md, int addx, int addy);

void	gameover(t_map *md);

#endif

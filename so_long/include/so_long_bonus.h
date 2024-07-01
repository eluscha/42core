/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:56:30 by eusatiko          #+#    #+#             */
/*   Updated: 2024/07/01 12:40:49 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*credits for sprite graphics:
- docokogo.itch.io/ for the background
- caz-creates-games.itch.io/ducky-2 for the duck (wall)
- totuslotus.itch.io/small-platformer-pack for the player
- bdragon1727.itch.io/basic-pixel-health-bar-and-scroll-bar exit animation
- bdragon1727.itch.io/pixel-holy-spell-effect-32x32-pack-3 black hole*/

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <stdio.h>
# include <memory.h> //why
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "MLX42.h"
# include "libft.h"

# define UNIT_SIZE 50

typedef struct s_tx
{
	mlx_texture_t	*bckgr;
	mlx_texture_t	*wall;
	mlx_texture_t	*cllct;
	mlx_texture_t	*pl1;
	mlx_texture_t	*pl2;
	mlx_texture_t	*pl3;
	mlx_texture_t	*e1;
	mlx_texture_t	*e2;
	mlx_texture_t	*e3;
	mlx_texture_t	*e4;
	mlx_texture_t	*enemy;
}		t_tx;

typedef struct s_map
{
	char		**map;
	int			width;
	int			height;
	int			px;
	int			py;
	int			enx;
	int			eny;
	bool		exit;
	int			goal;
	int			score;
	int			go;
	size_t		moves;
	size_t		time;
	mlx_t		*mlx;
	t_tx		*txtr;
	mlx_image_t	*img_bckgr;
	mlx_image_t	*img_wall;
	mlx_image_t	*img_exit[4];
	mlx_image_t	*img_pl[2];
	mlx_image_t	*img_go;
	mlx_image_t	*img_cllct;
	mlx_image_t	*img_enemy;
}		t_map;

typedef struct s_pos
{
	int				x;
	int				y;
	char			val;
	struct s_pos	*next; 
}		t_pos;

/*main.c*/
int		open_mapfile(char *path);
void	init_mapdata(t_map *mapdata);
void	get_map(t_map *mapdata, char *oldline, int fd, int size);
void	close_free_exit(int fd, char **map, char *line, int excode);
/*map_helpers.c*/
char	**copy_map(t_map *mapdata);
void	free_map(char **map);
/*check_map.c*/
int		check_valid_map(t_map *mapdata);
int		check_other_lines(t_map *mapdata);
int		check_char(t_map *mapdata, char *line, int idx, int lnum);
int		check_last_line(t_map *mapdata, int num);
/*check_path.c*/
int		check_valid_path(t_map mapdata);
t_pos	*create_node(int x, int y, char c);
int		check_current_head(t_map *md, t_pos **h_adr, t_pos **t_adr);
t_pos	*add_nbs(char **map, int x, int y, t_pos *tail);
t_pos	*list_pop(t_pos *head);
/*draw_map.c*/
void	error(t_map *mapdata);
int32_t	draw_map(t_map *mapdata);
void	key_hook(mlx_key_data_t keydata, void *param);
void	hook(void *param);
int		dist(int x1, int y1, int x2, int y2);
/*txtr_img_utils.c*/
void	init_txtr(t_map *md, t_tx *t);
void	make_images(t_map *md);
void	delete_textures(t_tx *t);
void	delete_images(t_map *md);
/*draw_fts.c*/
void	draw_10ce(t_map *md);
void	draw_check_error(t_map *md, mlx_image_t *img, int x, int y);
void	draw_exit(t_map *md, int idx, int lnum);
void	draw_player(t_map *md);
void	place_enemy(t_map *md);
/*hook_fts.c*/
void	collect_item(t_map *md);
void	move_enemy(t_map *md, int intrvl);
void	gameover(t_map *md);
void	exit_animation(t_map *md);
int		check_exiting(t_map *md);
/*move_player.c*/
void	move_left(t_map *md);
void	move_up(t_map *md);
void	move_right(t_map *md);
void	move_down(t_map *md);
void	move_player(t_map *md, int addx, int addy);

#endif

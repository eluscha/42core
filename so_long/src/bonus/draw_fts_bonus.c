/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fts_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:49:58 by eusatiko          #+#    #+#             */
/*   Updated: 2024/06/28 12:30:04 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	draw_10ce(t_map *md)
{
	int	idx;
	int	lnum;

	lnum = -1;
	while (++lnum < md->height)
	{
		idx = -1;
		while (++idx < md->width)
		{
			draw_check_error(md, md->img_bckgr, idx, lnum);
			if (md->map[lnum][idx] == '1')
				draw_check_error(md, md->img_wall, idx, lnum);
			else if (md->map[lnum][idx] == 'C')
				draw_check_error(md, md->img_cllct, idx, lnum);
			else if (md->map[lnum][idx] == 'E')
				draw_exit(md, idx, lnum);
		}
	}
}

void	draw_check_error(t_map *md, mlx_image_t *img, int x, int y)
{
	if (mlx_image_to_window(md->mlx, img, x * UNIT_SIZE, y * UNIT_SIZE) < 0)
		error(md);
}

void	draw_exit(t_map *md, int idx, int lnum)
{
	if (mlx_image_to_window(md->mlx, md->img_exit[0], \
		idx * UNIT_SIZE, lnum * UNIT_SIZE) < 0)
		error(md);
	if (mlx_image_to_window(md->mlx, md->img_exit[1], \
		idx * UNIT_SIZE, lnum * UNIT_SIZE) < 0)
		error(md);
	if (mlx_image_to_window(md->mlx, md->img_exit[2], \
		idx * UNIT_SIZE, lnum * UNIT_SIZE) < 0)
		error(md);
	if (mlx_image_to_window(md->mlx, md->img_exit[3], \
		idx * UNIT_SIZE, lnum * UNIT_SIZE) < 0)
		error(md);
}

void	draw_player(t_map *md)
{
	if (mlx_image_to_window(md->mlx, md->img_pl[0], \
		md->px * UNIT_SIZE, md->py * UNIT_SIZE) < 0)
		error(md);
	if (mlx_image_to_window(md->mlx, md->img_pl[1], \
		md->px * UNIT_SIZE, md->py * UNIT_SIZE) < 0)
		error(md);
	md->img_pl[1]->enabled = 0;
}

void	place_enemy(t_map *md)
{
	int	tries;
	int	ex; 
	int	ey;

	tries = -1;
	while (++tries < 1000)
	{
		ex = rand() % md->width;
		ey = rand() % md->height;
		if (md->map[ey][ex] == '0' && dist(ex, ey, md->px, md->py) > 2)
			break ;
	}
	if (tries < 1000)
	{
		md->enx = ex;
		md->eny = ey;
		if (mlx_image_to_window(md->mlx, md->img_enemy, \
			md->enx * UNIT_SIZE, md->eny * UNIT_SIZE) < 0)
			error(md);
	}
}

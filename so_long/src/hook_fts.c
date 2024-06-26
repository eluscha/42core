/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:52:14 by eusatiko          #+#    #+#             */
/*   Updated: 2024/06/26 11:52:22 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collect_item(t_map *md)
{
	size_t i;
	
	if (md->map[md->py][md->px] == 'C')
	{
		md->map[md->py][md->px] = '0';
		md->score++;
		i = -1;
		while (++i < md->img_cllct->count)
		{
			if (md->img_cllct->instances[i].x == \
			md->px*UNIT_SIZE && md->img_cllct->instances[i].y == md->py*UNIT_SIZE)
				md->img_cllct->instances[i].enabled = 0;
		}
	}
}

void	move_enemy(t_map *md, int intrvl)
{
	int addx;
	int addy;

	if (md->enx && md->time % intrvl == 0)
	{
		addx = rand() % 3 - 1;
		addy = rand() % 3 - 1;
		if (md->map[md->eny + addy][md->enx + addx] == '0' )
		{
			md->enx += addx;
			md->img_enemy->instances[0].x += UNIT_SIZE * addx;
			md->eny += addy;
			md->img_enemy->instances[0].y += UNIT_SIZE * addy;
		}
	}
}

void	gameover(t_map *md)
{
	static int addx;
	static int addy;

	if (!addx)
	{
		addx = (md->px * UNIT_SIZE - md->enx * UNIT_SIZE) / 10;
		addy = (md->py * UNIT_SIZE - md->eny * UNIT_SIZE) / 10;
		md->go = 1;
	}
	if (md->time % 10 != 0)
		return ;
	if (md->go == 11)
	{
		md->img_pl[0]->enabled = 0;
		md->img_pl[1]->enabled = 0;
		if (mlx_image_to_window(md->mlx, md->img_go, \
			md->enx * UNIT_SIZE, md->eny * UNIT_SIZE) < 0)
			error(md);
		md->go++;
		return ;
	}
	else if (md->go == 12)
		mlx_close_window(md->mlx);
	move_player(md, addx, addy);
	md->go++;
}

void	exit_animation(t_map *md)
{
	static int i;
	int idx;
	
	idx = -1;
	if (md->time % 10 == 0)
	{
		while (++idx < 4)
		{
			if (idx == i)
				md->img_exit[idx]->enabled = 1;
			else
				md->img_exit[idx]->enabled = 0;
		}
		if (i == 3)
			i = 0;
		i++;
	}
}

void check_exiting(t_map *md)
{
	if (md->map[md->py][md->px] != 'E')
		return ;
	if (md->score != md->goal)
		return ;
	if (mlx_image_to_window(md->mlx, md->img_go, \
		md->enx * UNIT_SIZE, md->eny * UNIT_SIZE) < 0)
		error(md);
	mlx_close_window(md->mlx);
}

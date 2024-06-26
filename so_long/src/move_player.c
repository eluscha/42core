/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:55:02 by eusatiko          #+#    #+#             */
/*   Updated: 2024/06/26 11:55:04 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_left(t_map *md)
{
	if (md->map[md->py][md->px-1] == '1')
		return ;
	md->px--;
	md->moves++;
	ft_printf("Moves: %i\n", md->moves);
	md->img_pl[1]->enabled = !md->img_pl[1]->enabled;
	md->img_pl[0]->enabled = !md->img_pl[0]->enabled;
	md->img_pl[0]->instances[0].x -= UNIT_SIZE;
	md->img_pl[1]->instances[0].x -= UNIT_SIZE;
}


void	move_up(t_map *md)
{
	if (md->map[md->py-1][md->px] == '1')
		return ;
	md->py--;
	md->moves++;
	ft_printf("Moves: %i\n", md->moves);
	md->img_pl[1]->enabled = !md->img_pl[1]->enabled;
	md->img_pl[0]->enabled = !md->img_pl[0]->enabled;
	md->img_pl[0]->instances[0].y -= UNIT_SIZE;
	md->img_pl[1]->instances[0].y -= UNIT_SIZE;
}

void	move_right(t_map *md)
{
	if (md->map[md->py][md->px+1] == '1')
		return ;
	md->px++;
	md->moves++;
	ft_printf("Moves: %i\n", md->moves);
	md->img_pl[1]->enabled = !md->img_pl[1]->enabled;
	md->img_pl[0]->enabled = !md->img_pl[0]->enabled;
	md->img_pl[0]->instances[0].x += UNIT_SIZE;
	md->img_pl[1]->instances[0].x += UNIT_SIZE;

}

void	move_down(t_map *md)
{
	if (md->map[md->py+1][md->px] == '1')
		return ;
	md->py++;
	md->moves++;
	ft_printf("Moves: %i\n", md->moves);
	md->img_pl[1]->enabled = !md->img_pl[1]->enabled;
	md->img_pl[0]->enabled = !md->img_pl[0]->enabled;
	md->img_pl[0]->instances[0].y += UNIT_SIZE;
	md->img_pl[1]->instances[0].y += UNIT_SIZE;
}

void	move_player(t_map *md, int addx, int addy)
{
	md->img_pl[0]->instances[0].x -= addx;
	md->img_pl[1]->instances[0].x -= addx;
	md->img_pl[0]->instances[0].y -= addy;
	md->img_pl[1]->instances[0].y -= addy;
}

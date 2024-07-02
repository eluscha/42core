/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:52:14 by eusatiko          #+#    #+#             */
/*   Updated: 2024/07/02 10:23:53 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collect_item(t_map *md)
{
	size_t	i;

	if (md->map[md->py][md->px] == 'C')
	{
		md->map[md->py][md->px] = '0';
		md->score++;
		i = -1;
		while (++i < md->img_cllct->count)
		{
			if (md->img_cllct->instances[i].x == md->px * UNIT_SIZE \
				&& md->img_cllct->instances[i].y == md->py * UNIT_SIZE)
				md->img_cllct->instances[i].enabled = 0;
		}
	}
}

int	check_exiting(t_map *md)
{
	static size_t	time;

	if (md->map[md->py][md->px] != 'E')
		return (1);
	if (md->score != md->goal)
		return (1);
	if (!time)
	{
		time = md->time;
		md->exit = 1;
		ft_printf("You won!\n");
	}
	else if (md->time == time + 20)
		mlx_close_window(md->mlx);
	return (0);
}

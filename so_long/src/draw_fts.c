/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:49:58 by eusatiko          #+#    #+#             */
/*   Updated: 2024/06/28 12:33:50 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
				draw_check_error(md, md->img_exit, idx, lnum);
		}
	}
}

void	draw_check_error(t_map *md, mlx_image_t *img, int x, int y)
{
	if (mlx_image_to_window(md->mlx, img, x * UNIT_SIZE, y * UNIT_SIZE) < 0)
		error(md);
}

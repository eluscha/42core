/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:50:17 by eusatiko          #+#    #+#             */
/*   Updated: 2024/07/01 10:41:28 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error(t_map *mapdata)
{
	ft_printf("%s", mlx_strerror(mlx_errno));
	if (mapdata->txtr)
	{
		delete_images(mapdata);
		delete_textures(mapdata->txtr);
	}
	if (mapdata->mlx)
		mlx_terminate(mapdata->mlx);
	free_map(mapdata->map);
	exit(EXIT_FAILURE);
}

int32_t	draw_map(t_map *md)
{
	t_tx	txtr;

	md->mlx = mlx_init(md->width * UNIT_SIZE, md->height * UNIT_SIZE, \
						"Game", false);
	if (!md->mlx)
		error(md);
	init_txtr(md, &txtr);
	make_images(md);
	draw_10ce(md);
	draw_check_error(md, md->img_pl, md->px, md->py);
	mlx_key_hook(md->mlx, &key_hook, md);
	mlx_loop_hook(md->mlx, &hook, md);
	ft_printf("Moves: %i\n", md->moves);
	mlx_loop(md->mlx);
	delete_images(md);
	delete_textures(&txtr);
	mlx_terminate(md->mlx);
	free_map(md->map);
	return (EXIT_SUCCESS);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*md;

	md = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(md->mlx);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_left(md);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_up(md);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_right(md);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_down(md);
}

void	hook(void *param)
{
	t_map	*md;

	md = param;
	md->time++;
	if (check_exiting(md) == 0)
		return ;
	collect_item(md);
}

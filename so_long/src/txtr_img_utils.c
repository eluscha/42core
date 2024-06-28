/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txtr_img_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:55:14 by eusatiko          #+#    #+#             */
/*   Updated: 2024/06/28 12:32:20 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_txtr(t_map *md, t_tx *t)
{
	t->bckgr = mlx_load_png("./textures/Floor.png");
	t->wall = mlx_load_png("./textures/ducky.png");
	t->cllct = mlx_load_png("./textures/cllct.png");
	t->pl = mlx_load_png("./textures/pl1.png");
	t->e = mlx_load_png("./textures/e1.png");
	if (!t->bckgr || !t->wall || !t->cllct)
		error(md);
	if (!t->pl || !t->e)
		error(md);
	md->txtr = t;
}

void	make_images(t_map *md)
{
	t_tx	*txtr;

	txtr = md->txtr;
	md->img_bckgr = mlx_texture_to_image(md->mlx, txtr->bckgr);
	md->img_wall = mlx_texture_to_image(md->mlx, txtr->wall);
	md->img_cllct = mlx_texture_to_image(md->mlx, txtr->cllct);
	if (!md->img_bckgr || !md->img_wall || !md->img_cllct)
		error(md);
	md->img_pl = mlx_texture_to_image(md->mlx, txtr->pl);
	md->img_exit = mlx_texture_to_image(md->mlx, txtr->e);
	if (!md->img_pl || !md->img_exit)
		error(md);
}

void	delete_textures(t_tx *t)
{
	if (t->bckgr)
		mlx_delete_texture(t->bckgr);
	if (t->wall)
		mlx_delete_texture(t->wall);
	if (t->cllct)
		mlx_delete_texture(t->cllct);
	if (t->pl)
		mlx_delete_texture(t->pl);
	if (t->e)
		mlx_delete_texture(t->e);
}

void	delete_images(t_map *md)
{
	if (md->img_bckgr)
		mlx_delete_image(md->mlx, md->img_bckgr);
	if (md->img_wall)
		mlx_delete_image(md->mlx, md->img_wall);
	if (md->img_cllct)
		mlx_delete_image(md->mlx, md->img_cllct);
	if (md->img_pl)
		mlx_delete_image(md->mlx, md->img_pl);
	if (md->img_exit)
		mlx_delete_image(md->mlx, md->img_exit);
}

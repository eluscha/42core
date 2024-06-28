/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txtr_img_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:55:14 by eusatiko          #+#    #+#             */
/*   Updated: 2024/06/28 12:29:13 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_txtr(t_map *md, t_tx *t)
{
	t->bckgr = mlx_load_png("./textures/Floor.png");
	t->wall = mlx_load_png("./textures/ducky.png");
	t->cllct = mlx_load_png("./textures/cllct.png");
	t->pl1 = mlx_load_png("./textures/pl1.png");
	t->pl2 = mlx_load_png("./textures/pl2.png");
	t->pl3 = mlx_load_png("./textures/go.png");
	t->e1 = mlx_load_png("./textures/e1.png");
	t->e2 = mlx_load_png("./textures/e2.png");
	t->e3 = mlx_load_png("./textures/e3.png");
	t->e4 = mlx_load_png("./textures/e4.png");
	t->enemy = mlx_load_png("./textures/bh.png");
	if (!t->bckgr || !t->wall || !t->cllct)
		error(md);
	if (!t->pl1 || !t->pl2 || !t->pl3)
		error(md);
	if (!t->e1 || !t->e2 || !t->e3 || !t->e4)
		error(md);
	if (!t->enemy)
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
	md->img_pl[0] = mlx_texture_to_image(md->mlx, txtr->pl1);
	md->img_pl[1] = mlx_texture_to_image(md->mlx, txtr->pl2);
	md->img_go = mlx_texture_to_image(md->mlx, txtr->pl3);
	if (!md->img_bckgr || !md->img_wall || !md->img_cllct)
		error(md);
	if (!md->img_pl[0] || !md->img_pl[1] || !md->img_go)
		error(md);
	md->img_exit[0] = mlx_texture_to_image(md->mlx, txtr->e1);
	md->img_exit[1] = mlx_texture_to_image(md->mlx, txtr->e2);
	md->img_exit[2] = mlx_texture_to_image(md->mlx, txtr->e3);
	md->img_exit[3] = mlx_texture_to_image(md->mlx, txtr->e4);
	if (!md->img_exit[0] || !md->img_exit[1])
		error(md);
	if (!md->img_exit[2] || !md->img_exit[3])
		error(md);
	md->img_enemy = mlx_texture_to_image(md->mlx, txtr->enemy);
	if (!md->img_enemy)
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
	if (t->pl1)
		mlx_delete_texture(t->pl1);
	if (t->pl2)
		mlx_delete_texture(t->pl2);
	if (t->pl3)
		mlx_delete_texture(t->pl3);
	if (t->e1)
		mlx_delete_texture(t->e1);
	if (t->e2)
		mlx_delete_texture(t->e2);
	if (t->e3)
		mlx_delete_texture(t->e3);
	if (t->e4)
		mlx_delete_texture(t->e4);
	if (t->enemy)
		mlx_delete_texture(t->enemy);
}

void	delete_images(t_map *md)
{
	if (md->img_bckgr)
		mlx_delete_image(md->mlx, md->img_bckgr);
	if (md->img_wall)
		mlx_delete_image(md->mlx, md->img_wall);
	if (md->img_cllct)
		mlx_delete_image(md->mlx, md->img_cllct);
	if (md->img_pl[0])
		mlx_delete_image(md->mlx, md->img_pl[0]);
	if (md->img_pl[1])
		mlx_delete_image(md->mlx, md->img_pl[1]);
	if (md->img_go)
		mlx_delete_image(md->mlx, md->img_go);
	if (md->img_exit[0])
		mlx_delete_image(md->mlx, md->img_exit[0]);
	if (md->img_exit[1])
		mlx_delete_image(md->mlx, md->img_exit[1]);
	if (md->img_exit[2])
		mlx_delete_image(md->mlx, md->img_exit[2]);
	if (md->img_exit[3])
		mlx_delete_image(md->mlx, md->img_exit[3]);
	if (md->img_enemy)
		mlx_delete_image(md->mlx, md->img_enemy);
}

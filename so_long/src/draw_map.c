#include "so_long.h"


static void error(t_map *mapdata)
{
	puts(mlx_strerror(mlx_errno));
	free_map(mapdata->map);
	exit(EXIT_FAILURE);
}

void	key_hook(mlx_key_data_t keydata, void* param)
{
	t_map* md;

	md = param;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_left(md);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_up(md);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_right(md);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_down(md);
}

void	hook(void* param)
{
	t_map* md;

	md = param;
	md->time++;
	if (mlx_is_key_down(md->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(md->mlx);
	collect_item(md);
	move_enemy(md, 50);
	exit_animation(md);
}

int32_t	draw_map(t_map *md)
{
	t_textures txtr;

	md->mlx = mlx_init(md->width * UNIT_SIZE, md->height * UNIT_SIZE, "Game", true);
	if (!md->mlx)
		error(md);
	init_txtr(md, &txtr);
	make_images(md, &txtr);
    draw_10CE(md);
	draw_player(md);
	place_enemy(md);
	mlx_key_hook(md->mlx, &key_hook, md);
	mlx_loop_hook(md->mlx, &hook, md);
	ft_printf("Moves: %i\n", md->moves);
	mlx_loop(md->mlx);
	delete_images(md);
	delete_textures(&txtr);
	mlx_terminate(md->mlx);
	return (EXIT_SUCCESS); //still need to free map
}

int dist(int x1, int y1, int x2, int y2)
{
	int dist_x;
	int dist_y;
	
	if (x1 > x2)
		dist_x = x1 - x2;
	else
		dist_x = x2 - x1;

	if (y1 > y2)
		dist_y = y1 - y2;
	else
		dist_y = y2 - y1;

	return (dist_x * dist_x + dist_y * dist_y);
}

void init_txtr(t_map *md, t_textures *t)
{
	t->bckgr = mlx_load_png("./textures/Floor.png");
	t->wall = mlx_load_png("./textures/ducky.png");
	t->cllct = mlx_load_png("./textures/cllct.png");
    t->pl1 = mlx_load_png("./textures/pl1.png");
	t->pl2 = mlx_load_png("./textures/pl2.png");
	t->e1 = mlx_load_png("./textures/e1.png");
	t->e2 = mlx_load_png("./textures/e2.png");
	t->e3 = mlx_load_png("./textures/e3.png");
	t->e4 = mlx_load_png("./textures/e4.png");
	t->enemy = mlx_load_png("./textures/bh.png");
	if (!t->bckgr || !t->wall || !t->cllct)
		error(md);
	if (!t->pl1 || !t->pl2 || !t->e1 || !t->e2 || !t->e3 || !t->e4)
		error(md);
	if (!t->enemy)
		error(md);
}

void make_images(t_map *md, t_textures *txtr)
{
	md->img_bckgr = mlx_texture_to_image(md->mlx, txtr->bckgr);
	md->img_wall = mlx_texture_to_image(md->mlx, txtr->wall);
	md->img_cllct = mlx_texture_to_image(md->mlx, txtr->cllct);
    md->img_pl[0] = mlx_texture_to_image(md->mlx, txtr->pl1);
	md->img_pl[1] = mlx_texture_to_image(md->mlx, txtr->pl2);

	if (!md->img_wall || !md->img_wall || !md->img_cllct)
        error(md);
	if (!md->img_pl[0] || !md->img_pl[1])
		error(md);

	md->img_exit[0] = mlx_texture_to_image(md->mlx, txtr->e1);
	md->img_exit[1] = mlx_texture_to_image(md->mlx, txtr->e2);
	md->img_exit[2] = mlx_texture_to_image(md->mlx, txtr->e3);
	md->img_exit[3] = mlx_texture_to_image(md->mlx, txtr->e4);
	
	if (!md->img_exit[0] || !md->img_exit[1]  || !md->img_exit[2] || !md->img_exit[3])
        error(md);

	md->img_enemy = mlx_texture_to_image(md->mlx, txtr->enemy);

	if (!md->img_enemy)
		error(md);
}

void	delete_textures(t_textures *t)
{
	mlx_delete_texture(t->bckgr);
	mlx_delete_texture(t->wall);
	mlx_delete_texture(t->cllct);
    mlx_delete_texture(t->pl1);
	mlx_delete_texture(t->pl2);
	mlx_delete_texture(t->e1);
	mlx_delete_texture(t->e2);
	mlx_delete_texture(t->e3);
	mlx_delete_texture(t->e4);
	mlx_delete_texture(t->enemy);
}

void	delete_images(t_map *md)
{
	mlx_delete_image(md->mlx, md->img_wall);
    mlx_delete_image(md->mlx, md->img_pl[0]);
	mlx_delete_image(md->mlx, md->img_pl[1]);
	mlx_delete_image(md->mlx, md->img_cllct);
	mlx_delete_image(md->mlx, md->img_enemy);
	mlx_delete_image(md->mlx, md->img_bckgr);

	mlx_delete_image(md->mlx, md->img_exit[0]);
	mlx_delete_image(md->mlx, md->img_exit[1]);
	mlx_delete_image(md->mlx, md->img_exit[2]);
	mlx_delete_image(md->mlx, md->img_exit[3]);
}

void	place_enemy(t_map *md)
{
	int tries = -1;
	int ex; 
	int ey;

	while(++tries < 1000)
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
		if (mlx_image_to_window(md->mlx, md->img_enemy, md->enx*UNIT_SIZE, md->eny*UNIT_SIZE) < 0)
			error(md);
	}
}

void draw_exit(t_map *md, int idx, int lnum)
{
    if (mlx_image_to_window(md->mlx, md->img_exit[0], idx*UNIT_SIZE, lnum*UNIT_SIZE) < 0)
		error(md);
	if (mlx_image_to_window(md->mlx, md->img_exit[1], idx*UNIT_SIZE, lnum*UNIT_SIZE) < 0)
		error(md);
	if (mlx_image_to_window(md->mlx, md->img_exit[2], idx*UNIT_SIZE, lnum*UNIT_SIZE) < 0)
		error(md);
	if (mlx_image_to_window(md->mlx, md->img_exit[3], idx*UNIT_SIZE, lnum*UNIT_SIZE) < 0)
		error(md);
}

void	draw_10CE(t_map *md)
{
	int idx;
	int lnum;
	
	lnum = -1;
	while (++lnum < md->height)
	{
		idx = -1;
		while (++idx < md->width)
		{
			if (mlx_image_to_window(md->mlx, md->img_bckgr, idx*UNIT_SIZE, lnum*UNIT_SIZE) < 0)
		            error(md);
            if (md->map[lnum][idx] == '1')
            {
                if (mlx_image_to_window(md->mlx, md->img_wall, idx*UNIT_SIZE, lnum*UNIT_SIZE) < 0)
		            error(md);
            }
            else if (md->map[lnum][idx] == 'C')
			{
            	if (mlx_image_to_window(md->mlx, md->img_cllct, idx*UNIT_SIZE, lnum*UNIT_SIZE) < 0)
		            error(md);
            }
            else if (md->map[lnum][idx] == 'E')
				draw_exit(md, idx, lnum);
        }
    }
}

void	draw_player(t_map *md)
{
	if (mlx_image_to_window(md->mlx, md->img_pl[0], md->px*UNIT_SIZE, md->py*UNIT_SIZE) < 0)
		error(md);
	if (mlx_image_to_window(md->mlx, md->img_pl[1], md->px*UNIT_SIZE, md->py*UNIT_SIZE) < 0)
		error(md);
	md->img_pl[1]->enabled = 0;
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
			if (md->img_cllct->instances[i].x == md->px*UNIT_SIZE && md->img_cllct->instances[i].y == md->py*UNIT_SIZE)
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
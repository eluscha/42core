#include "so_long.h"


static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	key_hook(mlx_key_data_t keydata, void* param)
{
	t_map* md;

	md = param;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		if (md->map[md->py][md->px-1] != '1')
		{
			md->px--;
			md->moves++;
			ft_printf("Moves: %i\n", md->moves);
			md->img_pl[1]->enabled = !md->img_pl[1]->enabled;
			md->img_pl[0]->enabled = !md->img_pl[0]->enabled;
			md->img_pl[0]->instances[0].x -= UNIT_SIZE;
			md->img_pl[1]->instances[0].x -= UNIT_SIZE;
		}
	}
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		if (md->map[md->py-1][md->px] != '1')
		{
			md->py--;
			md->moves++;
			ft_printf("Moves: %i\n", md->moves);
			md->img_pl[1]->enabled = !md->img_pl[1]->enabled;
			md->img_pl[0]->enabled = !md->img_pl[0]->enabled;
			md->img_pl[0]->instances[0].y -= UNIT_SIZE;
			md->img_pl[1]->instances[0].y -= UNIT_SIZE;
		}
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		if (md->map[md->py][md->px+1] != '1')
		{
			md->px++;
			md->moves++;
			ft_printf("Moves: %i\n", md->moves);
			md->img_pl[1]->enabled = !md->img_pl[1]->enabled;
			md->img_pl[0]->enabled = !md->img_pl[0]->enabled;
			md->img_pl[0]->instances[0].x += UNIT_SIZE;
			md->img_pl[1]->instances[0].x += UNIT_SIZE;
		}
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		if (md->map[md->py+1][md->px] != '1')
		{
			md->py++;
			md->moves++;
			ft_printf("Moves: %i\n", md->moves);
			md->img_pl[1]->enabled = !md->img_pl[1]->enabled;
			md->img_pl[0]->enabled = !md->img_pl[0]->enabled;
			md->img_pl[0]->instances[0].y += UNIT_SIZE;
			md->img_pl[1]->instances[0].y += UNIT_SIZE;
		}
	}
}

void	hook(void* param)
{
	t_map* md;

	md = param;
	md->time ++;
	if (mlx_is_key_down(md->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(md->mlx);
	
	if (md->map[md->py][md->px] == 'C')
	{
		md->map[md->py][md->px] = '0';
		md->score++;
		size_t i = -1;
		while (++i < md->img_cllct->count)
		{
			if (md->img_cllct->instances[i].x == md->px*UNIT_SIZE && md->img_cllct->instances[i].y == md->py*UNIT_SIZE)
				md->img_cllct->instances[i].enabled = 0;
		}
	}
	int addx;
	int addy;
	if (md->time % 50 == 0)
	{
		addx = rand() % 3 - 1;
		addy = rand() % 3 - 1;
		if (md->map[md->ey + addy][md->ex + addx] != '1')
		{
			md->ex += addx;
			md->img_enemy->instances[0].x += UNIT_SIZE * addx;
			md->ey += addy;
			md->img_enemy->instances[0].y += UNIT_SIZE * addy;
		}
	}

}

int32_t	draw_map(t_map *md)
{
	md->mlx = mlx_init(md->width * UNIT_SIZE, md->height * UNIT_SIZE, "Game", true);
	if (!md->mlx)
		exit(EXIT_FAILURE);
	mlx_texture_t* background = mlx_load_png("./textures/Floor.png");
	mlx_texture_t* wall_texture = mlx_load_png("./textures/ducky.png");
    mlx_texture_t* pl1_texture = mlx_load_png("./textures/pl1.png");
	mlx_texture_t* pl2_texture = mlx_load_png("./textures/pl2.png");
	mlx_texture_t* c_texture = mlx_load_png("./textures/cllct.png");
	mlx_texture_t* e_texture = mlx_load_png("./textures/bh.png");
	if (!background || !wall_texture || !pl1_texture || !pl2_texture || !c_texture || !e_texture)
        error();

	mlx_image_t	*bg_img = mlx_texture_to_image(md->mlx, background);
	if (!bg_img)
        error();

	md->img_wall = mlx_texture_to_image(md->mlx, wall_texture);
    md->img_pl[0] = mlx_texture_to_image(md->mlx, pl1_texture);
	md->img_pl[1] = mlx_texture_to_image(md->mlx, pl2_texture);
	md->img_cllct = mlx_texture_to_image(md->mlx, c_texture);
	md->img_enemy = mlx_texture_to_image(md->mlx, e_texture);
	if (!md->img_wall || !md->img_pl[0] || !md->img_pl[1] || !md->img_cllct || !md->img_enemy)
        error();

    int idx;
	int lnum;
	char *line = md->map[0];
	lnum = -1;
	while (++lnum < md->height)
	{
        line = md->map[lnum];
		idx = -1;
		while (++idx < md->width)
		{
			if (mlx_image_to_window(md->mlx,bg_img, idx*UNIT_SIZE, lnum*UNIT_SIZE) < 0)
		            error();
            if (line[idx] == '1')
            {
                if (mlx_image_to_window(md->mlx, md->img_wall, idx*UNIT_SIZE, lnum*UNIT_SIZE) < 0)
		            error();
            }
            else if (line[idx] == 'C')
			{
            	if (mlx_image_to_window(md->mlx, md->img_cllct, idx*UNIT_SIZE, lnum*UNIT_SIZE) < 0)
		            error();
            }
            //also check for E
        }
    }

	if (mlx_image_to_window(md->mlx, md->img_pl[0], md->px*UNIT_SIZE, md->py*UNIT_SIZE) < 0)
		error();
	if (mlx_image_to_window(md->mlx, md->img_pl[1], md->px*UNIT_SIZE, md->py*UNIT_SIZE) < 0)
		error();
	
	md->img_pl[1]->enabled = 0;

	//place enemy
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
		md->ex = ex;
		md->ey = ey;
		if (mlx_image_to_window(md->mlx, md->img_enemy, md->ex*UNIT_SIZE, md->ey*UNIT_SIZE) < 0)
			error();
	}
	

	mlx_key_hook(md->mlx, &key_hook, md);
	mlx_loop_hook(md->mlx, &hook, md);

	ft_printf("Moves: %i\n", md->moves);
	mlx_loop(md->mlx);

	mlx_delete_image(md->mlx, md->img_wall);
    mlx_delete_image(md->mlx, md->img_pl[0]);
	mlx_delete_image(md->mlx, md->img_pl[1]);
	mlx_delete_image(md->mlx, md->img_cllct);
	mlx_delete_image(md->mlx, md->img_enemy);
	mlx_delete_image(md->mlx, bg_img);

	mlx_delete_texture(wall_texture);
    mlx_delete_texture(pl1_texture);
	mlx_delete_texture(pl2_texture);
	mlx_delete_texture(c_texture);
	mlx_delete_texture(e_texture);
	mlx_delete_texture(background);

	mlx_terminate(md->mlx);
	return (EXIT_SUCCESS);
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
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
			md->img_pl2->enabled = !md->img_pl2->enabled;
			md->img_pl1->enabled = !md->img_pl1->enabled;
			md->img_pl1->instances[0].x -= 60;
			md->img_pl2->instances[0].x -= 60;
		}
	}
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		if (md->map[md->py-1][md->px] != '1')
		{
			md->py--;
			md->img_pl2->enabled = !md->img_pl2->enabled;
			md->img_pl1->enabled = !md->img_pl1->enabled;
			md->img_pl1->instances[0].y -= 60;
			md->img_pl2->instances[0].y -= 60;
		}
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		if (md->map[md->py][md->px+1] != '1')
		{
			md->px++;
			md->img_pl2->enabled = !md->img_pl2->enabled;
			md->img_pl1->enabled = !md->img_pl1->enabled;
			md->img_pl1->instances[0].x += 60;
			md->img_pl2->instances[0].x += 60;
		}
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		if (md->map[md->py+1][md->px] != '1')
		{
			md->py++;
			md->img_pl2->enabled = !md->img_pl2->enabled;
			md->img_pl1->enabled = !md->img_pl1->enabled;
			md->img_pl1->instances[0].y += 60;
			md->img_pl2->instances[0].y += 60;
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
		ft_printf("Score is %i\n", md->score);
		size_t i = -1;
		while (++i < md->img_cllct->count)
		{
			if (md->img_cllct->instances[i].x == md->px*60 && md->img_cllct->instances[i].y == md->py*60)
				md->img_cllct->instances[i].enabled = 0;
		}
	}
	int addx;
	int addy;
	if (md->time % 100 == 0)
	{
		addx = rand() % 3 - 1;
		addy = rand() % 3 - 1;
		if (md->map[md->ey + addy][md->ex + addx] != '1')
		{
			md->ex += addx;
			md->img_enemy->instances[0].x += 60 * addx;
			md->ey += addy;
			md->img_enemy->instances[0].y += 60 * addy;
		}
	}

}

int32_t	draw_map(t_map *md)
{
	md->mlx = mlx_init(md->width * 60, md->height * 60, "Game", true);
	if (!md->mlx)
		exit(EXIT_FAILURE);
	mlx_texture_t* background = mlx_load_png("./textures/stars.png");
	mlx_texture_t* wall_texture = mlx_load_png("./textures/wall.png");
    mlx_texture_t* pl1_texture = mlx_load_png("./textures/pl1.png");
	mlx_texture_t* pl2_texture = mlx_load_png("./textures/pl2.png");
	mlx_texture_t* c_texture = mlx_load_png("./textures/cllct.png");
	mlx_texture_t* e_texture = mlx_load_png("./textures/bh.png");
	if (!background || !wall_texture || !pl1_texture || !pl2_texture || !c_texture || !e_texture)
        error();

	int fillx;
	int filly = -1;

	mlx_image_t	*bg_img = mlx_texture_to_image(md->mlx, background);
	if (!bg_img)
        error();
	while(++filly * 224 < md->height * 60)
	{
		fillx = -1;
		while(++fillx * 256 < md->width * 60)
		{
			if (mlx_image_to_window(md->mlx, bg_img, fillx * 256, filly * 224) < 0)
				error();
		}
	}
	

	md->img_wall = mlx_texture_to_image(md->mlx, wall_texture);
    md->img_pl1 = mlx_texture_to_image(md->mlx, pl1_texture);
	md->img_pl2 = mlx_texture_to_image(md->mlx, pl2_texture);
	md->img_cllct = mlx_texture_to_image(md->mlx, c_texture);
	md->img_enemy = mlx_texture_to_image(md->mlx, e_texture);
	if (!md->img_wall || !md->img_pl1 || !md->img_pl2 || !md->img_cllct || !md->img_enemy)
        error();
    if (mlx_image_to_window(md->mlx, md->img_pl1, md->px*60, md->py*60) < 0)
		error();
	if (mlx_image_to_window(md->mlx, md->img_pl2, md->px*60, md->py*60) < 0)
		error();
	if (mlx_image_to_window(md->mlx, md->img_enemy, md->ex*60, md->ey*60) < 0)
		error();
	md->img_pl2->enabled = 0;

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
            if (line[idx] == '1')
            {
                if (mlx_image_to_window(md->mlx, md->img_wall, idx*60, lnum*60) < 0)
		            error();
            }
            else if (line[idx] == 'C')
			{
            	if (mlx_image_to_window(md->mlx, md->img_cllct, idx*60, lnum*60) < 0)
		            error();
            }
            //also check for E
        }
    }
	mlx_key_hook(md->mlx, &key_hook, md);
	mlx_loop_hook(md->mlx, &hook, md);
	mlx_loop(md->mlx);

	mlx_delete_image(md->mlx, md->img_wall);
    mlx_delete_image(md->mlx, md->img_pl1);
	mlx_delete_image(md->mlx, md->img_pl2);
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
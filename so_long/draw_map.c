#include "so_long.h"


static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	hook(void* param)
{
	t_map* md;

	md = param;
	if (mlx_is_key_down(md->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(md->mlx);
	if (mlx_is_key_down(md->mlx, MLX_KEY_S))
		md->img_player->instances[0].y += 60;
	if (mlx_is_key_down(md->mlx, MLX_KEY_W))
		md->img_player->instances[0].y -= 60;
	if (mlx_is_key_down(md->mlx, MLX_KEY_A))
		md->img_player->instances[0].x -= 60;
	if (mlx_is_key_down(md->mlx, MLX_KEY_D))
		md->img_player->instances[0].x += 60;
	//for (uint32_t x = 0; x < g_img->width; x++)
	//	for(uint32_t y= 0; y < g_img->height; y++)
	//		mlx_put_pixel(g_img, x, y, rand());
}

int32_t	draw_map(t_map *md)
{
	md->mlx = mlx_init(md->width * 60, md->height * 60, "Game", true);
	if (!md->mlx)
		exit(EXIT_FAILURE);
	mlx_texture_t* wall_texture = mlx_load_png("./textures/wall.png");
    mlx_texture_t* pl1_texture = mlx_load_png("./textures/pl1.png");
	if (!wall_texture || !pl1_texture)
        error();
	md->img_wall = mlx_texture_to_image(md->mlx, wall_texture);
    md->img_player = mlx_texture_to_image(md->mlx, pl1_texture);
	if (!md->img_wall || !md->img_player)
        error();
    if (mlx_image_to_window(md->mlx, md->img_player, md->px*60, md->py*60) < 0)
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
            if (line[idx] == '1')
            {
                if (mlx_image_to_window(md->mlx, md->img_wall, idx*60, lnum*60) < 0)
		            error();
            }
            //else if (line[idx] == 'C')
            //{
            //    if (mlx_image_to_window(md->mlx, md->img_player, idx*60, lnum*60) < 0)
		    //        error();
            //}
            //also check for P and E and C..
        }
    }
	
	mlx_loop_hook(md->mlx, &hook, md);
	mlx_loop(md->mlx);
	mlx_delete_image(md->mlx, md->img_wall);
    mlx_delete_image(md->mlx, md->img_player);

	mlx_delete_texture(wall_texture);
    mlx_delete_texture(pl1_texture);

	mlx_terminate(md->mlx);
	return (EXIT_SUCCESS);
}
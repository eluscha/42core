#include "so_long.h"

int main(int argc, char **argv)
{
	int fd;
	t_map mapdata;

	fd = 0;
	if (argc != 1)
		fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);    
	init_mapdata(&mapdata);
	get_map(&mapdata, NULL, fd, 100);
	close(fd);
	//printf("got the map\n");
	int i = -1;
	if (!valid_map(&mapdata))
		close_free_exit(0, mapdata.map, NULL, 2);
	i = -1;
	//while(mapdata.map[++i])
	//	printf("line number %i is %s\n", i, mapdata.map[i]);
	printf("map is valid\n");
	draw_map(&mapdata);
}

void get_map(t_map *mapdata, char *oldline, int fd, int size)
{
	int idx;
	char *line;
	char **newmap;
	
	newmap = ft_calloc(size + 1, sizeof(char*));
	if (!newmap)
		close_free_exit(fd, mapdata->map, oldline, 1);
	idx = -1;
	if (mapdata->map)
	{
		while (mapdata->map[++idx])
			newmap[idx] = mapdata->map[idx];
		idx--;
		free(mapdata->map);
	}
	mapdata->map = newmap;
	line = oldline;
	if (!line)
		line = get_next_line(fd);
	while (line && ++idx < size)
	{
		mapdata->map[idx] = line;
		line = get_next_line(fd);
	}
	if (line)
		get_map(mapdata, line, fd, size * 2);
}

void    close_free_exit(int fd, char **map, char *line, int excode) //excode can code for wrong map vs failed malloc..
{   
	if (fd)
		close(fd);
	if (line)
		free(line);
	free_map(map);
	if (excode == 2)
		printf("Map is invalid");
	exit(EXIT_FAILURE);
}

void init_mapdata(t_map *mapdata)
{
	mapdata->map = NULL;
	mapdata->px = 0; //init to 0
	mapdata->exit = 0; //init to 0,-
	mapdata->goal = 0;
	mapdata->score = 0;
	mapdata->mlx = NULL;
	mapdata->img_wall = NULL;
	mapdata->img_pl1 = NULL;
	mapdata->img_pl2 = NULL;
	mapdata->img_exit = NULL;
	mapdata->img_cllct = NULL;
}

void free_map(char **map)
{
	int idx = 0;
	if (!map)
		return ;
	while(map[idx])
		free(map[idx++]);
	free(map);
}
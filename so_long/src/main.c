/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:52:32 by eusatiko          #+#    #+#             */
/*   Updated: 2024/07/02 10:24:39 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	int		fd;
	int		error;
	t_map	mapdata;

	fd = 0;
	if (argc != 1)
		fd = open_mapfile(argv[1]);
	init_mapdata(&mapdata);
	get_map(&mapdata, NULL, fd, 100);
	close(fd);
	error = check_valid_map(&mapdata);
	if (error)
		close_free_exit(0, mapdata.map, NULL, error);
	mapdata.exit = 0;
	draw_map(&mapdata);
}

int	open_mapfile(char *path)
{
	int	fd;
	int	len;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".ber", 4) != 0)
	{
		ft_printf("Error: map file has to be of format *.ber\n");
		exit(EXIT_FAILURE);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error: ");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	init_mapdata(t_map *mapdata)
{
	mapdata->map = NULL;
	mapdata->px = 0;
	mapdata->exit = 0;
	mapdata->goal = 0;
	mapdata->score = 0;
	mapdata->mlx = NULL;
	mapdata->txtr = NULL;
	mapdata->img_bckgr = NULL;
	mapdata->img_wall = NULL;
	mapdata->img_cllct = NULL;
	mapdata->img_pl = NULL;
	mapdata->img_exit = NULL;
	mapdata->time = 0;
	mapdata->moves = 0;
}

void	get_map(t_map *mapdata, char *line, int fd, int size)
{
	int		idx;
	char	**newmap;

	newmap = ft_calloc(size + 1, sizeof(char *));
	if (!newmap)
		close_free_exit(fd, mapdata->map, line, -1);
	idx = -1;
	if (mapdata->map)
	{
		while (mapdata->map[++idx])
			newmap[idx] = mapdata->map[idx];
		idx--;
		free(mapdata->map);
	}
	mapdata->map = newmap;
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

void	close_free_exit(int fd, char **map, char *line, int error)
{
	if (fd)
		close(fd);
	if (line)
		free(line);
	free_map(map);
	if (error == -1)
		ft_printf("Error: failed to allocate space on the heap\n");
	else if (error == 1)
		ft_printf("Error: no valid path (to all collectables and exit)\n");
	else if (error == 2)
		ft_printf("Error: the map has to be rectangular, surrounded by walls\n");
	else if (error == 3)
		ft_printf("Error: there can be only 1 player (P)\n");
	else if (error == 4)
		ft_printf("Error: there can be only 1 exit (E)\n");
	else if (error == 5)
		ft_printf("Error: only characters 0, 1, C, E, and P are allowed\n");
	else if (error == 6)
	{
		ft_printf("Error: there has to be 1 player (P), 1 exit (E), ");
		ft_printf("and at least 1 collectable (C)\n");
	}
	exit(EXIT_FAILURE);
}

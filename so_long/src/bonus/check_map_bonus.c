/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:49:18 by eusatiko          #+#    #+#             */
/*   Updated: 2024/06/28 12:30:17 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_valid_map(t_map *mapdata)
{
	int		idx;
	int		res;
	char	*line;

	line = mapdata->map[0];
	idx = -1;
	while (line[++idx] && line[idx] != '\n')
	{
		if (line[idx] != '1')
			return (2);
	}
	mapdata->width = idx;
	res = check_other_lines(mapdata);
	if (res != 0)
		return (res);
	if (!mapdata->exit || !mapdata->px || !mapdata->goal)
		return (6);
	return (check_valid_path(*mapdata)); 
}

int	check_other_lines(t_map *mapdata)
{
	char	*line;
	int		lnum;
	int		idx;
	int		res;

	lnum = 1;
	res = 0;
	line = mapdata->map[lnum];
	while (line)
	{
		idx = -1;
		while (!res && ++idx < mapdata->width)
			res = check_char(mapdata, line, idx, lnum);
		if (!res && line[idx] && line[idx] != '\n')
			res = 2;
		if (res != 0)
			return (res);
		line = mapdata->map[++lnum];
	}
	mapdata->height = lnum;
	return (check_last_line(mapdata, lnum - 1));
}

int	check_last_line(t_map *mapdata, int num)
{
	char	*line;
	int		idx;

	line = mapdata->map[num];
	idx = -1;
	while (++idx < mapdata->width)
	{
		if (!line[idx] || line[idx] != '1')
			return (2);
	}
	if (line[idx] && line[idx] != '\n')
		return (2);
	return (0);
}

int	check_char(t_map *mapdata, char *line, int idx, int lnum)
{
	if (!line[idx] || line[idx] == '\n')
		return (2);
	if ((idx == 0 || idx == mapdata->width - 1) && line[idx] != '1')
		return (2);
	if (line[idx] == 'P')
	{
		if (mapdata->px != 0)
			return (3);
		mapdata->px = idx;
		mapdata->py = lnum;
		line[idx] = '0';
	}
	else if (line[idx] == 'E')
	{
		if (mapdata->exit != 0)
			return (4);
		mapdata->exit = 1;
	}
	else if (line[idx] == 'C')
		mapdata->goal++;
	else if (line[idx] != '1' && line[idx] != '0')
		return (5);
	return (0);
}

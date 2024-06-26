/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:54:21 by eusatiko          #+#    #+#             */
/*   Updated: 2024/06/26 11:54:25 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char **copy_map(t_map *mapdata)
{
	char **newmap = ft_calloc(mapdata->height + 1, sizeof(char*));
	if (!newmap)
		return (NULL);
	int i = 0;
	while (i < mapdata->height)
	{
		newmap[i] = ft_strdup(mapdata->map[i]);
		if (!newmap[i])
		{
			while (--i >= 0)
				free(newmap[i]);
			free(newmap);
			return (NULL);
		}
		i++;
	}
	return (newmap);
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

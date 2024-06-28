/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helpers_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:54:21 by eusatiko          #+#    #+#             */
/*   Updated: 2024/06/28 12:29:33 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	**copy_map(t_map *mapdata)
{
	int		i;
	char	**newmap;

	newmap = ft_calloc(mapdata->height + 1, sizeof(char *));
	if (!newmap)
		return (NULL);
	i = 0;
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

void	free_map(char **map)
{
	int	idx;

	idx = 0;
	if (!map)
		return ;
	while (map[idx])
		free(map[idx++]);
	free(map);
}

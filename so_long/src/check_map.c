#include "so_long.h"

int valid_map(t_map *mapdata)
{
	int idx;
	int lnum;
	char *line = mapdata->map[0];
	

	idx = -1;
	while (line[++idx] && line[idx] != '\n')
	{
		if (line[idx] != '1')
			return (0);
	}
	line[idx] = '\0';
	if (idx < 3)
		return (0);
	mapdata->width = idx;
	lnum = 1;
	line = mapdata->map[lnum];
	while (line)
	{
		idx = -1;
		while (line[++idx] && line[idx] != '\n')
		{
			printf("lnum is %i, idx is %i\n", lnum, idx);
			if (idx == mapdata->width)
				return (0);
			if (idx == 0 || idx == mapdata->width - 1)
			{
				if (line[idx] != '1')
					return (0);
			}
			else if (line[idx] == 'P')
			{
				if (mapdata->px != 0)
					return (0);
				mapdata->px = idx;
				mapdata->py = lnum;
				line[idx] = '0';
			}
			else if (line[idx] == 'E')
			{
				if (mapdata->exit != 0)
					return (0);
				mapdata->exit = 1;
			}
			else if (line[idx] == 'C')
				mapdata->goal++;
			else if (line[idx] != '1' && line[idx] != '0')
				return (0);
		}
		line[idx] = '\0';
		line = mapdata->map[++lnum];
	}
	mapdata->height = lnum;
	if (lnum < 3)
		return (0);
	line = mapdata->map[lnum - 1];
	idx = 0;
	while (line[idx])
	{
		if (line[idx++] != '1')
			return (0);
	}
	if (!mapdata->exit || !mapdata->px || !mapdata->goal)
		return (0);
	if (valid_path(*mapdata))
	{
		printf("There is valid path!\n");
		return (1);
	}
	printf("no path\n");
	return (0);
}

int valid_path(t_map md)
{
	char	val;
	bool		valid_path = 0;
	t_pos *head;
	t_pos *tail;
	t_pos *temp;

	int i;
	printf("in valid_path\n");
	md.map = copy_map(&md);
	if (!md.map)
		return (-1);
	md.exit = 0;
	head = create_node(md.px, md.py);
	tail = head;
	while (head && tail && !valid_path)
	{
		val = md.map[head->y][head->x];
		printf("map[head->y][head->x] is map[%i][%i] and val is %c\n", head->y, head->x, val);
		if (val == 'E')
			md.exit = 1;
		else if (val == 'C' || val == '0')
		{
			if (val == 'C')
				md.score++;
			tail = add_nbs(md.map, head->x, head->y, tail);
		}
		md.map[head->y][head->x] = 'X'; //visited
		i = -1;
		while (md.map[++i])
			printf("line number %i is %s\n", i, md.map[i]);
		temp = head;
		head = head->next;
		free(temp);
		printf("exit is %i, score is %i\n", md.exit, md.score);
		if (md.exit && md.score == md.goal)
			valid_path = 1;
	}
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	free_map(md.map);
	return (valid_path);
}

t_pos *create_node(int x, int y)
{
	//printf("in create with x %i and y %i\n", x, y);
	t_pos *node = malloc(sizeof(t_pos));

	if (!node)
		return (NULL);
	node->x = x;
	node->y = y;
	node->next = NULL;
	return (node);
}

char **copy_map(t_map *mapdata)
{
	printf("in copy\n");
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

t_pos *add_nbs(char **map, int x, int y, t_pos* tail) //mallocs!
{
	if (tail && map[y - 1][x] != '1' && map[y - 1][x] != 'X') // up
	{
		tail->next = create_node(x, y - 1);
		tail = tail->next;
	}
	if (tail && map[y][x + 1] != '1' && map[y][x + 1] != 'X') //right
	{
		tail->next = create_node(x + 1, y);
		tail = tail->next;
	}
	if (tail && map[y + 1][x] != '1' && map[y + 1][x] != 'X') //down
	{
		tail->next = create_node(x, y + 1);
		tail = tail->next;
	}
	if (tail && map[y][x - 1] != '1' && map[y][x - 1] != 'X') //left
	{
		tail->next = create_node(x - 1, y);
		tail = tail->next;
	}
	return (tail);
}
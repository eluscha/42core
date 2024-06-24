#include "so_long.h"

int check_valid_map(t_map *mapdata)
{
	int idx;
	int res;
	char *line;

	line = mapdata->map[0];	
	idx = -1;
	while (line[++idx] && line[idx] != '\n')
	{
		if (line[idx] != '1')
			return (2); //2 for has to be rectangular, surrounded by walls
	}
	mapdata->width = idx;
	res = check_other_lines(mapdata);
	if (res != 0)
		return (res);
	if (!mapdata->exit || !mapdata->px || !mapdata->goal)
		return (6); //6 for missing items
	return (check_valid_path(*mapdata)); // 0 for valid map, -1 for malloc problems, 1 for no valid path
}

int check_other_lines(t_map *mapdata)
{
	char *line;
	int lnum = 1;
	int idx;
	int	res;

	res = 0;
	line = mapdata->map[lnum];
	while (line)
	{
		idx = -1;
		while (!res && ++idx < mapdata->width)
			res = check_char(mapdata, line, idx, lnum);
		if (!res && line[idx] && line[idx] != '\n') //line too long
			res = 2;
		if (res != 0)
			return (res);
		line = mapdata->map[++lnum];
	}
	mapdata->height = lnum;
	return (check_last_line(mapdata, lnum - 1));
}

int check_last_line(t_map *mapdata, int num)
{
	char *line = mapdata->map[num];
	int idx = -1;
	while (++idx < mapdata->width)
	{
		if (!line[idx] || line[idx] != '1')
			return (2); //2 for has to be rectangular, surrounded by walls
	}
	if (line[idx] && line[idx] != '\n')
		return (2); //cause last line is too long
	return (0);
}

int check_char(t_map *mapdata, char *line, int idx, int lnum)
{
	if (!line[idx] || line[idx] == '\n')
		return (2); //2 for has to be rectangular, surrounded by walls
	if ((idx == 0 || idx == mapdata->width - 1) && line[idx] != '1')
		return (2); //2 for has to be rectangular, surrounded by walls
	if (line[idx] == 'P')
	{
		if (mapdata->px != 0)
			return (3); //code 3 for can be only 1 player
		mapdata->px = idx;
		mapdata->py = lnum;
		line[idx] = '0';
	}
	else if (line[idx] == 'E')
	{
		if (mapdata->exit != 0)
			return (4); //code 4 for can be only 1 exit
		mapdata->exit = 1;
	}
	else if (line[idx] == 'C')
		mapdata->goal++;
	else if (line[idx] != '1' && line[idx] != '0')
		return (5); //map has to consist of characters 0, 1, C, E, and P
	return (0);
}

int check_valid_path(t_map md)
{
	bool	nopath;
	t_pos 	*head;
	t_pos 	*tail;

	nopath = 1;
	md.map = copy_map(&md);
	if (!md.map)
		return (-1);
	md.exit = 0;
	head = create_node(md.px, md.py, '0'); 
	tail = head; //so if malloc failed tail is NULL
	md.map[md.py][md.px] = 'X';
	while (head && tail && nopath)
		nopath = check_current_head(&md, &head, &tail);
	while (head)
		head = list_pop(head);
	free_map(md.map);
	if (!tail)
		return (-1);
	return (nopath);
}

int check_current_head(t_map *md, t_pos **h_adr, t_pos **t_adr)
{
	t_pos *head;

	head = *h_adr;
	if (head->val == 'E')
		md->exit = 1;
	if (head->val == 'C')
		md->score++;
	*t_adr = add_nbs(md->map, head->x, head->y, *t_adr);
	*h_adr = list_pop(head);
	if (md->exit && md->score == md->goal)
		return (0);
	return (1);
}

t_pos *create_node(int x, int y, char c)
{
	t_pos *node = malloc(sizeof(t_pos));

	if (!node)
		return (NULL);
	node->x = x;
	node->y = y;
	node->val = c;
	node->next = NULL;
	return (node);
}

t_pos *list_pop(t_pos *head)
{
	t_pos *temp;
	temp = head;
	head = head->next;
	free(temp);
	return (head);
}

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

t_pos *add_nbs(char **map, int x, int y, t_pos* tail)
{
	if (tail && map[y - 1][x] != '1' && map[y - 1][x] != 'X') // up
	{
		tail->next = create_node(x, y - 1, map[y - 1][x]);
		tail = tail->next;
		map[y - 1][x] = 'X';
	}
	if (tail && map[y][x + 1] != '1' && map[y][x + 1] != 'X') //right
	{
		tail->next = create_node(x + 1, y, map[y][x + 1]);
		tail = tail->next;
		map[y][x + 1] = 'X';
	}
	if (tail && map[y + 1][x] != '1' && map[y + 1][x] != 'X') //down
	{
		tail->next = create_node(x, y + 1, map[y + 1][x]);
		tail = tail->next;
		map[y + 1][x] = 'X';
	}
	if (tail && map[y][x - 1] != '1' && map[y][x - 1] != 'X') //left
	{
		tail->next = create_node(x - 1, y, map[y][x - 1]);
		tail = tail->next;
		map[y][x - 1] = 'X';
	}
	return (tail);
}
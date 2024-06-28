/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:49:48 by eusatiko          #+#    #+#             */
/*   Updated: 2024/06/28 12:30:11 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_valid_path(t_map md)
{
	bool	nopath;
	t_pos	*head;
	t_pos	*tail;

	nopath = 1;
	md.map = copy_map(&md);
	if (!md.map)
		return (-1);
	md.exit = 0;
	head = create_node(md.px, md.py, '0'); 
	tail = head;
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

t_pos	*create_node(int x, int y, char c)
{
	t_pos	*node;

	node = malloc(sizeof(t_pos));
	if (!node)
		return (NULL);
	node->x = x;
	node->y = y;
	node->val = c;
	node->next = NULL;
	return (node);
}

int	check_current_head(t_map *md, t_pos **h_adr, t_pos **t_adr)
{
	t_pos	*head;

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

t_pos	*add_nbs(char **map, int x, int y, t_pos *tail)
{
	if (tail && map[y - 1][x] != '1' && map[y - 1][x] != 'X')
	{
		tail->next = create_node(x, y - 1, map[y - 1][x]);
		tail = tail->next;
		map[y - 1][x] = 'X';
	}
	if (tail && map[y][x + 1] != '1' && map[y][x + 1] != 'X')
	{
		tail->next = create_node(x + 1, y, map[y][x + 1]);
		tail = tail->next;
		map[y][x + 1] = 'X';
	}
	if (tail && map[y + 1][x] != '1' && map[y + 1][x] != 'X')
	{
		tail->next = create_node(x, y + 1, map[y + 1][x]);
		tail = tail->next;
		map[y + 1][x] = 'X';
	}
	if (tail && map[y][x - 1] != '1' && map[y][x - 1] != 'X')
	{
		tail->next = create_node(x - 1, y, map[y][x - 1]);
		tail = tail->next;
		map[y][x - 1] = 'X';
	}
	return (tail);
}

t_pos	*list_pop(t_pos *head)
{
	t_pos	*temp;

	temp = head;
	head = head->next;
	free(temp);
	return (head);
}

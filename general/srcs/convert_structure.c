/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_structure.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:54:19 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 18:06:08 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		create_link(t_lem *lem, const char *first, const char *second)
{
	t_node	*f;
	t_node	*s;

	f = find_node(first, lem->graph);
	s = find_node(second, lem->graph);
	if (f != s)
		if (in_neighbors(f->neighbors, f->n_len, s) == 0)
		{
			if (!add_darr(&f->neighbors, s))
				error_f("create_link add_darr malloc", 0);
			if (!add_darr(&s->neighbors, f))
				error_f("create_link add_darr malloc", 0);
			f->n_len++;
			s->n_len++;
		}
}

t_node		*get_node(t_read *read, t_lem *lem, t_rooms *rooms, int i)
{
	t_node	*node;

	node = new_node_conv(ft_strdup(rooms->room), rooms->x, rooms->y);
	if (!node)
		error_f("convert_rooms new_node malloc error", 0);
	if (!ft_strcmp(node->name, read->start_name))
	{
		node->s_or_end = 1;
		lem->graph->start = i;
	}
	else if (!ft_strcmp(node->name, read->end_name))
	{
		node->s_or_end = 1;
		lem->graph->end = i;
	}
	return (node);
}

void		convert_rooms(t_read *read, t_lem *lem)
{
	t_rooms	*rooms;
	t_node	*node;
	int		i;

	lem->graph = new_graph();
	i = 0;
	rooms = read->rooms;
	while (rooms)
	{
		node = get_node(read, lem, rooms, i);
		if (!add_darr(&(lem->graph->nodes), node))
			error_f("convert_rooms add_darr malloc error", 0);
		lem->graph->len++;
		rooms = rooms->next;
		i++;
	}
}

void		convert_links(t_read *read, t_lem *lem)
{
	t_cnct	*cntc;

	cntc = read->conect;
	while (cntc)
	{
		create_link(lem, cntc->from->room, cntc->to->room);
		cntc = cntc->next;
	}
}

void		convert_structure(t_read *read, t_lem *lem)
{
	lem->n_ants = read->ant_cnt;
	convert_rooms(read, lem);
	convert_links(read, lem);
}

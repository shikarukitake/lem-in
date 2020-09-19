/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dublicate_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:55:33 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/18 16:36:38 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	create_copy(t_edge *edge_dub)
{
	t_node	*copy;
	t_node	*current;

	current = edge_dub->from;
	if (current->copy == NULL)
	{
		copy = new_node(ft_strjoin(current->name, "_copy"), "0", "0");
		if (!copy)
			error_f("create_copy new_node malloc", 0);
		copy->is_copy = 1;
		copy->copy = edge_dub->from;
		edge_dub->from->copy = copy;
	}
	current = edge_dub->to;
	if (current->copy == NULL)
	{
		copy = new_node(ft_strjoin(current->name, "_copy"), "0", "0");
		if (!copy)
			error_f("create_copy new_node malloc", 0);
		copy->is_copy = 1;
		copy->copy = edge_dub->to;
		edge_dub->to->copy = copy;
	}
}

void	one_relation(t_node *from, t_node *to, t_lem *lem)
{
	t_list	*new;
	t_edge	*edge;

	edge = new_edge(from, to);
	if (!edge)
		error_f("add_relation new_edge malloc", 0);
	edge->w = 0;
	new = ft_lstnew(edge, sizeof(t_edge));
	if (!new)
	{
		free(edge);
		error_f("add_relation ft_lstnew malloc", 0);
	}
	ft_lstadd(&(lem->edges), new);
}

void	add_relation(t_lem *lem, t_edge *edge_dub)
{
	one_relation(edge_dub->from->copy, edge_dub->from, lem);
	one_relation(edge_dub->to->copy, edge_dub->to, lem);
}

void	dublicate_node(t_lem *lem, t_edge *edge_dub)
{
	t_list	*edges;
	t_edge	*edge;

	edges = lem->edges;
	create_copy(edge_dub);
	while (edges)
	{
		edge = edges->content;
		if (edge->from == edge_dub->from && edge->w != -1)
			edge->from = edge_dub->from->copy;
		else if (edge->from == edge_dub->to && edge->to == edge_dub->from)
			edge->to = edge->to->copy;
		else if (edge->from == edge_dub->to && edge->w != -1)
			edge->from = edge_dub->to->copy;
		else if (edge->to == edge_dub->to && edge->w == -1)
			edge->to = edge_dub->to->copy;
		edges = edges->next;
	}
	add_relation(lem, edge_dub);
}

void	dublicate_nodes(t_lem *lem)
{
	t_list	*paths;
	t_list	*path;

	paths = lem->paths;
	while (paths)
	{
		path = ((t_list*)(paths->content))->next;
		if (path)
			while (path->next)
			{
				dublicate_node(lem, path->content);
				path = path->next;
			}
		paths = paths->next;
	}
}

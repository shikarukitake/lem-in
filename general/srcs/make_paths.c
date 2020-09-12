/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:56:28 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:57:32 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	make_paths(t_lem *lem, int suurbale)
{
	t_list	*path;
	t_node	*node;
	t_edge	*edge;

	path = NULL;
	node = lem->graph->nodes->array[lem->graph->end];
	while (node->prev)
	{
		edge = get_edge(node->prev, node, lem);
		node->prev->in_way++;
		node->in_way++;
		if (edge)
			if (!ft_lst_pb(&path, edge, sizeof(t_edge)))
				error_f("one_path ft_lstnew malloc", 0);
		node = node->prev;
	}
	if (!ft_lst_pb(&(lem->paths), path, sizeof(t_list)))
		error_f("one_path ft_lstnew malloc", 0);
}

void	make_new_paths(t_lem *lem)
{
	t_edge	*edge;
	t_list	*path;

	lem->paths = NULL;
	while (lem->new_paths)
	{
		path = NULL;
		edge = find_edge(&(lem->new_paths), NULL, &start_edges);
		if (!ft_lst_pb(&path, edge, sizeof(t_edge)))
			error_f("make_new_paths ft_lstnew malloc", 0);
		if (!ft_lst_pb(&(lem->paths), path, sizeof(t_list)))
			error_f("make_new_paths ft_lstnew malloc", 0);
		while (edge->to != lem->graph->nodes->array[lem->graph->end])
		{
			edge = find_edge(&(lem->new_paths), edge, &path_edges);
			if (!ft_lst_pb(&path, edge, sizeof(t_edge)))
				error_f("make_new_paths ft_lstnew malloc", 0);
			if (edge == NULL)
				error_f("something wrong maybe very big map", 0);
		}
	}
}

void	make_paths_many(t_lem *lem)
{
	t_list	*path;
	t_node	*node;
	t_edge	*edge;

	path = NULL;
	node = lem->graph->nodes->array[lem->graph->end];
	while (node->prev)
	{
		edge = new_edge(node->prev, node);
		node->prev->in_way++;
		node->in_way++;
		if (!edge)
			error_f("make_paths_many malloc", 0);
		if (!ft_lst_pb(&path, edge, sizeof(t_edge)))
			error_f("make_paths_many ft_lstnew malloc", 0);
		node = node->prev;
	}
	if (!ft_lst_pb(&(lem->paths), path, sizeof(t_list)))
		error_f("one_path ft_lstnew malloc", 0);
}

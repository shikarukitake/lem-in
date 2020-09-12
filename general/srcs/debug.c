/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:55:14 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:55:20 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node	*find_node_without_delete(t_lem *lem, const char *name)
{
	int i;

	i = 0;
	while (i != lem->graph->len)
	{
		if (!ft_strcmp(lem->graph->nodes->array[i]->name, name))
			return (lem->graph->nodes->array[i]);
		i++;
	}
}

t_edge	*find_edge_without_delete(t_lem *lem, t_node *from, t_node *to)
{
	t_list	*paths;
	t_list	*path;
	t_edge	*edge;

	paths = lem->paths;
	while (paths)
	{
		path = paths->content;
		while (path)
		{
			edge = path->content;
			if (edge->from == from && edge->to == to)
				return (edge);
			path = path->next;
		}
		paths = paths->next;
	}
	return (NULL);
}

t_list	*find_end(t_list *list)
{
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}

void	print_path(t_list *list)
{
	t_edge	*edge;

	edge = (list->content);
	ft_printf("%s-%s ", edge->from->name, edge->to->name);
}

void	print_paths(t_lem *lem)
{
	t_list	*swap;

	swap = lem->paths;
	while (swap)
	{
		ft_lstiter(swap->content, &print_path);
		swap = swap->next;
		ft_printf("\n");
	}
}

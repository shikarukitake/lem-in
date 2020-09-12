/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_in_way.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:56:56 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:56:56 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clear_in_way(t_lem *lem)
{
	t_node	**nodes;
	int		i;

	nodes = lem->graph->nodes->array;
	i = 0;
	while (i != lem->graph->len)
	{
		nodes[i]->in_way = 0;
		i++;
	}
}

void	set_way_path(t_list *elem)
{
	t_edge	*edge;

	edge = elem->content;
	edge->from->in_way++;
	edge->to->in_way++;
}

void	set_way_paths(t_list *elem)
{
	ft_lstiter(elem->content, &set_way_path);
}

void	set_in_way(t_lem *lem)
{
	clear_in_way(lem);
	ft_lstiter(lem->paths, &set_way_paths);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:55:44 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:55:44 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_edges(t_list *elem)
{
	t_edge	*edge;

	edge = (t_edge*)elem->content;
	ft_printf("EDGE:\n");
	ft_printf("FROM: %s | TO: %s\n", edge->from->name, edge->to->name);
	ft_printf("W=%d\n\n", edge->w);
}

void	del_edge(void *edge_addr, size_t size)
{
	t_edge	*edge;

	size += 0;
	edge = (t_edge*)edge_addr;
	free(edge);
}

t_edge	*new_edge(t_node *from, t_node *to)
{
	t_edge	*edge;

	edge = malloc(sizeof(t_edge));
	if (edge == NULL)
		return (NULL);
	edge->from = from;
	edge->to = to;
	edge->w = 1;
	return (edge);
}

int		create_edge(t_lem *lem)
{
	int		i;
	int		j;
	t_list	*list;
	t_edge	*edge;
	t_node	*node;

	i = 0;
	list = NULL;
	edge = NULL;
	while (i != lem->graph->len)
	{
		node = lem->graph->nodes->array[i];
		j = 0;
		while (j != node->n_len)
		{
			edge = new_edge(node, node->neighbors->array[j]);
			if (edge == NULL)
				error_f("edge malloc error", 0);
			j++;
			ft_lst_pb(&list, edge, sizeof(t_edge));
		}
		i++;
	}
	lem->origin_edges = list;
	return (1);
}

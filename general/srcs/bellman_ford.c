/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:53:58 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:53:58 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		relax_edge(t_edge *edge, t_lem *lem)
{
	int		dist_v;
	int		dist_u;

	dist_v = edge->to->weight;
	dist_u = edge->from->weight;
	if (dist_u == FT_INT_MAX)
		return (FT_FALSE);
	if (dist_v > dist_u + edge->w)
	{
		edge->to->weight = dist_u + edge->w;
		edge->to->prev = edge->from;
		return (FT_TRUE);
	}
	return (FT_FALSE);
}

void	zero_weight(t_lem *lem)
{
	t_list	*edges;
	int		i;

	i = 0;
	while (i != lem->graph->len)
	{
		if (i == lem->graph->start)
			lem->graph->nodes->array[i]->weight = 0;
		else
		{
			lem->graph->nodes->array[i]->weight = FT_INT_MAX;
			if (lem->graph->nodes->array[i]->copy)
				lem->graph->nodes->array[i]->copy->weight = FT_INT_MAX;
		}
		i++;
	}
}

int		bellman_ford(t_lem *lem)
{
	int		i;
	int		r;
	int		r_temp;
	t_list	*edges;

	i = 0;
	zero_weight(lem);
	while (i != lem->graph->len)
	{
		edges = (t_list*)lem->edges;
		r = FT_FALSE;
		while (edges)
		{
			r_temp = relax_edge(edges->content, lem);
			if (!r)
				r = r_temp;
			edges = edges->next;
		}
		if (r == FT_FALSE)
			break ;
		i++;
	}
	return (FT_TRUE);
}

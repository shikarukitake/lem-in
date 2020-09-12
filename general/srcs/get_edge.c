/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_edge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:56:22 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:57:32 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_edge	*get_first_edge(t_node *from, t_node *to, t_lem *lem, int *running)
{
	t_edge	*edge;
	t_list	*temp;

	edge = lem->edges->content;
	if (edge->from == from && edge->to == to)
	{
		temp = lem->edges->next;
		free(lem->edges);
		lem->edges = temp;
		*running += 1;
		return (edge);
	}
	else if (edge->from == to && edge->to == from)
	{
		edge->w = -1;
		*running += 1;
	}
	return (NULL);
}

t_edge	*get_other_edge(t_node *from, t_node *to, t_list *edges, int *running)
{
	t_edge	*edge;
	t_list	*temp;

	edge = edges->next->content;
	if (edge->from == from && edge->to == to)
	{
		temp = edges->next->next;
		free(edges->next);
		edges->next = temp;
		*running += 1;
		return (edge);
	}
	else if (edge->from == to && edge->to == from)
	{
		edge->w = -1;
		*running += 1;
	}
	return (NULL);
}

/*
** This function get edge with same from node and
** same to node and set weight -1 to reversed edge
*/

t_edge	*get_edge(t_node *from, t_node *to, t_lem *lem)
{
	t_edge	*edge;
	t_list	*edges;
	t_edge	*finded;
	int		running;

	finded = NULL;
	edge = NULL;
	running = 0;
	edge = get_first_edge(from, to, lem, &running);
	if (edge)
		finded = edge;
	edges = lem->edges;
	while (edges && edges->next)
	{
		if (running == 2)
			break ;
		edge = get_other_edge(from, to, edges, &running);
		if (edge)
			finded = edge;
		else
			edges = edges->next;
	}
	return (finded);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_edge_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:56:15 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:57:32 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		path_edges(t_edge *a, t_edge *b)
{
	if (b->to == a->from)
		return (1);
	else
		return (0);
}

int		disjoint_edge(t_edge *a, t_edge *b)
{
	if (a->from == b->to && a->to == b->from)
		return (1);
	else
		return (0);
}

int		in_way_edge(t_edge *a, t_edge *b)
{
	if (a->from->in_way > 2 && a->to->in_way > 2)
	{
		if (a->from->s_or_end || a->to->s_or_end)
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

int		start_edges(t_edge *a, t_edge *b)
{
	if (a->from->s_or_end)
		return (1);
	return (0);
}

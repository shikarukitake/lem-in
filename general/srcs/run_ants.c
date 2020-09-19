/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:56:41 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 15:11:11 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				all_ants_in_finish(t_lem *lem)
{
	t_list	*path;
	t_way	*ways;
	t_node	*node;

	ways = lem->var->ways;
	while (ways)
	{
		path = ways->path;
		node = path->content;
		if (ways->ants > 0 || node->ant != -1)
			return (0);
		ways = ways->next;
	}
	return (1);
}

void			set_node_part(t_way *way, t_lem *lem,
							t_node *node, t_node *next)
{
	if (way->ants > 0)
	{
		node->ant = ++(lem->i);
		way->ants--;
	}
	else if (way->ants <= 0 && next->ant != -1)
	{
		node->ant = -1;
		next->ant = -1;
	}
	else
		node->ant = next->ant;
}

void			set_node(t_list *path, t_way *way, t_lem *lem)
{
	t_node	*node;
	t_node	*next;

	if (path)
		while (path->next)
		{
			node = path->content;
			next = path->next->content;
			if (next->s_or_end)
			{
				set_node_part(way, lem, node, next);
			}
			else
				node->ant = next->ant;
			path = path->next;
		}
}

void			run_ants(t_lem *lem)
{
	t_list	*path;
	t_way	*ways;

	lem->i = 0;
	ways = lem->var->ways;
	while (ways)
	{
		reverse_list(&(ways->path));
		ways = ways->next;
	}
	while (!all_ants_in_finish(lem))
	{
		ways = lem->var->ways;
		while (ways)
		{
			path = ways->path;
			set_node(path, ways, lem);
			ways = ways->next;
		}
		print_nodes(lem);
	}
}

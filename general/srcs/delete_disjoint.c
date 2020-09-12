/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_disjoint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:50:43 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:54:09 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	cpy_back(t_lem *lem, t_list *temp_list)
{
	t_list	*temp;

	temp = temp_list;
	while (temp->next)
		temp = temp->next;
	temp->next = lem->new_paths;
	lem->new_paths = temp_list;
}

void	get_find_edge(t_lem *lem, t_edge *edge, t_list **temp_list)
{
	t_edge *temp;

	temp = find_edge(&(lem->new_paths), edge, &disjoint_edge);
	if (temp)
	{
		edge->from->in_way -= 2;
		edge->to->in_way -= 2;
		free(edge);
		free(temp);
	}
	else
	{
		if (!ft_lst_pb(temp_list, edge, sizeof(t_edge)))
			error_f("delete_disjoint malloc", 0);
	}
}

void	delete_disjoint_edges(t_lem *lem)
{
	t_edge	*edge;
	t_edge	*temp;
	t_list	*temp_list;

	temp_list = NULL;
	edge = find_edge(&(lem->new_paths), NULL, &in_way_edge);
	while (edge)
	{
		if (edge->from == edge->to)
			free(edge);
		else
			get_find_edge(lem, edge, &temp_list);
		edge = find_edge(&(lem->new_paths), NULL, &in_way_edge);
	}
	if (temp_list)
		cpy_back(lem, temp_list);
}

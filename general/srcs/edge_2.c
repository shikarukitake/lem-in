/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:56:01 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:56:08 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	all_edges_in_paths_connected(t_lem *lem)
{
	t_list	*paths;
	t_list	*path;
	t_list	*temp;

	paths = lem->paths;
	while (paths)
	{
		path = paths->content;
		if (lem->new_paths == FT_NULL)
			lem->new_paths = path;
		else
		{
			temp = path;
			while (path->next)
			{
				path = path->next;
			}
			path->next = lem->new_paths;
			lem->new_paths = temp;
		}
		paths = paths->next;
	}
	ft_lstdel(&(lem->paths), NULL);
	lem->paths = NULL;
}

void	copy_edge(t_lem *lem)
{
	t_list	*edges;
	t_list	*new;
	t_list	*new_lstnew;

	edges = lem->origin_edges;
	new = NULL;
	while (edges)
	{
		new_lstnew = ft_lstnew_copy(edges->content, edges->content_size);
		if (new_lstnew == NULL)
			error_f("copy_edge ft_lstnew_copy", 0);
		ft_lstadd(&new, new_lstnew);
		edges = edges->next;
	}
	lem->edges = new;
}

void	refresh_edges(t_lem *lem)
{
	t_list	*paths;
	t_list	*path;
	t_edge	*edge;
	t_edge	*finded;

	paths = lem->paths;
	while (paths)
	{
		path = paths->content;
		while (path)
		{
			edge = path->content;
			finded = get_edge(edge->from, edge->to, lem);
			if (finded)
				free(finded);
			path = path->next;
		}
		paths = paths->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:55:00 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:55:20 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_way	*new_way(void)
{
	t_way	*new;

	new = malloc(sizeof(t_way));
	if (!new)
		error_f("new_way malloc error", 0);
	new->next = NULL;
	new->len = 0;
	new->ants = 0;
	new->path = NULL;
	new->on = 0;
	return (new);
}

void	insert_node(t_lem *lem, t_list **new_path, t_edge *edge, int end)
{
	t_node	*from;
	t_node	*to;

	from = edge->from;
	to = edge->to;
	if (!ft_lst_pb_copy(new_path, from, sizeof(t_node)))
		error_f("insert_node ft_lstnew malloc", 0);
	if (end)
		if (!ft_lst_pb_copy(new_path, to, sizeof(t_node)))
			error_f("insert_node ft_lstnew malloc", 0);
}

void	copy_path_part(t_lem *lem, t_list *path, t_list **new_path, int *i)
{
	(*new_path) = NULL;
	(*i) = 0;
	while (path)
	{
		if (path->next)
			insert_node(lem, new_path, path->content, 0);
		else
			insert_node(lem, new_path, path->content, 1);
		path = path->next;
		(*i)++;
	}
}

void	copy_paths(t_lem *lem)
{
	t_list	*paths;
	t_list	*path;
	t_list	*new_path;
	int		i;
	t_way	*temp;

	lem->var->ways = new_way();
	paths = lem->paths;
	temp = lem->var->ways;
	while (paths)
	{
		path = paths->content;
		copy_path_part(lem, path, &new_path, &i);
		paths = paths->next;
		temp->path = new_path;
		temp->len = i;
		temp->on = 1;
		if (paths)
		{
			temp->next = new_way();
			temp = temp->next;
		}
	}
	temp->next = NULL;
}

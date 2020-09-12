/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:57:01 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:57:01 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reverse_list(t_list **head_ref)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;

	prev = NULL;
	current = *head_ref;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head_ref = prev;
}

t_graph	*new_graph(void)
{
	t_graph	*graph;

	graph = malloc(sizeof(t_graph));
	if (graph == NULL)
		error_f("reading malloc error", 0);
	graph->nodes = NULL;
	graph->len = 0;
	return (graph);
}

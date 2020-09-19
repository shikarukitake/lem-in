/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:57:13 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:57:13 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	first_solve(t_lem *lem)
{
	lem->graph->nodes->array[lem->graph->end]->prev = NULL;
	create_edge(lem);
	copy_edge(lem);
	bellman_ford(lem);
	if (!(lem->graph->nodes->array[lem->graph->end]->prev))
		error_f("There is no path", 0);
	make_paths(lem);
	if (ft_lstsize(lem->paths->content) > 1)
		dublicate_nodes(lem);
	reverse_list((t_list **)&(lem->paths->content));
	make_solution_from_first(lem);
	count_steps(lem, lem->var);
}

int		second_solve(t_lem *lem)
{
	lem->graph->nodes->array[lem->graph->end]->prev = NULL;
	bellman_ford(lem);
	if (!(lem->graph->nodes->array[lem->graph->end]->prev))
		return (1);
	make_paths_many(lem);
	delete_dublicates(lem);
	set_in_way(lem);
	all_edges_in_paths_connected(lem);
	delete_disjoint_edges(lem);
	make_new_paths(lem);
	if (lem->edges)
		ft_lstdel(&(lem->edges), &del_edge);
	copy_edge(lem);
	refresh_edges(lem);
	delete_copy_nodes(lem);
	dublicate_nodes(lem);
	make_solutuins_from_second(lem);
	count_steps(lem, lem->var);
	lem->graph->nodes->array[lem->graph->end]->prev = NULL;
	return (0);
}

void	solve(t_lem *lem)
{
	first_solve(lem);
	while (check_solutions(lem))
		if (second_solve(lem))
			break ;
	delete_copy_nodes(lem);
	choose_solution(lem);
}

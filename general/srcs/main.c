/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 19:15:11 by sdagger           #+#    #+#             */
/*   Updated: 2020/08/30 15:12:00 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_graph(t_lem *lem)
{
	int		i;
	t_node	*node;
	int		j;

	i = 0;
	while (i != lem->graph->len)
	{
		j = 0;
		node = lem->graph->nodes->array[i];
		ft_printf("Node name: %s\n", node->name);
		ft_printf("Node's neighbors:\n");
		while (j != node->n_len)
		{
			ft_printf("%s\n", ((t_node*)node->neighbors->array[j])->name);
			j++;
		}
		ft_printf("END\n\n");
		i++;
	}
}

int		main(int ac, char **av)
{
	t_lem	*lem;

	lem = error_f(NULL, 1);
	reading(lem);
	//print_graph(lem);
	solve(lem);
	free_lem(lem);
	return (0);
}

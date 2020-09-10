/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 19:15:11 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/09 17:40:40 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
t_lem	*lem;

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

void	parse_flags_lemin(int ac, char **av)
{
	int	i;

	i = 1;
	lem->dflag = 0;
	while (i != ac)
	{
		if (!ft_strcmp("-d", av[i]))
			lem->dflag = 1;
		i++;
	}
}

int		main(int ac, char **av)
{
	lem = error_f(NULL, 1);
	parse_flags_lemin(ac, av);
	reading(lem);//bogdan
	//print_graph(lem);
	ft_printf("\n");
	solve(lem);//ravil
	free_lem(lem);
	exit(0);
	return (0);
}


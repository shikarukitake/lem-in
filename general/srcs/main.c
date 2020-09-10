/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 19:15:11 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/10 15:47:59 by sdagger          ###   ########.fr       */
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

void	parse_flags_lemin(int ac, char **av, t_lem *lem)
{
	int	i;

	i = 1;
	lem->dflag = 0;
	lem->lflag = 0;
	lem->pflag = 0;
	lem->hflag = 0;
	while (i != ac)
	{
		if (!ft_strcmp("-d", av[i]))
			lem->dflag = 1;
		else if (!ft_strcmp("-l", av[i]))
			lem->lflag = 1;
		else if (!ft_strcmp("-p", av[i]))
			lem->pflag = 1;
		else if (!ft_strcmp("-h", av[i]))
			lem->hflag = 1;
		i++;
	}
}

void	execute_flags_after(t_lem *lem)
{
	if (lem->lflag && lem->var)
	{
		ft_printf(COLOR_GREEN);
		ft_printf("\nLines count:%d\n", lem->var->steps);
		ft_printf(COLOR_RESET);
	}
}

void	execute_flags_before(t_lem *lem)
{
	if (lem->hflag)
	{
		ft_printf("Usage: ./lem-in < map\n"
			"-h -- help\n-l -- lines count\n");
		free_lem(lem);
		exit(0);
	}
}

int		main(int ac, char **av)
{
	t_lem	*lem;

	lem = error_f(NULL, 1);
	parse_flags_lemin(ac, av, lem);
	execute_flags_before(lem);
	reading(lem);//bogdan
	//print_graph(lem);
	ft_printf("\n");
	solve(lem);//ravil
	execute_flags_after(lem);
	free_lem(lem);
	exit(0);
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 19:15:11 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/10 16:18:39 by sdagger          ###   ########.fr       */
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

void	print_node_path(t_list *list)
{
	t_node	*node;

	node = list->content;
	if (node)
		ft_printf(" %s", node->name);
}

void	execute_flags_after(t_lem *lem)
{
	t_way	*way;
	int		i;

	if (lem->pflag && lem->var)
	{
		ft_printf(COLOR_MAGENTA);
		ft_printf("\nPATHS:\n");
		ft_printf(COLOR_RESET);
		way = lem->var->ways;
		i = 1;
		while (way)
		{
			ft_printf(COLOR_GREEN);
			ft_printf("Path #%d", i);
			ft_printf(COLOR_RESET);
			ft_lstiter(way->path, &print_node_path);
			ft_printf("\n");
			way = way->next;
			i++;
		}
	}
	if (lem->lflag && lem->var)
	{
		ft_printf(COLOR_GREEN);
		ft_printf("\nCount of lines: %d\n", lem->var->steps);
		ft_printf(COLOR_RESET);
	}
}

void	execute_flags_before(t_lem *lem)
{
	if (lem->hflag)
	{
		ft_printf("Usage: ./lem-in < map\n"
			"Flags:\n"
			"-h -- help\n-l -- count of lines\n");
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


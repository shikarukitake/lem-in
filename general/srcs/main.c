/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 19:15:11 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 18:08:16 by sdagger          ###   ########.fr       */
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

void print_paths_from_solution(t_lem *lem)
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
}

void	execute_flags_after(t_lem *lem)
{
	print_paths_from_solution(lem);
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
	t_read	*reader;

	lem = error_f(NULL, 1);
	parse_flags_lemin(ac, av, lem);
	execute_flags_before(lem);
//	reading(lem);//bogdan
	//print_graph(lem);
	if (!(reader = init_read()))
		error_f("reader malloc error", 0);
	if (reading(reader))
		error_f("reaging error", 0);
	convert_structure(reader, lem);
	write(1, reader->global_line, ft_strlen(reader->global_line));
	reader->line = NULL;
	free_read(reader);
	ft_printf("\n");
	solve(lem);//ravil
	execute_flags_after(lem);
	free_lem(lem);
	exit(0);
	return (0);
}

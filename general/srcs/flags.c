/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 15:11:39 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/13 15:11:41 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	print_paths_from_solution(t_lem *lem)
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

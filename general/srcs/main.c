/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 19:15:11 by sdagger           #+#    #+#             */
/*   Updated: 2020/08/20 18:34:16 by sdagger          ###   ########.fr       */
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
		node = lem->graph->nodes[i];
		ft_printf("Node name: %s\n", node->name);
		ft_printf("Node's neighbors:\n");
		while (j != node->n_len)
		{
			ft_printf("%s\n", ((t_node*)node->neighbors[j])->name);
			j++;
		}
		ft_printf("END\n\n");
		i++;
	}
}

t_node	*new_node(const char *name, const char *x, const char *y)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (new == NULL)
		error_f("new_node malloc", 0);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		error_f("new_node name malloc", 0);
	}
	new->x = ft_atoi(x);
	new->y = ft_atoi(y);
	new->n_len = 0;
	new->neighbors = NULL;
	return (new);
}

int		main(int ac, char **av)
{
	t_lem	*lem;

	lem = error_f(NULL, 1);
	reading(lem);
	print_graph(lem);
//	solve(lem);
	free_lem(lem);
	return (0);
}

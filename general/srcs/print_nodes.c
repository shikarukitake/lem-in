/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 15:15:35 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/13 15:15:36 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				print_nodes_part(int i, t_node *node)
{
	if (node->ant != 0 && node->ant != -1)
	{
		if (i != 0)
			ft_printf(" ");
		ft_printf("L%d-%s", node->ant, node->name);
		i++;
	}
	return (i);
}

void			print_nodes(t_lem *lem)
{
	int		i;
	t_node	*node;
	t_list	*path;
	t_way	*ways;

	ways = lem->var->ways;
	i = 0;
	while (ways)
	{
		path = ways->path;
		while (path)
		{
			node = path->content;
			i = print_nodes_part(i, node);
			path = path->next;
		}
		ways = ways->next;
	}
	if (i != 0)
		ft_printf("\n");
}

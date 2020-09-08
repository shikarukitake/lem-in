/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 19:15:11 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/07 19:01:06 by sdagger          ###   ########.fr       */
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
	return (0);
}

//void	del_nodes(void *elem, size_t size)
//{
//	t_node *node;
//
//	node = (t_node*)elem;
//	free(node->name);
//	free(elem);
//}
//
//void	del_included(void	*list, size_t size)
//{
//	ft_lstdel(&list, NULL);
//}
//
//int		main(void)
//{
//	t_list *general = NULL;
//	t_list *included = NULL;
//	t_node	*some;
//	int value;
//
//	for (int j = 0; j < 10; j++)
//	{
//		ft_printf("j=%d \n", j);
//		included = NULL;
//		for (int i = 0; i < 10; i++)
//		{
//			some = new_node(ft_itoa(i), "0", "0");
//			ft_lst_pb(&included, some, sizeof(t_node));
//			ft_printf("i=%d \n", i);
//		}
//		ft_lst_pb(&general, included, sizeof(t_list));
//
//	}
//	ft_lstdel(&general, &del_included);
//	return (0);
//}

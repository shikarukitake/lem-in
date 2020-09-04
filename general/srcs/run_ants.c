#include "lem_in.h"

extern t_lem	*lem;

void			print_ants(t_list *list)
{
	t_edge	*edge;
	t_node	*from;
	t_node	*to;

	edge = list->content;
	from = edge->from;
	to = edge->to;
	if (to->ant > 0)
	{
		ft_printf("L%d-%s", to->ant, to->name);
		ft_printf(" ");
	}
}

//int				all_ants_in_finish(t_lem *lem)
//{
//	t_list	*path;
//	t_way	*ways;
//	t_node	*node;
//
//	ways = lem->var->ways;
//	while (ways)
//	{
//		path = ways->path;
//		while (path)
//		{
//			node = (t_node*)(path->content);
//			if (node->ant >= 0)
//				return (0);
//			path = path->next;
//		}
//		ways = ways->next;
//	}
//	if (lem->n_ants <= 0)
//		return (1);
//	return (0);
//}

int				all_ants_in_finish(t_lem *lem)
{
	t_list	*path;
	t_way	*ways;
	t_node	*node;

	ways = lem->var->ways;
	while (ways)
	{
		path = ways->path;
//		while (path->next)
//			path = path->next;
		node = path->content;
		if (ways->ants > 0 || node->ant != -1)
			return (0);
		ways = ways->next;
	}
	return (1);
}

void			set_node(t_list	*path, t_way *way)
{
	t_node	*node;
	t_node	*next;

	if (path)
		while (path->next)
		{
			node = path->content;
			next = path->next->content;
			if (next->s_or_end)
			{
				if (way->ants > 0)
				{
					node->ant = ++(lem->i);
					way->ants--;
				}
				else if (way->ants <= 0 && next->ant != -1)
				{
					node->ant = -1;
					next->ant = -1;
				}
				else
					node->ant = next->ant;
			}
			else
				node->ant = next->ant;
			path = path->next;
		}
//	if (from->s_or_end)
//	{
//		if (way->ants > 0)
//		{
//			to->ant = ++(lem->i);
//			way->ants--;
//		}
//		else if (way->ants <= 0)
//		{
//			to->ant = -1;
//		}
//	}
//	else
//		to->ant = from->ant;
}

void			print_nodes()
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
			if (node->ant != 0 && node->ant != -1)
			{
				if (i != 0)
					ft_printf(" ");
				ft_printf("L%d-%s", node->ant, node->name);
				i++;
			}
			path = path->next;
		}
		ways = ways->next;
	}
	if (i != 0)
		ft_printf("\n");
}

void			run_ants(t_lem *lem)
{
	int		n_ants;
	t_list	*path;
	t_way	*ways;

	n_ants = lem->n_ants;
	lem->i = 0;

	ways = lem->var->ways;
	while (ways)
	{
		reverse_list(&(ways->path));
		ways = ways->next;
	}
	while (!all_ants_in_finish(lem))
	{
		ways = lem->var->ways;
		while (ways)
		{
			path = ways->path;
			set_node(path, ways);
			ways = ways->next;
		}
		print_nodes();
//		ways = lem->var->ways;
//		while (ways)
//		{
//			path = ways->path;
//			ft_lstiter(path, &print_ants);
//			ways = ways->next;
//		}
	}

}
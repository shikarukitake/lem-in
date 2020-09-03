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
	t_edge	*edge;

	ways = lem->var->ways;
	while (ways)
	{
		path = ways->path;
		while (path->next)
			path = path->next;
		edge = path->content;
		if (ways->ants > 0 || edge->from->ant != -1)
			return (0);
		ways = ways->next;
	}
	return (1);
}

void			set_node(t_list	*list, void *stuff)
{
	t_edge	*edge;
	t_node	*from;
	t_node	*to;
	t_way	*way;

	way = stuff;
	edge = list->content;
	from = edge->from;
	to = edge->to;
	if (from->s_or_end)
	{
		if (way->ants > 0)
		{
			to->ant = ++(lem->i);
			way->ants--;
		}
		else if (way->ants <= 0)
		{
			to->ant = -1;
		}
	}
	else
		to->ant = from->ant;
}

void			run_ants(t_lem *lem)
{
	int		n_ants;
	t_list	*path;
	t_way	*ways;

	n_ants = lem->n_ants;
	int i = 0;
	lem->i = 0;
	while (!all_ants_in_finish(lem))
	{
		ways = lem->var->ways;
		while (ways)
		{
			path = ways->path;
			ft_lstiter_ext(path, ways, &set_node);
			ways = ways->next;
		}
		ways = lem->var->ways;
		while (ways)
		{
			path = ways->path;
			ft_lstiter(path, &print_ants);
			ways = ways->next;
		}
		ft_printf("\n");
		i++;
		if (i > 100)
			break;
	}

}
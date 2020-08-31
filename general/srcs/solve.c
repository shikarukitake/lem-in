#include "lem_in.h"

void	print_path(t_list *list)
{
	t_edge	*edge;

	edge = (list->content);
	ft_printf("%s-%s ", edge->to->name, edge->from->name);
}

void	print_paths(t_lem *lem)
{
	t_list	*swap;

	swap = lem->paths;
	while (swap)
	{
		ft_lstiter(swap->content, &print_path);
		swap = swap->next;
	}
	ft_printf("\n");
}

void	count_steps(t_lem *lem)
{

}

int		get_running(const t_node *from, const t_node *to, t_list *edges, t_list *swap)
{
	if (edges->next)
	{
		if (((t_edge*)(edges->next->content))->from == to &&
		((t_edge*)(edges->next->content))->to == from)
		{
			swap = edges->next;
			edges->next = edges->next->next;
			free(swap);
			return (1);
		}
	}
	return (0);
}

// TODO REFACTOR TO SMALLER
t_edge	*find_edge(t_node *from, t_node *to, t_lem *lem, int delete_reversed)
{
	t_edge	*edge;
	t_list	*edges;
	t_edge	*finded;
	t_list	*swap;
	int		running;

	edges = lem->edges;
	edge = edges->content;
	finded = NULL;
	running = 0;
	if (edge->from == to && edge->to == from)
	{
		lem->edges = edges->next;
		free(edges);
		edges = edges->next;
		running++;
	}
	while (edges)
	{
		if (running == 2)
			break;
		edge = edges->content;
		if (edge->from == from && edge->to == to)
		{
			finded = edge;
			running++;
		}
		running += get_running(from, to, edges, swap);
		edges = edges->next;
	}
	return (finded);
}

void	one_path(t_lem *lem)
{
	t_list	*path;
	t_node	*node;
	t_edge	*edge;

	path = NULL;
	node = lem->graph->nodes->array[lem->graph->end];
	while (node->prev)
	{
		edge = find_edge(node, node->prev, lem, 1);
		ft_lst_pb(&path, edge, sizeof(t_edge));//TODO protect
		node = node->prev;
	}
	ft_lst_pb(&(lem->paths), path, sizeof(t_list));//TODO protect
}

void	many_paths(t_lem *lem)
{

}

void	make_paths(t_lem *lem, int suurbale)
{
	t_list	*path;
	t_node	*node;

	if (suurbale == 0)
		one_path(lem);
	else
		many_paths(lem);
}

void	solve(t_lem *lem)
{
	int	suurbale_used;

	suurbale_used = 0;
	create_edge(lem);
	if (!bellman_ford(lem))
		error_f("There is no shortest PATH", 0);
	//ft_lstiter(lem->edges, &print_edges);
	make_paths(lem, suurbale_used);
	count_steps(lem);
	print_paths(lem);
	suurbale(lem);
}
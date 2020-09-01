#include "lem_in.h"

void	print_path(t_list *list)
{
	t_edge	*edge;

	edge = (list->content);
	ft_printf("%s-%s ", edge->from->name, edge->to->name);
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
//t_edge	*get_edge(t_node *from, t_node *to, t_lem *lem)
//{
//	t_edge	*edge;
//	t_list	*edges;
//	t_edge	*finded;
//	t_list	*swap;
//	int		running;
//
//	edges = lem->edges;
//	edge = edges->content;
//	finded = NULL;
//	running = 0;
//	if (edge->from == to && edge->to == from)
//	{
//		lem->edges = edges->next;
//		free(edges);
//		edges = edges->next;
//		running++;
//	}
//	while (edges)
//	{
//		if (running == 2)
//			break;
//		edge = edges->content;
//		if (edge->from == from && edge->to == to)
//		{
//			finded = edge;
//			running++;
//		}
//		running += get_running(from, to, edges, swap);
//		edges = edges->next;
//	}
//	return (finded);
//}

t_edge	*get_first_edge(t_node *from, t_node *to, t_lem *lem, int *running)
{
	t_edge	*edge;
	t_list	*temp;

	edge = lem->edges->content;
	if (edge->from == from && edge->to == to)
	{
		temp = lem->edges->next;
		free(lem->edges);
		lem->edges = temp;
		*running += 1;
		return (edge);
	}
	else if (edge->from == to && edge->to == from)
	{
		edge->w = -1;
		*running += 1;
	}
	return (NULL);
}

t_edge	*get_other_edge(t_node *from, t_node *to, t_list *edges, int *running)
{
	t_edge	*edge;
	t_list	*temp;

	edge = edges->next->content;
	if (edge->from == from && edge->to == to)
	{
		temp = edges->next->next;
		free(edges->next);
		edges->next = temp;
		*running += 1;
		return (edge);
	}
	else if (edge->from == to && edge->to == from)
	{
		edge->w = -1;
		*running += 1;
	}
	return (NULL);
}

/*
** This function get edge with same from node and same to node and set weight -1 to reversed edge
*/

t_edge	*get_edge(t_node *from, t_node *to, t_lem *lem)
{
	t_edge	*edge;
	t_list	*edges;
	t_edge	*finded;
	int		running;

	finded = NULL;
	edge = NULL;
	running = 0;
	edge = get_first_edge(from, to, lem, &running);
	if (edge)
		finded = edge;
	edges = lem->edges;
	while (edges && edges->next)
	{
		if (running == 2)
			break;
		edge = get_other_edge(from, to, edges, &running);
		if (edge)
			finded = edge;
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
		edge = get_edge(node->prev, node, lem);
		if (edge)
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

void	create_copy(t_lem *lem, t_edge *edge_dub)
{
	t_node	*copy;
	t_node	*current;

	current = edge_dub->from;
	copy = new_node(ft_strjoin(current->name, "_copy"), "0", "0");
	if (!copy)
		error_f("create_copy new_node malloc", 0);
	edge_dub->from->copy = copy;

	current = edge_dub->to;
	copy = new_node(ft_strjoin(current->name, "_copy"), "0", "0");
	if (!copy)
		error_f("create_copy new_node malloc", 0);
	edge_dub->to->copy = copy;
}

void	add_relation(t_lem *lem, t_edge *edge_dub)
{
	t_list	*new;
	t_edge	*edge;

	edge = new_edge(edge_dub->from->copy, edge_dub->from);
	if (!edge)
		error_f("add_relation new_edge malloc", 0);
	edge->w = 0;
	new = ft_lstnew(edge, sizeof(t_edge));
	if (!new)
		error_f("add_relation ft_lstnew malloc", 0);
	ft_lstadd(&(lem->edges), new);

	edge = new_edge(edge_dub->to->copy, edge_dub->to);
	if (!edge)
		error_f("add_relation new_edge malloc", 0);
	edge->w = 0;
	new = ft_lstnew(edge, sizeof(t_edge));
	if (!new)
		error_f("add_relation ft_lstnew malloc", 0);
	ft_lstadd(&(lem->edges), new);
}

void	dublicate_node(t_lem *lem, t_edge *edge_dub)
{
	t_list	*edges;
	t_edge	*edge;

	edges = lem->edges;
	create_copy(lem, edge_dub);
	while (edges)
	{
		edge = edges->content;
		if (edge->from == edge_dub->from && edge->w != -1)
			edge->from = edge_dub->from->copy;
		else if (edge->from == edge_dub->to && edge->to == edge_dub->from)
			edge->to = edge->to->copy;
		else if (edge->from == edge_dub->to && edge->w != -1)
			edge->from = edge_dub->to->copy;
		else if (edge->to == edge_dub->to && edge->w == -1)
			edge->to = edge_dub->to->copy;
		edges = edges->next;
	}
	add_relation(lem, edge_dub);
}

void	dublicate_nodes(t_lem *lem)
{
	t_list	*paths;
	t_list	*path;

	paths = lem->paths;
	while (paths)
	{
		path = ((t_list*)(paths->content))->next;
		while (path->next)
		{
			dublicate_node(lem, path->content);
			path = path->next;
		}
		paths = paths->next;
	}
}

void	make_new_paths(lem)
{

}

void	solve(t_lem *lem)
{
	int	suurbale_used;

	suurbale_used = 0;
	create_edge(lem);
	bellman_ford(lem);
	if (!(lem->graph->nodes->array[lem->graph->end]->prev))
		error_f("There is no path", 0);
	make_paths(lem, suurbale_used);
	dublicate_nodes(lem);
	count_steps(lem);
	print_paths(lem);
//	ft_lstiter(lem->edges, &print_edges);

//	bellman_ford(lem);
//	suurbale(lem);
}
#include "lem_in.h"

void	change_path_dublicates(t_list *list)
{
	t_edge	*edge;

	edge = list->content;
	if (edge->from->is_copy == 0 && edge->to->is_copy == 1)
	{
		edge->to = edge->to->copy;
		edge->to->in_way++;
	}
	else if (edge->from->is_copy == 1 && edge->to->is_copy == 0)
	{
		edge->from = edge->from->copy;
		edge->from->in_way++;
	}
	else if (edge->from->is_copy == 1 && edge->to->is_copy == 1)
	{
		edge->to = edge->to->copy;
		edge->from = edge->from->copy;
		edge->to->in_way++;
		edge->from->in_way++;
	}
}

void	delete_copy_nodes(t_lem *lem)
{
	t_node	**nodes;
	int		i;

	i = 0;
	nodes = lem->graph->nodes->array;
	while (i != lem->graph->len)
	{
		if (nodes[i]->copy)
		{
			free_node(&(nodes[i]->copy));
			nodes[i]->copy = NULL;
		}
		i++;
	}
}

void	delete_dublicates(t_lem *lem)
{
	t_list	*paths;

	paths = lem->paths;
	while (paths)
	{
		ft_lstiter(paths->content, &change_path_dublicates);
		paths = paths->next;
	}
	ft_lstdel(&(lem->edges), &del_edge);

	lem->edges = NULL;
}
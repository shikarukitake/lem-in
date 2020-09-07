#include "lem_in.h"

t_node	*find_node_without_delete(t_lem *lem, const char *name)
{
	int i;

	i = 0;
	while (i != lem->graph->len)
	{
		if (!ft_strcmp(lem->graph->nodes->array[i]->name, name))
			return (lem->graph->nodes->array[i]);
		i++;
	}
}

t_edge	*find_edge_without_delete(t_lem *lem, t_node *from, t_node *to)
{
	t_list	*paths;
	t_list	*path;
	t_edge	*edge;

	paths = lem->paths;
	while (paths)
	{
		path = paths->content;
		while (path)
		{
			edge = path->content;
			if (edge->from == from && edge->to == to)
				return (edge);
			path = path->next;
		}
		paths = paths->next;
	}
	return (NULL);
}
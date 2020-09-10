#include "lem_in.h"

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
		else
			edges = edges->next;
	}
	return (finded);
}

void	make_paths(t_lem *lem, int suurbale)
{
	t_list	*path;
	t_node	*node;
	t_edge	*edge;

	path = NULL;
	node = lem->graph->nodes->array[lem->graph->end];
	while (node->prev)
	{
		edge = get_edge(node->prev, node, lem);
		node->prev->in_way++;
		node->in_way++;
		if (edge)
			if (!ft_lst_pb(&path, edge, sizeof(t_edge)))
				error_f("one_path ft_lstnew malloc", 0);
		node = node->prev;
	}
	if (!ft_lst_pb(&(lem->paths), path, sizeof(t_list)))
		error_f("one_path ft_lstnew malloc", 0);
}

void	create_copy(t_lem *lem, t_edge *edge_dub)
{
	t_node	*copy;
	t_node	*current;

	current = edge_dub->from;
	if (current->copy == NULL)
	{
		copy = new_node(ft_strjoin(current->name, "_copy"), "0", "0");
		if (!copy)
			error_f("create_copy new_node malloc", 0);
		copy->is_copy = 1;
		copy->copy = edge_dub->from;
		edge_dub->from->copy = copy;
	}

	current = edge_dub->to;
	if (current->copy == NULL)
	{
		copy = new_node(ft_strjoin(current->name, "_copy"), "0", "0");
		if (!copy)
			error_f("create_copy new_node malloc", 0);
		copy->is_copy = 1;
		copy->copy = edge_dub->to;
		edge_dub->to->copy = copy;
	}
}

void	one_relation(t_node *from, t_node *to, t_lem *lem)
{
	t_list	*new;
	t_edge	*edge;

	edge = new_edge(from, to);
	if (!edge)
		error_f("add_relation new_edge malloc", 0);
	edge->w = 0;
	new = ft_lstnew(edge, sizeof(t_edge));
	if (!new)
	{
		free(edge);
		error_f("add_relation ft_lstnew malloc", 0);
	}
	ft_lstadd(&(lem->edges), new);
}

void	add_relation(t_lem *lem, t_edge *edge_dub)
{
	one_relation(edge_dub->from->copy, edge_dub->from, lem);
	one_relation(edge_dub->to->copy, edge_dub->to, lem);
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

/*
** find_edge
*/

int		path_edges(t_edge *a, t_edge *b)
{
	if (b->to == a->from)
		return (1);
	else
		return (0);
}

int		disjoint_edge(t_edge *a, t_edge *b)
{
	if (a->from == b->to && a->to == b->from)
		return (1);
	else
		return (0);
}

int		in_way_edge(t_edge *a, t_edge *b)
{
	if (a->from->in_way > 2 && a->to->in_way > 2)
	{
		if (a->from->s_or_end || a->to->s_or_end)
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

int		start_edges(t_edge *a, t_edge *b)
{
	if (a->from->s_or_end)
		return (1);
	return (0);
}

t_edge *find_edge_part(t_edge *edge, int (*f)(t_edge *, t_edge *), t_edge *finded, t_list *temp, t_list *prev)
{
	while (temp)
	{
		finded = temp->content;
		if (f(finded, edge))
			break;
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (NULL);
	prev->next = temp->next;
	free(temp);
	return (finded);
}

t_edge	*find_edge(t_list	**paths, t_edge *edge, int (*f)(t_edge*, t_edge*))//todo norm
{
	t_edge	*finded;
	t_list	*temp;
	t_list	*prev;

	temp = *paths;
	prev = *paths;
	finded = NULL;
	if (temp != NULL)
	{
		finded = temp->content;
		if (f(finded, edge))
		{
			*paths = temp->next;
			free(temp);
			return (finded);
		}
		return (find_edge_part(edge, f, finded, temp, prev));
	}
	return (NULL);
}

/*
** find_edge end
*/

void	make_new_paths(t_lem *lem)
{
	t_edge	*edge;
	t_list	*path;

	lem->paths = NULL;
	while (lem->new_paths)
	{
		path = NULL;
		edge = find_edge(&(lem->new_paths), NULL, &start_edges);
		if (!ft_lst_pb(&path, edge, sizeof(t_edge)))
			error_f("make_new_paths ft_lstnew malloc", 0);
		if (!ft_lst_pb(&(lem->paths), path, sizeof(t_list)))
			error_f("make_new_paths ft_lstnew malloc", 0);
		while (edge->to != lem->graph->nodes->array[lem->graph->end])
		{
			edge = find_edge(&(lem->new_paths), edge, &path_edges);
			if (!ft_lst_pb(&path, edge, sizeof(t_edge)))
				error_f("make_new_paths ft_lstnew malloc", 0);
			if (edge == NULL)
				error_f("something wrong maybe very big map", 0);
		}
	}
}

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

void	del_edges(void *content, size_t size)//TODO SAME FUNCTION DEL_EDGE
{
	t_edge	*edge;

	edge = content;
	free(edge);
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
	ft_lstdel(&(lem->edges), &del_edges);

	lem->edges = NULL;
}

void	cpy_back(t_lem *lem, t_list	*temp_list)
{
	t_list	*temp;

	temp = temp_list;
	while (temp->next)
		temp = temp->next;
	temp->next = lem->new_paths;
	lem->new_paths = temp_list;
}

void	get_find_edge(t_lem *lem, t_edge *edge, t_list **temp_list)
{
	t_edge *temp;

	temp = find_edge(&(lem->new_paths), edge, &disjoint_edge);
	if (temp)
	{
		edge->from->in_way -= 2;
		edge->to->in_way -= 2;
		free(edge);
		free(temp);
	}
	else
		if (!ft_lst_pb(temp_list, edge, sizeof(t_edge)))
			error_f("delete_disjoint malloc", 0);//todo safe
}

void	delete_disjoint_edges(t_lem *lem)
{
	t_edge	*edge;
	t_edge	*temp;
	t_list	*temp_list;

	temp_list = NULL;
	edge = find_edge(&(lem->new_paths), NULL, &in_way_edge);
	while (edge)
	{
		if (edge->from == edge->to)
			free(edge);
		else
			get_find_edge(lem, edge, &temp_list);
		edge = find_edge(&(lem->new_paths), NULL, &in_way_edge);
	}
	if (temp_list)
		cpy_back(lem, temp_list);
}

void	all_edges_in_paths_connected(t_lem *lem)
{
	t_list	*paths;
	t_list	*path;
	t_list	*temp;

	paths = lem->paths;
	while (paths)
	{
		path = paths->content;
		if (lem->new_paths == FT_NULL)
			lem->new_paths = path;
		else
		{
			temp = path;
			while (path->next)
			{
				path = path->next;
			}
			path->next = lem->new_paths;
			lem->new_paths = temp;
		}
		paths = paths->next;
	}
	ft_lstdel(&(lem->paths), NULL);
	lem->paths = NULL;
}

void	copy_edge(t_lem *lem)
{
	t_list	*edges;
	t_list	*new;
	t_list	*new_lstnew;

	edges = lem->origin_edges;
	new = NULL;
	while (edges)
	{
		new_lstnew = ft_lstnew_copy(edges->content, edges->content_size);
		if (new_lstnew == NULL)
			error_f("copy_edge ft_lstnew_copy", 0);
		ft_lstadd(&new, new_lstnew);
		edges = edges->next;
	}
	lem->edges = new;
}

void	refresh_edges(t_lem *lem)
{
	t_list	*paths;
	t_list	*path;
	t_edge	*edge;
	t_edge	*finded;

	paths = lem->paths;
	while (paths)
	{
		path = paths->content;
		while (path)
		{
			edge = path->content;
			finded = get_edge(edge->from, edge->to, lem);
			if (finded)
				free(finded);
			path = path->next;
		}
		paths = paths->next;
	}
}

void	make_paths_many(t_lem *lem)
{
	t_list	*path;
	t_node	*node;
	t_edge	*edge;

	path = NULL;
	node = lem->graph->nodes->array[lem->graph->end];
	while (node->prev)
	{
		edge = new_edge(node->prev, node);
		node->prev->in_way++;
		node->in_way++;
		if (!edge)
			error_f("make_paths_many malloc", 0);
		if (!ft_lst_pb(&path, edge, sizeof(t_edge)))
			error_f("make_paths_many ft_lstnew malloc", 0);
		node = node->prev;
	}
	if (!ft_lst_pb(&(lem->paths), path, sizeof(t_list)))
		error_f("one_path ft_lstnew malloc", 0);
}

void	first_solve(t_lem *lem)
{
	lem->graph->nodes->array[lem->graph->end]->prev = NULL;
	create_edge(lem);
	copy_edge(lem);
	bellman_ford(lem);
	if (!(lem->graph->nodes->array[lem->graph->end]->prev))
		error_f("There is no path", 0);
	make_paths(lem, 0);
	if (ft_lstsize(lem->paths->content) > 1)
		dublicate_nodes(lem);
	reverse_list((t_list **)&(lem->paths->content));
	make_solution_from_first(lem);
	count_steps(lem, lem->var);
}

int		second_solve(t_lem *lem)
{
	lem->graph->nodes->array[lem->graph->end]->prev = NULL;
	bellman_ford(lem);
	if (!(lem->graph->nodes->array[lem->graph->end]->prev))
		return (1);
	make_paths_many(lem);
	delete_dublicates(lem);
	set_in_way(lem);
	all_edges_in_paths_connected(lem);
	delete_disjoint_edges(lem);
	make_new_paths(lem);
	if (lem->edges)
		ft_lstdel(&(lem->edges), &del_edge);
	copy_edge(lem);
	refresh_edges(lem);
	delete_copy_nodes(lem);
	dublicate_nodes(lem);
	make_solutuins_from_second(lem);
	count_steps(lem, lem->var);
	lem->graph->nodes->array[lem->graph->end]->prev = NULL;
	return (0);
}

void	solve(t_lem *lem)
{
	first_solve(lem);
	while (check_solutions(lem))
		if (second_solve(lem))
			break;
	delete_copy_nodes(lem);
	choose_solution(lem);
	run_ants(lem);
}

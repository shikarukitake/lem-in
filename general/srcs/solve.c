#include <stdbool.h>
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
		ft_printf("\n");
	}
}

void			distribute_ants(t_lem *lem, t_var *var, int max_len)
{
	int			n;
	int			s;
	t_way		*tmp;

	s = max_len - 1;
	n = lem->n_ants;
	tmp = var->ways;
	while (tmp && n > 0 && var->n_ways != 1)
	{
		if (tmp->on)
		{
			tmp->ants = (n < max_len - tmp->len) ? n : max_len - tmp->len;
			n -= tmp->ants;
		}
		tmp = tmp->next;
	}
	s += (n % var->n_ways == 0) ? n / var->n_ways : n / var->n_ways + 1;
	tmp = var->ways;
	while (n-- > 0)
	{
		++tmp->ants;
		tmp = (tmp->next) ? tmp->next : var->ways;
	}
	var->steps = s;
}

void			count_steps(t_lem *lem, t_var *var)
{
	int			max_len;
	int			valid_space;
	t_way		*tmp;

	valid_space = 0;
	tmp = var->ways;
	max_len = tmp->len;
	if (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->len > max_len)
			max_len = tmp->len;
		tmp = tmp->next;
	}
	tmp = var->ways;
	while (tmp)
	{
		valid_space += max_len - tmp->len;
		tmp = tmp->next;
	}
	distribute_ants(lem, var, max_len);
}


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
		node->prev->in_way++;
		node->in_way++;
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
	copy->is_copy = 1;
	copy->copy = edge_dub->from;
	edge_dub->from->copy = copy;

	current = edge_dub->to;
	copy = new_node(ft_strjoin(current->name, "_copy"), "0", "0");
	if (!copy)
		error_f("create_copy new_node malloc", 0);
	copy->is_copy = 1;
	copy->copy = edge_dub->to;
	edge_dub->to->copy = copy;
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
		error_f("add_relation ft_lstnew malloc", 0);
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

t_list	*find_and_delete_first(t_lem *lem)
{
	t_list	*old_paths;
	t_list	*temp;
	t_edge	*edge;
	t_list	*temp_list;

	old_paths = lem->new_paths;
	edge = old_paths->content;
	temp = NULL;
	if (edge->from->s_or_end)
	{
		lem->new_paths = old_paths->next;
		ft_lstadd(&(temp), old_paths);
		ft_lst_pb(&(lem->paths), temp, sizeof(t_list));
		return (temp);
	}
	while (old_paths->next)
	{
		edge = old_paths->next->content;
		if (edge->from->s_or_end)
		{
			temp_list = old_paths->next->next;
			ft_lstadd(&(temp), old_paths->next);
			ft_lst_pb(&(lem->paths), temp, sizeof(t_list));
			old_paths->next = temp_list;
			return (temp);
		}
		old_paths = old_paths->next;
	}
	return (NULL);
}

void	make_new_paths(t_lem *lem)
{
	t_list	*old_paths;
	t_list	*path;
	t_edge	*edge;
	t_edge	*temp_edge;
	t_list	*prev;

	while (lem->new_paths)
	{
		path = find_and_delete_first(lem);
		if (!path)
			return;
		edge = path->content;
		old_paths = lem->new_paths;
		prev = NULL;
		while (old_paths)
		{
			temp_edge = old_paths->content;
			if (temp_edge->from == edge->to)//TODO FREE
			{
				ft_lst_pb(&path, temp_edge, sizeof(t_edge));
				if (prev)
				{
					prev->next = old_paths->next;
					old_paths = old_paths->next;
				}
				else
				{
					old_paths = old_paths->next;
					lem->new_paths = old_paths;
				}
				edge = temp_edge;
				if (edge->to == lem->graph->nodes->array[lem->graph->end])
					break;
			}
			else
			{
				prev = old_paths;
				old_paths = old_paths->next;
			}
			if (!old_paths)
				old_paths = lem->new_paths;
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

void	delete_disjoint(t_list	*list)
{
	t_edge	*edge;
	t_list	*temp;

	if (list->next)
	{
		edge = list->next->content;
		if (edge->from->in_way > 2 && edge->to->in_way > 2)
		{
			if (edge->from->s_or_end || edge->to->s_or_end)
				return ;
			free(edge);
			temp = list->next;
			list->next = list->next->next;
			free(temp);
		}
	}
}

void	delete_disjoint_edges(t_lem *lem)
{
	t_list	*paths;

	paths = lem->paths;
	while (paths)
	{
		ft_lstiter(paths->content, &delete_disjoint);
		paths = paths->next;
	}
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

t_var	*new_var(int n_ways)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		error_f("make solution from first var malloc error", 0);
	var->n_ways = n_ways;
	var->ways = NULL;
	var->next = NULL;
	var->steps = 0;
	return (var);
}

t_way	*new_way(void)
{
	t_way	*new;

	new = malloc(sizeof(t_way));
	if (!new)
		error_f("new_way malloc error", 0);
	new->next = NULL;
	new->len = 0;
	new->ants = 0;
	new->path = NULL;
	new->on = 0;
	return (new);
}

void	copy_paths(t_lem *lem)
{
	t_list	*paths;
	t_list	*path;
	t_list	*new_path;
	int		i;
	t_way	*temp;

	lem->var->ways = new_way();
	paths = lem->paths;
	temp = lem->var->ways;
	while (paths)
	{
		path = paths->content;
		new_path = NULL;
		i = 0;
		while (path)
		{
			ft_lst_pb_copy(&new_path, path->content, path->content_size);
			path = path->next;
			i++;
		}
		temp->path = new_path;
		temp->len = i;
		temp->on = 1;
		temp->next = new_way();
		temp = temp->next;
		paths = paths->next;
	}
}

void	make_solution_from_first(t_lem *lem)
{
	lem->var = new_var(1);
	copy_paths(lem);
}

void	reverse_list(t_list **head_ref)
{
	t_list	*prev = NULL;
	t_list	*current = *head_ref;
	t_list	*next = NULL;
	while (current != NULL) {
		// Store next
		next = current->next;

		// Reverse current node's pointer
		current->next = prev;

		// Move pointers one position ahead.
		prev = current;
		current = next;
	}
	*head_ref = prev;
}

void	first_solve(t_lem *lem)
{
	create_edge(lem);
	bellman_ford(lem);
	if (!(lem->graph->nodes->array[lem->graph->end]->prev))
		error_f("There is no path", 0);
	make_paths(lem, 0);
	dublicate_nodes(lem);
	reverse_list(&(lem->paths->content));
	make_solution_from_first(lem);
	count_steps(lem, lem->var);
	ft_printf("\nsteps=%d\n\n", lem->var->steps);
	print_paths(lem);
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

void	free_var(t_var	**var)//todo complete free
{
	free(*var);
	*var = NULL;
}

void	make_solutuins_from_second(t_lem *lem)
{
	t_var	*temp_var;
	int		n_ways;

	temp_var = lem->var;
	n_ways = (int)ft_lstsize(lem->paths);
	if (temp_var->next)
	{
		free_var(&(lem->var->next));
		lem->var = new_var(n_ways);
		lem->var->next = temp_var;
	}
	else
	{
		lem->var = new_var(n_ways);
		lem->var->next = temp_var;
	}
	copy_paths(lem);
}


int		second_solve(t_lem *lem)
{
	bellman_ford(lem);
	if (!(lem->graph->nodes->array[lem->graph->end]->prev))
		return (1);
	make_paths(lem, 0);
	delete_dublicates(lem);
	ft_printf("\nfinded paths:\n");
	print_paths(lem);
	delete_disjoint_edges(lem);
	ft_printf("\ndeleted disjoint edges paths:\n");
	print_paths(lem);
	all_edges_in_paths_connected(lem);
	ft_printf("\nall path's edges:\n");
	ft_lstiter(lem->new_paths, &print_path);
	make_new_paths(lem);
	create_edge(lem);
	refresh_edges(lem);
	ft_printf("\n\nall new paths:\n");
	if (lem->paths)
		print_paths(lem);
	dublicate_nodes(lem);
	make_solutuins_from_second(lem);
	count_steps(lem, lem->var);
	ft_printf("\nsteps=%d\n\n", lem->var->steps);
	lem->graph->nodes->array[lem->graph->end]->prev = NULL;
//	ft_lstiter(lem->edges, &print_edges);
//	ft_lstiter(lem->edges, &print_edges);
	return (0);
}


int		check_solutions(t_lem *lem)
{
	if (lem->var->next == NULL)
		return (1);
	else
	{
		if (lem->var->steps < lem->var->next->steps)
			return (1);
		else
			return (0);
	}
	return (0);
}

void	solve(t_lem *lem)
{


	// FIRST
	first_solve(lem);
	//	ft_lstiter(lem->edges, &print_edges);

	//second
	while (check_solutions(lem))
		if (second_solve(lem))
			break;
}
//todo COUNT_STEPS
//todo ANTS RUNNING
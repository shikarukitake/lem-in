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
			if (!ft_lst_pb(&path, edge, sizeof(t_edge)))
				error_f("one_path ft_lstnew malloc", 0);
		node = node->prev;
	}
	if (!ft_lst_pb(&(lem->paths), path, sizeof(t_list)))
		error_f("one_path ft_lstnew malloc", 0);
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

int		equal_edges(t_edge *a, t_edge *b)
{
	if (a->from == b->from &&
		a->to == b->to)
		return (1);
	else
		return (0);
}

int		path_edges(t_edge *a, t_edge *b)
{
	if (b->to == a->from)
		return (1);
	else
		return (0);
}

int		start_edges(t_edge *a, t_edge *b)
{
	if (a->from->s_or_end)
		return (1);
	return (0);
}

t_edge	*find_edge(t_list	**paths, t_edge *edge, int (*f)(t_edge*, t_edge*))
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
	return (NULL);
}

void	make_new_paths(t_lem *lem)
{
	t_list	*new_paths;
	t_edge	*edge;
	t_list	*path;
	t_edge	*temp;//todo delete

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
			temp = edge;
			edge = find_edge(&(lem->new_paths), edge, &path_edges);
			if (!ft_lst_pb(&path, edge, sizeof(t_edge)))
				error_f("make_new_paths ft_lstnew malloc", 0);
			if (edge == NULL)
			{
//				ft_lstiter(path, &print_path);
				error_f("something wrong maybe very big map", 0);
			}
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

void	insert_node(t_lem *lem, t_list **new_path, t_edge *edge, int end)
{
	t_node	*from;
	t_node	*to;

	from = edge->from;
	to = edge->to;

	if (!ft_lst_pb_copy(new_path, from, sizeof(t_node)))
		error_f("insert_node ft_lstnew malloc", 0);
	if (end)
		if (!ft_lst_pb_copy(new_path, to, sizeof(t_node)))
			error_f("insert_node ft_lstnew malloc", 0);
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
			if (path->next)
				insert_node(lem, &new_path, path->content, 0);
			else
				insert_node(lem, &new_path, path->content, 1);
			path = path->next;
			i++;
		}
		paths = paths->next;
		temp->path = new_path;
		temp->len = i;
		temp->on = 1;
		if (paths)
		{
			temp->next = new_way();
			temp = temp->next;
		}
	}
	temp->next = NULL;
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


void copy_edge(t_lem *lem)
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

void	first_solve(t_lem *lem)
{
	lem->graph->nodes->array[lem->graph->end]->prev = NULL;
	create_edge(lem);
	copy_edge(lem);
	bellman_ford(lem);
	if (!(lem->graph->nodes->array[lem->graph->end]->prev))
		error_f("There is no path", 0);
	make_paths(lem, 0);
	dublicate_nodes(lem);
	reverse_list(&(lem->paths->content));
	make_solution_from_first(lem);
	count_steps(lem, lem->var);
//	ft_printf("\nsteps=%d\n\n", lem->var->steps);
//	print_paths(lem);
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

void	del_node_l(t_list *list, size_t size)
{
	free_node(list->content);
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
		lem->var->next = NULL;
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

void	refresh_nodes(t_lem *lem)
{
	int i;

	i = 0;
	while (i != lem->graph->len)
	{
		if (lem->graph->nodes->array[i]->copy)
		{
			free(lem->graph->nodes->array[i]->copy);//todo maybe need free
			lem->graph->nodes->array[i]->copy = NULL;
		}
		i++;
	}
}


void	clear_in_way(t_lem *lem)
{
	t_node	**nodes;
	int		i;

	nodes = lem->graph->nodes->array;
	i = 0;
	while (i != lem->graph->len)
	{
		nodes[i]->in_way = 0;
		i++;
	}
}

void	set_way_path(t_list *elem)
{
	t_edge	*edge;

	edge = elem->content;
	edge->from->in_way++;
	edge->to->in_way++;
}

void	set_way_paths(t_list *elem)
{
	ft_lstiter(elem->content, &set_way_path);
}

void	set_in_way(t_lem *lem)
{
	clear_in_way(lem);
	ft_lstiter(lem->paths, &set_way_paths);
}

int		second_solve_time(t_lem *lem)
{
	clock_t		begin;
	clock_t		end;
	double		time_spent;

	lem->graph->nodes->array[lem->graph->end]->prev = NULL;

	printf("\n\nSTART");
	begin = clock();
	bellman_ford(lem);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("bellman_ford: %f\n", time_spent);
	if (!(lem->graph->nodes->array[lem->graph->end]->prev))
		return (1);

	begin = clock();
	make_paths(lem, 0);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("make_paths: %f\n", time_spent);



	begin = clock();
	delete_dublicates(lem);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("delete_dublicates: %f\n", time_spent);

//	ft_printf("\nfinded paths:\n");
//	print_paths(lem);
	begin = clock();
	set_in_way(lem);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("set_in_way: %f\n", time_spent);

	begin = clock();
	delete_disjoint_edges(lem);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("delete_disjoint_edges: %f\n", time_spent);

//	ft_printf("\ndeleted disjoint edges paths:\n");
//	print_paths(lem);
	begin = clock();
	all_edges_in_paths_connected(lem);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("all_edges_in_paths_connected: %f\n", time_spent);
//	ft_printf("\nall path's edges:\n");
//	ft_lstiter(lem->new_paths, &print_path);
//	ft_printf("\n\n");

	begin = clock();
	make_new_paths(lem);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("make_new_paths: %f\n", time_spent);

	if (lem->edges)
		ft_lstdel(&(lem->edges), &del_edge);
	begin = clock();
	copy_edge(lem);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("copy_edge: %f\n", time_spent);

	begin = clock();
	refresh_edges(lem);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("refresh_edges: %f\n", time_spent);


	begin = clock();
	delete_copy_nodes(lem);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("delete_copy_nodes: %f\n", time_spent);
//	ft_printf("\n\nall new paths:\n");
//	if (lem->paths)
//		print_paths(lem);
	begin = clock();
	dublicate_nodes(lem);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("dublicate_nodes: %f\n", time_spent);


	begin = clock();
	make_solutuins_from_second(lem);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("make_solutuins_from_second: %f\n", time_spent);

	begin = clock();
	count_steps(lem, lem->var);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("count_steps: %f\n", time_spent);

//	ft_printf("\nsteps=%d\n\n", lem->var->steps);
	lem->graph->nodes->array[lem->graph->end]->prev = NULL;
//	ft_lstiter(lem->edges, &print_edges);
//	ft_lstiter(lem->edges, &print_edges);
	return (0);
}

int		second_solve(t_lem *lem)
{
	lem->graph->nodes->array[lem->graph->end]->prev = NULL;
	bellman_ford(lem);
	if (!(lem->graph->nodes->array[lem->graph->end]->prev))
		return (1);
	make_paths(lem, 0);
	delete_dublicates(lem);
	ft_printf("\nfinded paths:\n");
	print_paths(lem);
	set_in_way(lem);
	delete_disjoint_edges(lem);
	ft_printf("\ndeleted disjoint edges paths:\n");
	print_paths(lem);
	all_edges_in_paths_connected(lem);
	ft_printf("\nall path's edges:\n");
	ft_lstiter(lem->new_paths, &print_path);
	ft_printf("\n\n");
	make_new_paths(lem);
	if (lem->edges)
		ft_lstdel(&(lem->edges), &del_edge);
//	create_edge(lem);
	copy_edge(lem);
	refresh_edges(lem);
	delete_copy_nodes(lem);
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

void	choose_solution(t_lem *lem)
{
	t_var	*temp;

	if (lem->var->next)
		if (lem->var->steps > lem->var->next->steps)
		{
			temp = lem->var;
			lem->var = lem->var->next;
			free_var(&temp);
		}
}

void	solve(t_lem *lem)
{


	// FIRST
	first_solve(lem);
	//	ft_lstiter(lem->edges, &print_edges);

	//second
	while (check_solutions(lem))
	{
		if (lem->dflag == 0)
		{
			if (second_solve(lem))
				break;
		}
		else if (lem->dflag == 1)
		{
			if (second_solve_time(lem))
				break;
		}
	}
	delete_copy_nodes(lem);
	choose_solution(lem);
	run_ants(lem);
}
//todo ANTS RUNNING
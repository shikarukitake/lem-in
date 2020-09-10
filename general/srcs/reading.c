#include "lem_in.h"

void		parse_nants(t_lem *lem)
{
	long	n_ants;

	n_ants = ft_atoi_l(lem->temps);
	if (n_ants > FT_INT_MAX || n_ants < FT_INT_MIN)
		error_f("parse_nants n_ants overflow", 0);
	lem->n_ants = (int)n_ants;
	ft_printf("%s\n", lem->temps);
}

void		parse_sharp(t_lem *lem)
{
	if (lem->temps[1] == '#')
	{
		if (!ft_strcmp(lem->temps, "##start"))
		{
			lem->next_start = 1;
			ft_printf("%s\n", "##start");
		}
		else if (!ft_strcmp(lem->temps, "##end"))
		{
			lem->next_end = 1;
			ft_printf("%s\n", "##end");
		}
	}
	else
		ft_printf("%s\n", lem->temps);
}

t_node		*find_node(const char *name, t_graph *graph)
{
	int		i;
	t_node	**nodes;

	i = 0;
	nodes = graph->nodes->array;
	while (i != graph->nodes->len)
	{
		if (!ft_strcmp(nodes[i]->name, name))
			return (nodes[i]);
		i++;
	}
	return (NULL);
}

int			in_neighbors(t_dynamicarr *arr_d, int len, t_node *target)
{
	int		i;
	t_node	**arr;

	if (arr_d == FT_NULL)
		return (0);
	arr = arr_d->array;
	i = 0;
	if (len == 0)
		return (0);
	while (arr[i])
	{
		if (arr[i] == target)
			return (1);
		i++;
	}
	return (0);
}

void		create_link(t_lem *lem)
{
	t_node	*f;
	t_node	*s;

	f = find_node(lem->temps_d[0], lem->graph);
	s = find_node(lem->temps_d[1], lem->graph);

	if (in_neighbors(f->neighbors, f->n_len, s) == 0)
	{
		if (!add_darr(&f->neighbors, s))
			error_f("create_link add_darr malloc", 0);
		if (!add_darr(&s->neighbors, f))
			error_f("create_link add_darr malloc", 0);
		f->n_len++;
		s->n_len++;
	}
}

void		parse_links(t_lem *lem)
{
	int len;

	if (word_counter(lem->temps, '-') == 2)
	{
		lem->temps_d = ft_strsplit(lem->temps, '-');
		if (lem->temps_d == NULL)
			error_f("parse rooms ft_strsplit malloc", 0);
		else
			create_link(lem);
		to_free_dstr(lem->temps_d);
		lem->temps_d = NULL;
	}
	else
		error_f("invalid map: room", 0);
}

void		parse_rooms(t_lem *lem)
{
	int				i;
	t_node			*node;
	t_dynamicarr	*nodes;

	if (word_counter(lem->temps, ' ') == 3)
	{
		nodes = lem->graph->nodes;
		lem->temps_d = ft_strsplit(lem->temps, ' ');
		if (lem->temps_d == NULL)
			error_f("parse rooms ft_strsplit malloc", 0);
		node = new_node(ft_strdup(lem->temps_d[0]), lem->temps_d[1], lem->temps_d[2]);
		if (!add_darr(&nodes, node))
			error_f("parse rooms add_darr malloc", 0);
		node->i = nodes->len - 1;
		if (lem->next_start)
		{
			lem->graph->start = nodes->len - 1;
			node->s_or_end = 1;
			lem->next_start = 0;
		}
		else if (lem->next_end)
		{
			lem->graph->end = nodes->len - 1;
			node->s_or_end = 1;
			lem->next_end = 0;
		}
		lem->graph->len++;
		to_free_dstr(lem->temps_d);
		lem->temps_d = NULL;
		lem->graph->nodes = nodes;
	}
	else
		error_f("invalid map: room", 0);
}

void		parse(t_lem *lem)
{
	if (lem->temps[0] == '#')
		parse_sharp(lem);
	else if (ft_strchri(lem->temps, '-') != -1)
	{
		parse_links(lem);
		ft_printf("%s\n", lem->temps);

	}
	else
	{
		parse_rooms(lem);
		ft_printf("%s\n", lem->temps);
	}
}

void		reading(t_lem *lem)
{
	int		i;

	i = 0;
	lem->graph = malloc(sizeof(t_graph));
	if (lem->graph == NULL)
		error_f("reading malloc error", 0);
	lem->graph->nodes = NULL;
	lem->graph->len = 0;
	while (ft_get_next_line(0, &(lem->temps)))
	{
		if (ft_strlen(lem->temps) == 0)
			error_f("reading error", 0);
		if (lem->temps == NULL)
			error_f("reading gnl malloc", 0);
		if (i == 0)
			parse_nants(lem);
		else
			parse(lem);
		i++;
		free(lem->temps);
	}
}

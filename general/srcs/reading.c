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
	nodes = graph->nodes;
	while (i != graph->len)
	{
		if (!ft_strcmp(nodes[i]->name, name))
			return (nodes[i]);
		i++;
	}
	return (NULL);
}

int			in_neighbors(t_node **arr, int len, t_node *target)
{
	int	i;

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
	if (f->neighbors == NULL)
		if (!(f->neighbors = malloc(sizeof(t_node*) * 100))) //change
			error_f("create link malloc", 0);
	if (s->neighbors == NULL)
		if (!(s->neighbors = malloc(sizeof(t_node*) * 100))) //change
			error_f("create link malloc", 0);
	if (in_neighbors(f->neighbors, f->n_len, s) == 0)
	{
		f->neighbors[f->n_len] = s;
		s->neighbors[s->n_len] = f;
		f->n_len++;
		s->n_len++;
		f->neighbors[f->n_len] = NULL;
		s->neighbors[s->n_len] = NULL;
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
	int len;

	if (word_counter(lem->temps, ' ') == 3)
	{
		lem->temps_d = ft_strsplit(lem->temps, ' ');
		if (lem->temps_d == NULL)
			error_f("parse rooms ft_strsplit malloc", 0);
		if (lem->graph->nodes == NULL)
			lem->graph->nodes = malloc(sizeof(t_node*) * 100); // change
		len = lem->graph->len;
		lem->graph->nodes[len] = malloc(sizeof(t_node));
		if (lem->graph->nodes[len] == NULL)
			error_f("parse rooms node malloc", 0);
		lem->graph->nodes[len]->name = ft_strdup(lem->temps_d[0]);
		lem->graph->nodes[len]->x = ft_atoi(lem->temps_d[1]);
		lem->graph->nodes[len]->y = ft_atoi(lem->temps_d[2]);
		lem->graph->nodes[len]->n_len = 0;
		lem->graph->nodes[len]->neighbors = NULL;
		if (lem->next_start)
		{
			lem->graph->start = len;
			lem->next_start = 0;
		}
		else if (lem->next_end)
		{
			lem->graph->end = len;
			lem->next_end = 0;
		}
		lem->graph->len++;
		to_free_dstr(lem->temps_d);
		lem->temps_d = NULL;
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

#include "lem_in.h"

int		relax_edge(t_edge *edge, t_lem *lem)
{
	int		dist_v;
	int		dist_u;

//	dist_v = lem->graph->nodes->weights[edge->to->i];
//	dist_u = lem->graph->nodes->weights[edge->from->i];
	dist_v = lem->graph->nodes->weights[edge->to->i];
	dist_u = lem->graph->nodes->weights[edge->from->i];

	if (dist_u == FT_INT_MAX)
		return (FT_FALSE);
	if (dist_v > dist_u + edge->w)
	{
		lem->graph->nodes->weights[edge->to->i] = dist_u + edge->w;
		edge->to->prev = edge->from;
		return (FT_TRUE);
	}
	return (FT_FALSE);
}

void	zero_weight(t_lem *lem)
{
	t_list	*edges;
	int		i;

	i = 0;
	while (i != lem->graph->len)
	{
		if (i == lem->graph->start)
			lem->graph->nodes->weights[i] = 0;
		else
			lem->graph->nodes->weights[i] = FT_INT_MAX;
		i++;
	}
}

int		bellman_ford(t_lem *lem)
{
	int		i;
	int		r;
	t_list	*edges;

	i = 0;
	zero_weight(lem);
	while (i != lem->graph->len)
	{
		edges = (t_list*)lem->edges;
		r = FT_FALSE;
		while (edges)
		{
			r = relax_edge(edges->content, lem);
			edges = edges->next;
		}
		if (r == FT_FALSE)
			break;
		i++;
	}
	return (FT_TRUE);
}

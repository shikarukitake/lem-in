#include "lem_in.h"


void	solve(t_lem *lem)
{
	create_edge(lem);
	if (!bellman_ford(lem))
		error_f("There is no shortest PATH", 0);
	//ft_lstiter(lem->edges, &print_edges);

}
#include "lem_in.h"

void	free_nodes(t_node **arr, int free_neight)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]->name);
		if (free_neight)
			free_nodes((t_node**)arr[i]->neighbors, 0);
		free(arr[i]);
		i++;
	}
	free(arr);
}
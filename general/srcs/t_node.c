#include "lem_in.h"

void	free_nodes(t_node **arr, int free_neight)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]->name);
		if (free_neight)
		{
			free(arr[i]->neighbors->array);
			free(arr[i]->neighbors->weights);
			free(arr[i]->neighbors);
		}
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_node	*new_node(const char *name, const char *x, const char *y)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (new == NULL)
		error_f("new_node malloc", 0);
	new->name = name;
	if (!new->name)
	{
		free(new);
		error_f("new_node name malloc", 0);
	}
	new->x = ft_atoi(x);
	new->y = ft_atoi(y);
	new->n_len = 0;
	new->neighbors = NULL;
	return (new);
}
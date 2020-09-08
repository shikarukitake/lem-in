#include "lem_in.h"

void	free_node(t_node **node_to_del)
{
	t_node	*node;

	node = *node_to_del;
	if (node->name)
		free(node->name);
	if (node->neighbors)
	{
		free(node->neighbors->array);
		free(node->neighbors);
	}
	free(node);
	*node_to_del = NULL;
}

void	free_nodes(t_node **arr, int free_neight)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i]->copy)
			free_node(&(arr[i]->copy));
		free_node(&(arr[i]));
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
	new->in_way = 0;
	new->s_or_end = 0;
	new->prev = NULL;
	new->weight = FT_INT_MAX;
	new->is_copy = 0;
	new->copy = NULL;
	new->ant = 0;
	return (new);
}

t_node	*new_node_conv(const char *name, int x, int y)
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
	new->in_way = 0;
	new->s_or_end = 0;
	new->prev = NULL;
	new->weight = FT_INT_MAX;
	new->is_copy = 0;
	new->copy = NULL;
	new->ant = 0;
	return (new);
}
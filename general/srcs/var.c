#include "lem_in.h"

void	free_var(t_var	**var)//todo complete free
{
	t_way	*ways;
	t_way	*temp;

	ways = (*var)->ways;
	while (ways)
	{
		temp = ways;
		ft_lstdel(&(ways->path), &del_edge);
		ways = ways->next;
		free(temp);
	}
	free(*var);
	*var = NULL;
}

void	free_vars(t_var **vars)
{
	t_var	*var;
	t_var	*temp;

	var = *vars;
	while (var)
	{
		temp = var;
		var = var->next;
		free_var(&temp);
	}
}
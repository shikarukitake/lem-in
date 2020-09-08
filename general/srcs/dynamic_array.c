#include "lem_in.h"
# define START 50

void			cpy_array(t_node **dest, t_node **src, int freeornot, int len)
{
	int i;

	i = 0;
	if (dest)
		while (i != len)
		{
			dest[i] = src[i];
			i++;
		}
	if (freeornot)
		free(src);
}

void			cpy_intarray(int *dest, int *src, int freeornot, int len)
{
	int i;

	i = 0;
	if (dest)
		while (i != len)
		{
			dest[i] = src[i];
			i++;
		}
	if (freeornot)
		free(src);
}

int				init_darr(t_dynamicarr **arr)
{
	t_node	**swap;
	int		*swap_int;

	if (arr)
	{
		if (*arr)
		{
			swap = (*arr)->array;
			if (!((*arr)->array = malloc(sizeof(t_node*) *
					(((*arr)->len * 2) + 2))))
				return (0);
			cpy_array((*arr)->array, swap, 1, (*arr)->len);
			(*arr)->freespace = (*arr)->len;//check
		}
		else
		{
			if (!((*arr) = (t_dynamicarr*)malloc(sizeof(t_dynamicarr))))
				return (0);
			(*arr)->array = malloc(sizeof(t_node*) * START + 4);
			if (!((*arr)->array))
				return (0);
			(*arr)->len = 0;
			(*arr)->freespace = START;
		}
	}
	return (1);
}

int			add_darr(t_dynamicarr **arr, t_node *value)
{
	if (arr)
	{
		if (!(*arr))
			if (!init_darr(arr))
				return (0);
		if (!(*arr)->freespace)
			if (!init_darr(arr))
				return (0);
		(*arr)->array[(*arr)->len] = value;
		(*arr)->len += 1;
		(*arr)->array[(*arr)->len] = NULL;
		(*arr)->freespace -= 1;
	}
	return (1);
}

void			print_darr(t_dynamicarr *arr)
{
	int i;

	i = 0;
	while (i != arr->len)
		ft_printf("%s \n", arr->array[i++]->name);
	ft_printf("\n");
}

void			free_d_arr(t_dynamicarr **arr, int free_neight)
{
	if (*arr)
	{
		if ((*arr)->array)
			free_nodes((*arr)->array, free_neight);
		free((*arr));
		*arr = NULL;
	}
}
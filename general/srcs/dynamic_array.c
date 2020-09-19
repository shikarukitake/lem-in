/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:55:38 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/18 16:48:33 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#define START 50

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

int				init_darr(t_dynamicarr **arr)
{
	t_node	**swap;

	if (arr)
	{
		if (*arr)
		{
			swap = (*arr)->array;
			if (!((*arr)->array = malloc(sizeof(t_node*) *
					(((*arr)->len * 2) + 10))))
				return (0);
			cpy_array((*arr)->array, swap, 1, (*arr)->len);
			(*arr)->freespace = (*arr)->len;
		}
		else
		{
			if (!((*arr) = (t_dynamicarr*)malloc(sizeof(t_dynamicarr))))
				return (0);
			(*arr)->array = malloc(sizeof(t_node*) * (START + 10));
			if (!((*arr)->array))
				return (0);
			(*arr)->len = 0;
			(*arr)->freespace = START;
		}
	}
	return (1);
}

int				add_darr(t_dynamicarr **arr, t_node *value)
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
		(*arr)->array[(*arr)->len] = 0;
		(*arr)->freespace -= 1;
	}
	return (1);
}

void			free_d_arr(t_dynamicarr **arr)
{
	if (*arr)
	{
		if ((*arr)->array)
			free_nodes((*arr)->array);
		free((*arr));
		*arr = NULL;
	}
}

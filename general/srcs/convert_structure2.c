/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_structure2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 15:20:08 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/13 15:20:15 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

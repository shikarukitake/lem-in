/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:57:24 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:57:24 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_var(t_var **var)
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

t_var	*new_var(int n_ways)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		error_f("make solution from first var malloc error", 0);
	var->n_ways = n_ways;
	var->ways = NULL;
	var->next = NULL;
	var->steps = 0;
	return (var);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:57:07 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:57:07 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_solutions(t_lem *lem)
{
	if (lem->var->next == NULL)
		return (1);
	else
	{
		if (lem->var->steps < lem->var->next->steps)
			return (1);
		else
			return (0);
	}
	return (0);
}

void	choose_solution(t_lem *lem)
{
	t_var	*temp;

	if (lem->var->next)
		if (lem->var->steps > lem->var->next->steps)
		{
			temp = lem->var;
			lem->var = lem->var->next;
			free_var(&temp);
		}
}

void	make_solution_from_first(t_lem *lem)
{
	lem->var = new_var(1);
	copy_paths(lem);
}

void	make_solutuins_from_second(t_lem *lem)
{
	t_var	*temp_var;
	int		n_ways;

	temp_var = lem->var;
	n_ways = (int)ft_lstsize(lem->paths);
	if (temp_var->next)
	{
		free_var(&(lem->var->next));
		lem->var->next = NULL;
		lem->var = new_var(n_ways);
		lem->var->next = temp_var;
	}
	else
	{
		lem->var = new_var(n_ways);
		lem->var->next = temp_var;
	}
	copy_paths(lem);
}

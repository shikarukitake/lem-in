/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:55:06 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 14:55:06 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	distribute_ants(t_lem *lem, t_var *var, int max_len)
{
	int			n;
	int			s;
	t_way		*tmp;

	s = max_len - 1;
	n = lem->n_ants;
	tmp = var->ways;
	while (tmp && n > 0 && var->n_ways != 1)
	{
		if (tmp->on)
		{
			tmp->ants = (n < max_len - tmp->len) ? n : max_len - tmp->len;
			n -= tmp->ants;
		}
		tmp = tmp->next;
	}
	s += (n % var->n_ways == 0) ? n / var->n_ways : n / var->n_ways + 1;
	tmp = var->ways;
	while (n-- > 0)
	{
		++tmp->ants;
		tmp = (tmp->next) ? tmp->next : var->ways;
	}
	var->steps = s;
}

void	count_steps(t_lem *lem, t_var *var)
{
	int			max_len;
	int			valid_space;
	t_way		*tmp;

	valid_space = 0;
	tmp = var->ways;
	max_len = tmp->len;
	if (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->len > max_len)
			max_len = tmp->len;
		tmp = tmp->next;
	}
	tmp = var->ways;
	while (tmp)
	{
		valid_space += max_len - tmp->len;
		tmp = tmp->next;
	}
	distribute_ants(lem, var, max_len);
}

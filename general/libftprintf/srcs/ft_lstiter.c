/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 23:00:13 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/03 20:54:20 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (lst)
	{
		if (lst->next)
			ft_lstiter(lst->next, f);
		f(lst);
	}
}

void	ft_lstiter_ext(t_list *lst, void *stuff, void (*f)(t_list *, void *))
{
	if (lst)
	{
		if (lst->next)
			ft_lstiter_ext(lst->next, stuff, f);
		f(lst, stuff);
	}
}

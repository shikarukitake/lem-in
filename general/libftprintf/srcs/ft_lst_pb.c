/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 19:41:22 by sdagger           #+#    #+#             */
/*   Updated: 2020/08/03 17:54:24 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lst_pb(t_list **begin_list,
		void const *content, size_t content_size)
{
	t_list *temporary;

	if (begin_list && *begin_list)
	{
		temporary = *begin_list;
		while (temporary->next)
			temporary = temporary->next;
		temporary->next = ft_lstnew(content, content_size);
		if (!(temporary->next))
			return (0);
	}
	else
	{
		*begin_list = ft_lstnew(content, content_size);
		if (!(*begin_list))
			return (0);
	}
	return (1);
}

int		ft_lst_pb_copy(t_list **begin_list,
					void const *content, size_t content_size)
{
	t_list *temporary;

	if (begin_list && *begin_list)
	{
		temporary = *begin_list;
		while (temporary->next)
			temporary = temporary->next;
		temporary->next = ft_lstnew_copy(content, content_size);
		if (!(temporary->next))
			return (0);
	}
	else
	{
		*begin_list = ft_lstnew_copy(content, content_size);
		if (!(*begin_list))
			return (0);
	}
	return (1);
}

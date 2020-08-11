/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_w.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:54:34 by sdagger           #+#    #+#             */
/*   Updated: 2020/08/06 18:54:36 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_fuldel(char ***str, size_t len)
{
	if (str)
	{
		while (len)
		{
			free(*str[len]);
			len--;
		}
		free(*str);
	}
}

static int	check_tab(char c, char q)
{
	return (c == q);
}

int			word_counter(char const *str, char c)
{
	size_t	i;
	int		q;

	i = 0;
	q = 0;
	if (!str)
		return (0);
	while (i < ft_strlen(str))
	{
		if (!check_tab(str[i], c) &&
				(i == ft_strlen(str) - 1 || check_tab(str[i + 1], c)))
		{
			q++;
		}
		i++;
	}
	return (q);
}

void		to_free_dstr(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i])
			free(s[i]);
		i++;
	}
	free(s);
}

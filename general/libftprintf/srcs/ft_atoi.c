/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 19:49:40 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/12 22:28:06 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			check_tab(char c)
{
	return (c == '\n' || c == '\t' || c == ' '
			|| c == '\v' || c == '\f' || c == '\r');
}

static long int		make_int(const char *str, long long q, int i, int neg)
{
	while (str[i] >= '0' && (str[i] <= '9'))
	{
		q = q * 10 + (str[i] - '0');
		i++;
	}
	if (i >= 19)
		return (neg == -1 ? 0 : -1);
	if (q > 9223372036854775807)
		return (neg == -1 ? 0 : -1);
	else
		return (q * neg);
	return (q);
}

int					ft_atoi(const char *str)
{
	long long	q;
	int			i;
	int			neg;

	q = 0;
	i = 0;
	while (check_tab(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		neg = str[i] == '-' ? -1 : 1;
		i++;
		q = make_int(str, q, i, neg);
	}
	else
		q = make_int(str, q, i, 1);
	return (q);
}

static long			make_int_l(const char *str, long long q, int i, int neg)
{
	int	j;

	j = 0;
	while (str[i] >= '0' && (str[i] <= '9'))
	{
		q = q * 10 + (str[i] - '0');
		i++;
		j++;
	}
	if (j >= 14 || q > FT_INT_MAX || q < FT_INT_MIN)
		return (FT_INT_MIN - 20);
	else
		return (q * neg);
	return (q);
}

long				ft_atoi_l(const char *str)
{
	long long	q;
	int			i;
	int			neg;

	q = 0;
	i = 0;
	while (check_tab(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		neg = str[i] == '-' ? -1 : 1;
		i++;
		q = make_int_l(str, q, i, neg);
	}
	else
		q = make_int_l(str, q, i, 1);
	return (q);
}

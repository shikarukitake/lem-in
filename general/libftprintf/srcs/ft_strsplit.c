/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 18:04:46 by sdagger           #+#    #+#             */
/*   Updated: 2020/08/05 22:12:16 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(const char *s, char c)
{
	size_t	i;
	size_t	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != 0 && s[i] != c)
				i++;
			word++;
		}
		if (s[i] == 0)
			break ;
		i++;
	}
	return (word);
}

static size_t	ft_lenstrm(const char *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char		*ft_onestr(const char *s, char c)
{
	char	*ps;
	size_t	len;
	size_t	i;

	len = ft_lenstrm(s, c);
	i = 0;
	if (!(ps = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (s[i] && s[i] != c)
	{
		ps[i] = s[i];
		i++;
	}
	ps[i] = 0;
	return (ps);
}

static char		**ft_fullstr(char const *s, char c)
{
	size_t	j;
	size_t	count_w;
	char	**fsplit;

	j = 0;
	count_w = ft_countword(s, c);
	if (!(fsplit = (char**)malloc(sizeof(char*) * (count_w + 1))))
		return (NULL);
	if (count_w != 0)
		while (j < count_w)
		{
			while (*s && *s == c)
				s++;
			if (!(fsplit[j] = ft_onestr(s, c)))
			{
				ft_fuldel(&fsplit, j);
				return (NULL);
			}
			while (*s && *s != c)
				s++;
			j++;
		}
	fsplit[j] = NULL;
	return (fsplit);
}

char			**ft_strsplit(char const *s, char c)
{
	char **split;

	split = NULL;
	if (s != NULL)
		split = ft_fullstr(s, c);
	return (split);
}

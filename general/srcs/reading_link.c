/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_link.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrynn <sbrynn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:50:56 by sbrynn            #+#    #+#             */
/*   Updated: 2020/09/13 14:35:18 by sbrynn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	read_name(t_read *reader, char **name, int num)
{
	int		i;
	char	c;

	i = reader->idx;
	c = num == 1 ? '-' : '\0';
	while (reader->line[i] != c)
	{
		if (num == 1 && !reader->line[i])
			return (1);
		i++;
	}
	*name = ft_strsub(reader->line, reader->idx, i);
	reader->idx = i + 1;
	return (0);
}

int	add_name(t_read *reader, char *tmp, t_cnct *link, int num)
{
	t_rooms	*curr;
	int		ok;

	ok = 1;
	curr = reader->rooms;
	while (curr)
	{
		if (!ft_strcmp(curr->room, tmp))
		{
			ok = 0;
			if (num == 1)
				link->from = curr;
			else
				link->to = curr;
		}
		curr = curr->next;
	}
	return (ok);
}

int	add_link_list(t_read *reader, t_cnct *link)
{
	t_cnct *curr;

	curr = reader->conect;
	while (curr && curr->next)
		curr = curr->next;
	if (curr)
		curr->next = link;
	else
		reader->conect = link;
	return (0);
}

int	read_link(t_read *reader)
{
	t_cnct	*link;
	char	*tmp;

	tmp = NULL;
	link = init_cnct();
	if (read_name(reader, &tmp, 1))
		return (1);
	if (add_name(reader, tmp, link, 1))
		return (freed(&tmp));
	free(tmp);
	if (read_name(reader, &tmp, 2))
		return (1);
	if (add_name(reader, tmp, link, 2))
		return (freed(&tmp));
	free(tmp);
	if (ft_strcmp((link->from)->room, (link->to)->room))
	{
		reader->connect_cnt++;
		add_link_list(reader, link);
	}
	else
		free_cnct(link);
	return (0);
}

int	links(t_read *reader)
{
	add_start_end(reader);
	if (!ft_strchr(reader->line, '-') || read_link(reader))
		return (1);
	while (gnl(reader) > 0)
	{
		if (ft_strncmp(reader->line, "#", 1))
		{
			if (!ft_strchr(reader->line, '-') || read_link(reader))
				return (1);
		}
		else if (!ft_strcmp(reader->line, "##end") ||\
		!ft_strcmp(reader->line, "##start"))
			return (1);
	}
	return (0);
}

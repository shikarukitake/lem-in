/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrynn <sbrynn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 18:14:01 by sbrynn            #+#    #+#             */
/*   Updated: 2020/09/18 14:48:41 by sbrynn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_read(t_read *head)
{
	free_rooms(head->rooms);
	free_cnct(head->conect);
	if (head->start_name)
		free(head->start_name);
	if (head->end_name)
		free(head->end_name);
	if (head->global_line)
		free(head->global_line);
	free(head);
}

void	skip_comment(t_read *reader)
{
	while (gnl(reader) > 0)
		if (ft_strncmp(reader->line, "#", 1)\
		|| !ft_strncmp(reader->line + reader->idx, "##", 2))
			break ;
}

int		rooms(t_read *reader)
{
	while (gnl(reader))
	{
		if (ft_strcmp(reader->line + reader->idx, "##start") == 0)
		{
			if (reader->start_name)
				return (1);
			skip_comment(reader);
			if (read_room(reader, 0))
				return (1);
		}
		else if (ft_strcmp(reader->line + reader->idx, "##end") == 0)
		{
			if (reader->end_name)
				return (1);
			skip_comment(reader);
			if (read_room(reader, 1))
				return (1);
		}
		else if (ft_strncmp(reader->line, "#", 1))
			if (read_room(reader, 2))
				return (!reader->start_name || !reader->end_name ||\
				links(reader) ? 1 : 0);
	}
	return (0);
}

int		first_line(t_read *reader)
{
	while (gnl(reader) > 0)
	{
		if (ft_strncmp(reader->line, "#", 1))
		{
			reader->ant_cnt = ft_atoi_l(reader->line);
			if (reader->ant_cnt < 1)
				return (1);
			return (check_after(reader->line, 0));
		}
		else if (!ft_strcmp(reader->line, "##end") ||\
		!ft_strcmp(reader->line, "##start"))
			return (1);
	}
	return (1);
}

int		reading(t_read *reader)
{
	if (first_line(reader) || rooms(reader) || !(reader->conect))
		return (1);
	return (0);
}

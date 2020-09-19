/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrynn <sbrynn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:46:20 by sbrynn            #+#    #+#             */
/*   Updated: 2020/09/13 17:06:40 by sbrynn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	read_room_content(t_read *reader, t_rooms *room)
{
	if (base_check_room(reader))
		return (1);
	if (skip_it(reader, 0))
		return (1);
	if (!(room->room = (char*)malloc(sizeof(char) * (reader->idx + 1))))
		return (1);
	ft_strncpy(room->room, reader->line, reader->idx);
	room->room[reader->idx] = '\0';
	room->x = ft_atoi(reader->line + reader->idx);
	if (room->x == 0 && reader->line[reader->idx + 1] != '0')
		return (1);
	if (*(reader->line + reader->idx + 1))
		reader->idx++;
	if (skip_it(reader, 1))
		return (1);
	room->y = ft_atoi(reader->line + reader->idx);
	if (room->y == 0 && reader->line[reader->idx + 1] != '0')
		return (1);
	return (check_after(reader->line, reader->idx + 1));
}

int	check_room(t_read *reader, t_rooms *room)
{
	t_rooms *curr;

	curr = reader->rooms;
	if (reader->start[0] == room->x && reader->start[1] == room->y\
	&& reader->start_name)
		return (1);
	if (reader->end[0] == room->x && reader->end[1] == room->y\
	&& reader->end_name)
		return (1);
	if ((reader->start_name && !ft_strcmp(reader->start_name, room->room)) ||\
	(reader->end_name && !ft_strcmp(reader->end_name, room->room)))
		return (1);
	while (curr)
	{
		if (curr->x == room->x && curr->y == room->y)
			return (1);
		if (!ft_strcmp(curr->room, room->room))
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	add_room_help(t_read *reader, t_rooms *room, int flag)
{
	if (flag == 0)
	{
		reader->start_name = ft_strdup(room->room);
		reader->start[0] = room->x;
		reader->start[1] = room->y;
		free_rooms(room);
	}
	else if (flag == 1)
	{
		reader->end_name = ft_strdup(room->room);
		reader->end[0] = room->x;
		reader->end[1] = room->y;
		free_rooms(room);
	}
	return (0);
}

int	add_room(t_read *reader, t_rooms *room, int flag)
{
	t_rooms *curr;

	curr = reader->rooms;
	if (flag <= 1)
	{
		add_room_help(reader, room, flag);
	}
	else
	{
		while (curr && curr->next)
			curr = curr->next;
		if (curr)
			curr->next = room;
		else
			reader->rooms = room;
	}
	reader->room_cnt++;
	return (0);
}

int	read_room(t_read *reader, int flag)
{
	t_rooms *room;

	room = init_room();
	if (read_room_content(reader, room) ||\
	check_room(reader, room) ||\
	add_room(reader, room, flag))
	{
		free_rooms(room);
		return (1);
	}
	return (0);
}

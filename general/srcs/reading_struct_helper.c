/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_struct_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrynn <sbrynn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:42:44 by sbrynn            #+#    #+#             */
/*   Updated: 2020/09/12 22:23:52 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms		*init_room(void)
{
	t_rooms *head;

	if (!(head = (t_rooms*)malloc(sizeof(t_rooms))))
		return (NULL);
	head->room = NULL;
	head->x = -1;
	head->y = -1;
	head->cnt = 1;
	head->next = NULL;
	return (head);
}

void		free_rooms(t_rooms *head)
{
	t_rooms *curr;

	while (head)
	{
		curr = head->next;
		free(head->room);
		free(head);
		head = curr;
	}
}

t_cnct		*init_cnct(void)
{
	t_cnct *head;

	if (!(head = (t_cnct*)malloc(sizeof(t_cnct))))
		return (NULL);
	head->from = NULL;
	head->to = NULL;
	head->next = NULL;
	return (head);
}

void		free_cnct(t_cnct *head)
{
	t_cnct *curr;

	while (head)
	{
		curr = head->next;
		free(head);
		head = curr;
	}
	free(head);
}

t_read		*init_read(void)
{
	t_read *head;

	if (!(head = (t_read*)malloc(sizeof(t_read))))
		return (NULL);
	head->ant_cnt = -1;
	head->start[0] = -1;
	head->start[1] = -1;
	head->start_name = NULL;
	head->end[0] = -1;
	head->end[1] = -1;
	head->end_name = NULL;
	head->connect_cnt = 0;
	head->room_cnt = 0;
	head->rooms = NULL;
	head->conect = NULL;
	head->line = NULL;
	head->global_line = NULL;
	head->idx = 0;
	return (head);
}

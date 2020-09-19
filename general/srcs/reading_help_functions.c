/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_help_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrynn <sbrynn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:50:51 by sbrynn            #+#    #+#             */
/*   Updated: 2020/09/13 14:34:54 by sbrynn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	gnl(t_read *reader)
{
	char *tmp_1;
	char *tmp_2;

	tmp_1 = NULL;
	tmp_2 = NULL;
	if (reader->line)
	{
		tmp_1 = ft_strjoin(reader->line, "\n");
		if (reader->global_line)
		{
			tmp_2 = ft_strjoin(reader->global_line, tmp_1);
			free(tmp_1);
			free(reader->global_line);
			reader->global_line = tmp_2;
		}
		else
			reader->global_line = tmp_1;
		if (reader->line)
			free(reader->line);
	}
	reader->idx = 0;
	return (ft_get_next_line(0, &(reader->line)));
}

int	base_check_room(t_read *reader)
{
	int i;

	i = 0;
	if (reader->line[reader->idx] == 'L')
		return (1);
	while (reader->line[i] && reader->line[i] != ' ')
	{
		if (reader->line[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	freed(char **line)
{
	free(*line);
	*line = NULL;
	return (1);
}

int	add_start_end(t_read *reader)
{
	t_rooms *curr;
	t_rooms	*start;
	t_rooms	*end;

	curr = reader->rooms;
	start = init_room();
	end = init_room();
	start->next = end;
	start->room = ft_strdup(reader->start_name);
	start->x = reader->start[0];
	start->y = reader->start[1];
	end->room = ft_strdup(reader->end_name);
	end->x = reader->end[0];
	end->y = reader->end[1];
	while (curr && curr->next)
		curr = curr->next;
	if (curr)
		curr->next = start;
	else
		reader->rooms = start;
	return (0);
}

int	skip_it(t_read *reader, int flag)
{
	if (reader->line[reader->idx] == '-')
		reader->idx++;
	while (reader->line[reader->idx] != ' ')
	{
		if (!reader->line[reader->idx] ||\
		(flag && (reader->line[reader->idx] > '9'\
		|| reader->line[reader->idx] < '0')))
			return (1);
		reader->idx++;
	}
	return (0);
}

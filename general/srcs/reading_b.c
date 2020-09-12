#include "lem_in.h"

int gnl(t_read *reader)
{
	char *tmp_1;
	char *tmp_2;

	tmp_1 = NULL;
	tmp_2 = NULL;
	if (reader->line)
	{
		tmp_1 = ft_strjoin(reader->line, ft_strdup("\n"));
		if (reader->global_line)
		{
			tmp_2 = ft_strjoin(reader->global_line, tmp_1);
			free(tmp_1);
			reader->global_line = tmp_2;
		}
		else
			reader->global_line = tmp_1;
		if (reader->line)
			free(reader->line);

	}
	reader->idx = 0;
	return (ft_get_next_line(0,&(reader->line)));
}

int	base_check_room(t_read *reader)
{
	if (reader->line[reader->idx] == 'L')
		return (1);
	if (ft_strchr(reader->line, '-'))
		return (1);
	return (0);
}

int	read_name(t_read *reader, char **name, int num)
{
	int	i;
	char c;

	i = reader->idx;
	c = num == 1 ? '-' : '\0';
	while(reader->line[i] != c)
	{
		if (num == 1 && !reader->line[i])
			return (1);
		i++;
	}
	*name  = ft_strsub(reader->line, reader->idx, i);
	reader->idx = i + 1;
	return (0);
}

int	add_name(t_read *reader, char *tmp, t_cnct *link, int num)
{
	t_rooms	*curr;
	int		ok;

	ok = 1;
	curr = reader->rooms;
	// if (!ft_strcmp(tmp, reader->start_name))
	// {

	// } не понятно что делать со старт и энд
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
	return(ok);
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

int read_link(t_read *reader)
{
	t_cnct *link;
	char	*tmp;

	tmp = NULL;
	link = init_cnct();
	if (read_name(reader,&tmp, 1))
		return (1);
	if (add_name(reader, tmp, link, 1))
		return (1);
	if (read_name(reader,&tmp, 2))
		return (1);
	if (add_name(reader, tmp, link, 2))
		return (1);
	if (ft_strcmp((link->from)->room, (link->to)->room))
	{
		reader->connect_cnt++;
		add_link_list(reader, link);
	}
	else
		free_cnct(link);
	return (0);
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
	start->room = reader->start_name;
	start->x = reader->start[0];
	start->y = reader->start[1];
	end->room = reader->end_name;
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

int	links(t_read *reader)
{
	add_start_end(reader);
	if (!ft_strchr(reader->line, '-') || read_link(reader))
		return (1);
	while (gnl(reader) > 0)
	{
		// ft_printf("%s\n",reader->line);
		if (!ft_strchr(reader->line, '-') || read_link(reader))
		{
			// ft_printf("kek\n");
			return (1);
		}
	}
	return (0);
}


int	read_room_content(t_read *reader, t_rooms *room)
{
	int		i;

	i = 0;
	if (base_check_room(reader))
		return (1);
	while (reader->line[reader->idx + i] != ' ')
	{
		if (!reader->line[reader->idx + i])
			return (1);
		i++;
	}
	if(!(room->room = (char*)malloc(sizeof(char)*(i+1))))
		return (1);
	ft_strncpy(room->room, reader->line+reader->idx, i);
	room->room[i] = '\0';
	reader->idx += i;
	room->x = ft_atoi(reader->line + reader->idx);
	if (room->x == 0 && reader->line[reader->idx + 1] != '0')
		return (1);
	if (*(reader->line + reader->idx + 1))
		reader->idx++;
	while (reader->line[reader->idx] != ' ')//probeli nepravilno
	{
		if (!reader->line[reader->idx])
			return (1);
		reader->idx++;
	}

	room->y = ft_atoi(reader->line + reader->idx);
	if (room->y == 0 && reader->line[reader->idx + 1] != '0')
		return (1);
	return (0);
}

int	check_room(t_read *reader, t_rooms *room)
{
	t_rooms *curr;

	curr = reader->rooms;
	if (reader->start[0] == room->x && reader->start[1] == room->y)
		return (1);
	if (reader->end[0] == room->x && reader->end[1] == room->y)
		return (1);
	if ((reader->start_name && !ft_strcmp(reader->start_name, room->room)) ||\
	(reader->end_name && !ft_strcmp(reader->end_name, room->room)))//lomaetsya
		return (1);
	while (curr && curr->next)
	{
		if (curr->x == room->x && curr->y == room->y)
			return (1);
		if (!ft_strcmp(curr->room, room->room))
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	add_room(t_read *reader, t_rooms *room, int flag)
{
	t_rooms *curr;

	curr = reader->rooms;
	if (flag == 0)
	{
		reader->start_name = room->room;
		reader->start[0] = room->x;
		reader->start[1] = room->y;
		free(room);
	}
	else if (flag == 1)
	{
		reader->end_name = room->room;
		reader->end[0] = room->x;
		reader->end[1] = room->y;
		free(room);
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
	t_rooms  *room;

	// if (base_check_room(reader))
	// 	return (1);
	room = init_room();
	if (read_room_content(reader, room) ||\
	check_room(reader, room) ||\
	add_room(reader, room, flag))
		return (1);
	// add_enter(reader);
	return (0);
}

int	first_line(t_read *reader)
{
	if (gnl(reader) < 0)
		return (1);
	reader->ant_cnt = ft_atoi(reader->line);
	if (reader->ant_cnt < 1)
		return (1);
	// while(reader->line[reader->idx])
	// 	reader->idx++;
	// add_enter(reader);
	return(0);
}

int	rooms(t_read *reader)
{
	while(gnl(reader))
	{
		if (ft_strcmp(reader->line + reader->idx, "##start") == 0) //##start
		{
			if (reader->start_name)
				return (1);
			// add_enter(reader);
			// reader->idx += 7;
			gnl(reader);
			if (read_room(reader, 0))
				return(1);
		}
		else if (ft_strcmp(reader->line + reader->idx, "##end") == 0) //##end
		{
			if (reader->end_name)
				return (1);
			// add_enter(reader);
			// reader->idx += 7;
			gnl(reader);
			if (read_room(reader, 1))
				return(1);
		}
		else if(ft_strncmp(reader->line, "#", 1))
		{
			//huinya po chteniu komnat uslovie v linki
			if(read_room(reader, 2))
			{
				if (reader->start_name && reader->end_name && links(reader))//reader->start_name && reader->end_name &&
					return (1);
				else
					return (0);
			}
		}

	}
	return(0);
}


// int	links(t_read *reader)
// {

// }

int	reading(t_read *reader)
{
	// reader = init_read();
	if (first_line(reader) || rooms(reader)) //|| links(reader))
		return(1);
	return(0);
}
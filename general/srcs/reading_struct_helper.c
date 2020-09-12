#include "lem_in.h"

t_rooms *init_room()
{
	t_rooms *head;

	if (!(head = (t_rooms*)malloc(sizeof(t_rooms))))
		return NULL;
	head->room = NULL;
	head->x = -1;
	head->y = -1;
	head->cnt = 1;
	head->next = NULL;

	return head;
}

// t_rooms	*add_room(t_rooms *head)
// {
// 	t_rooms *curr;

// 	curr = head;
// 	while(curr && curr->next)
// 	{
// 		curr = curr->next;
// 	}
// 	curr->next = init_room();
// 	if (curr->cnt)
// 		(curr->next)->cnt = 1 + curr->cnt;
// 	return curr->next;
// }

void	free_rooms(t_rooms *head)
{
	t_rooms *curr;
	while(head && head->next)
	{
		curr = head->next;
		free(head->room);
		free(head);
		head = curr;
	}
	free(head);
}

t_cnct *init_cnct()
{
	t_cnct *head;

	if (!(head = (t_cnct*)malloc(sizeof(t_cnct))))
		return NULL;
	head->from = NULL;
	head->to = NULL;
	head->next = NULL;

	return head;
}

t_cnct	*add_cnct(t_cnct *head)
{
	t_cnct *curr;

	curr = head;
	while(curr && curr->next)
	{
		curr = curr->next;
	}
	curr->next = init_cnct();
	return curr->next;
}

void	free_cnct(t_cnct *head)
{
	t_cnct *curr;
	while(head && head->next)
	{
		curr = head->next;
		free(head);
		head = curr;
	}
	free(head);
}

t_read *init_read()
{
	t_read *head;

	if (!(head = (t_read*)malloc(sizeof(t_read))))
		return (NULL);
	head->ant_cnt=-1;
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

void	free_read(t_read *head)
{
	free_rooms(head->rooms);
	free_cnct(head->conect);
	if (head->line)
		free(head->line);
	if (head->global_line)
		free(head->global_line);
	free(head);
}
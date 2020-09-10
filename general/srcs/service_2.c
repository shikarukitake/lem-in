#include "lem_in.h"

void	reverse_list(t_list **head_ref)
{
	t_list	*prev = NULL;
	t_list	*current = *head_ref;
	t_list	*next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head_ref = prev;
}
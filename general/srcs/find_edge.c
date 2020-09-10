#include "lem_in.h"

t_edge	*find_edge_part(t_edge *edge, int (*f)(t_edge *, t_edge *),
						t_list *temp, t_list *prev)
{
	t_edge	*finded;

	finded = temp->content;
	while (temp)
	{
		finded = temp->content;
		if (f(finded, edge))
			break;
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (NULL);
	prev->next = temp->next;
	free(temp);
	return (finded);
}

t_edge	*find_edge(t_list **paths, t_edge *edge, int (*f)(t_edge*, t_edge*))
{
	t_edge	*finded;
	t_list	*temp;
	t_list	*prev;

	temp = *paths;
	prev = *paths;
	finded = NULL;
	if (temp != NULL)
	{
		finded = temp->content;
		if (f(finded, edge))
		{
			*paths = temp->next;
			free(temp);
			return (finded);
		}
		return (find_edge_part(edge, f, temp, prev));
	}
	return (NULL);
}
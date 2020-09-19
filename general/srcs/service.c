/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:56:47 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/18 16:46:30 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_lem	*init_lem(void)
{
	t_lem	*lem;

	lem = malloc(sizeof(t_lem));
	if (lem == NULL)
		ft_error_t("init lem malloc error");
	else
	{
		lem->graph = NULL;
		lem->temps = NULL;
		lem->temps_d = NULL;
		lem->next_start = 0;
		lem->next_end = 0;
		lem->edges = NULL;
		lem->new_paths = NULL;
		lem->paths = NULL;
		lem->var = NULL;
		lem->dflag = 0;
		lem->origin_edges = NULL;
		return (lem);
	}
	return (NULL);
}

static void		free_graph(t_graph **graph)
{
	int	i;

	i = 0;
	if ((*graph))
	{
		if ((*graph)->nodes)
			free_d_arr(&((*graph)->nodes));
		free((*graph));
		(*graph) = NULL;
	}
}

void			free_paths(void *path_void, size_t size)
{
	size += 0;
	ft_lstdel((t_list **)&path_void, &del_edge);
}

void			free_lem(t_lem *lem)
{
	if (lem->edges)
		ft_lstdel(&(lem->edges), &del_edge);
	if (lem->origin_edges)
		ft_lstdel(&(lem->origin_edges), &del_edge);
	free_graph(&(lem->graph));
	if (lem->paths)
		ft_lstdel(&(lem->paths), &free_paths);
	free_vars(&(lem->var));
	free(lem);
}

t_lem			*error_f(char *text, int init)
{
	static t_lem	*lem;

	if (init)
	{
		lem = init_lem();
		return (lem);
	}
	free_lem(lem);
	ft_error_t(text);
	return (NULL);
}

#include "lem_in.h"

static t_lem	*init_lem()
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
		return (lem);
	}
}

static void		free_graph(t_graph **graph)
{
	int	i;

	i = 0;
	if ((*graph))
	{
		if ((*graph)->nodes)
			free_d_arr(&((*graph)->nodes), 1);
		free((*graph));
		(*graph) = NULL;
	}
}

void			del_l(void *content, size_t size)
{
	t_list	*list;

	list = (t_list*)content;
	ft_lstdel(&list, NULL);
}

void			free_path(void *path_void, size_t size)
{

}

void			free_paths(void *path_void, size_t size)
{
	ft_lstdel(&path_void, &del_edge);
}

void			free_lem(t_lem *lem)
{
	if (lem->edges)
		ft_lstdel(&(lem->edges), &del_edge);
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
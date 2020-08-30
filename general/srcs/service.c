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

void			free_lem(t_lem *lem)
{
	free_graph(&(lem->graph));
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
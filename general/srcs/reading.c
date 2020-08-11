#include "lem_in.h"

void		parse_nants(t_lem *lem)
{
	long	n_ants;

	n_ants = ft_atoi_l(lem->temps);
	if (n_ants > FT_INT_MAX || n_ants < FT_INT_MIN)
		error_f("parse_nants n_ants overflow", 0);
}

void		parse_sharp(t_lem *lem)
{

}

void		parse_links(t_lem *lem)
{

}

void		parse_rooms(t_lem *lem)
{
	if (word_counter(lem->temps, ' ') == 3)
	{

	}
	else
		error_f("invalid map: room", 0);
}

void		parse(t_lem *lem)
{
	if (lem->temps[0] == '#')
		parse_sharp(lem);
	else if (ft_strchri(lem->temps, '-'))
		parse_links(lem);
	else
		parse_rooms(lem);
}

void		reading(t_lem *lem)
{
	int		i;

	i = 0;
	lem->graph = malloc(sizeof(t_graph));
	if (lem->graph == NULL)
		error_f("reading malloc error", 0);
	while (ft_get_next_line(0, &(lem->temps)))
	{
		if (i == 0)
			parse_nants(lem);
		else
			parse(lem);
		i++;
	}
}

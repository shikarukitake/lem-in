//
// Created by Sole Dagger on 8/11/20.
//

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

/*
** lem structures
*/

typedef struct	s_node
{
	char			*name;
	struct t_node	**neighbors;
	int				x;
	int				y;
}				t_node;

typedef struct	s_grapg
{
	int		len;
	t_node	**nodes;
}				t_graph;

typedef struct	s_lem
{
	t_graph	*graph;
	char	*temps;
	char	**temps_d;
	int		n_ants;
	int		next_start;
	int		next_end;
}				t_lem;

/*
** service
*/

t_lem	*error_f(char *text, int init);
void	free_lem(t_lem *lem);

/*
** reading
*/

void		reading(t_lem *lem);

#endif

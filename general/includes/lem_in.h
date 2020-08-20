//
// Created by Sole Dagger on 8/11/20.
//

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct s_dynamicarr t_dynamicarr;

/*
** lem structures
*/

typedef struct	s_node
{
	char			*name;
	t_dynamicarr	*neighbors;
	int				x;
	int				y;
	int				n_len;
}				t_node;

typedef struct	s_grapg
{
	int				len;
	t_dynamicarr	*nodes;
	int				start;
	int				end;
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
** Dynamic Array
*/

typedef struct	s_dynamicarr
{
	t_node	**array;
	int		len;
	int		freespace;
}				t_dynamicarr;

int				init_darr(t_dynamicarr **arr);
void			cpy_array(t_node **dest, t_node **src, int freeornot, int len);
int				add_darr(t_dynamicarr **arr, t_node *value);
void			print_darr(t_dynamicarr *arr);
void			free_d_arr(t_dynamicarr **arr);

/*
** nodes
*/

void			free_nodes(t_node **arr, int free_neight);
t_node			*new_node(const char *name, const char *x, const char *y);

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

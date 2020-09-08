//
// Created by Sole Dagger on 8/11/20.
//

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <time.h> //todo DELETE
# include <stdio.h> //todo DELETE

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
	int				in_way;
	int				i;
	int				ant;
	int				weight;
	struct s_node	*prev;
	struct s_node	*copy;
	int				s_or_end;
	int				is_copy;
}				t_node;

typedef struct	s_grapg
{
	int				len;
	t_dynamicarr	*nodes;//array add_darr(&nodes, value)
	int				start;
	int				end;
}				t_graph;

typedef struct	s_edge
{
	t_node			*from;
	t_node			*to;
	int				w;
}				t_edge;

typedef struct		s_way
{
	int				len;
	int				ants;
	int				on;
	struct s_way	*next;
	t_list 			*path;
}					t_way;

typedef struct	s_var
{

	int				n_ways;
	int				steps;
	struct s_var	*next;
	t_way			*ways;
}				t_var;

typedef struct	s_lem
{
	t_graph	*graph;
	char	*temps;
	char	**temps_d;
	int		n_ants;
	int		next_start;
	int		next_end;
	t_list	*edges;
	t_list	*origin_edges;
	t_list	*new_paths;
	t_list	*paths;
	t_var	*var;
	int		i;
	short	dflag;
}				t_lem;


/*
** Extended list
*/

void				reverse_list(t_list **head_ref);

/*
** Dynamic Array
*/

typedef struct		s_dynamicarr
{
	t_node	**array;
	int		*weights;
	int		len;
	int		freespace;
}					t_dynamicarr;

int					init_darr(t_dynamicarr **arr);
void				cpy_array(t_node **dest, t_node **src, int freeornot, int len);
int					add_darr(t_dynamicarr **arr, t_node *value);
void				print_darr(t_dynamicarr *arr);
void				free_d_arr(t_dynamicarr **arr, int free_neight);

/*
** nodes
*/

void				free_nodes(t_node **arr, int free_neight);
t_node				*new_node(const char *name, const char *x, const char *y);
void				free_node(t_node **node_to_del);
t_node				*new_node_conv(const char *name, int x, int y);
t_node				*find_node(const char *name, t_graph *graph);

/*
** service
*/

t_lem				*error_f(char *text, int init);
void				free_lem(t_lem *lem);

/*
** reading
*/

void				reading(t_lem *lem);

/*
** solving
*/

void				solve(t_lem *lem);
int					bellman_ford(t_lem *lem);

/*
** edges
*/

t_edge				*new_edge(t_node *from, t_node *to);
int					create_edge(t_lem	*lem);
void				del_edge(void *edge_addr, size_t size);
void				print_edges(t_list *elem);

/*
** run ants
*/

void				run_ants(t_lem *lem);

/*
** var structure
*/

void				free_var(t_var	**var);
void				free_vars(t_var **vars);

/*
** debug
*/

t_edge	*find_edge_without_delete(t_lem *lem, t_node *from, t_node *to);
t_node	*find_node_without_delete(t_lem *lem, const char *name);

/*
** reading from Bogdan
*/

typedef struct 		s_rooms
{
	char			*room;
	int				x;
	int				y;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_cnct
{
	t_rooms			*from;
	t_rooms			*to;
	struct s_cnct	*next;
}					t_cnct;


typedef struct 		s_read
{
	int				ant_cnt;
	char			*start_name;
	char			*end_name;
	int				start[2];
	int				end[2];
	int				connect_cnt;
	int				room_cnt;
	t_rooms			*rooms;
	t_cnct			*conect;
	int				idx;
	char			*line;
}					t_read;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrynn <sbrynn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:54:52 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/18 17:02:10 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# define COLOR_RED		"\x1b[31m"
# define COLOR_GREEN	"\x1b[32m"
# define COLOR_YELLOW	"\x1b[33m"
# define COLOR_PINK		"\x1b[1;35m"
# define COLOR_BLUE		"\x1b[34m"
# define COLOR_MAGENTA	"\x1b[35m"
# define COLOR_CYAN		"\x1b[36m"
# define COLOR_RESET	"\x1b[0m"

typedef struct		s_dynamicarr
{
	struct s_node	**array;
	int				len;
	int				freespace;
}					t_dynamicarr;

/*
** lem structures
*/

typedef struct		s_node
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
}					t_node;

typedef struct		s_grapg
{
	int				len;
	t_dynamicarr	*nodes;
	int				start;
	int				end;
}					t_graph;

typedef struct		s_edge
{
	t_node			*from;
	t_node			*to;
	int				w;
}					t_edge;

typedef struct		s_way
{
	int				len;
	int				ants;
	int				on;
	struct s_way	*next;
	t_list			*path;
}					t_way;

typedef struct		s_var
{

	int				n_ways;
	int				steps;
	struct s_var	*next;
	t_way			*ways;
}					t_var;

typedef struct		s_lem
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
	short	lflag;
	short	pflag;
	short	hflag;
}					t_lem;

/*
** Extended list
*/

void				reverse_list(t_list **head_ref);

/*
** Dynamic Array
*/

int					init_darr(t_dynamicarr **arr);
void				cpy_array(t_node **dest, t_node **src,
					int freeornot, int len);
int					add_darr(t_dynamicarr **arr, t_node *value);
void				print_darr(t_dynamicarr *arr);
void				free_d_arr(t_dynamicarr **arr);

/*
** nodes
*/

void				free_nodes(t_node **arr);
t_node				*new_node(const char *name, const char *x, const char *y);
void				free_node(t_node **node_to_del);
t_node				*new_node_conv(const char *name, int x, int y);
t_node				*find_node(const char *name, t_graph *graph);

/*
** service
*/

t_lem				*error_f(char *text, int init);
void				free_lem(t_lem *lem);
void				reverse_list(t_list **head_ref);
t_graph				*new_graph(void);

/*
** solving
*/

void				solve(t_lem *lem);
int					bellman_ford(t_lem *lem);
void				set_in_way(t_lem *lem);
void				dublicate_nodes(t_lem *lem);
void				make_paths(t_lem *lem);
void				make_new_paths(t_lem *lem);
void				make_paths_many(t_lem *lem);

/*
** edges
*/

t_edge				*new_edge(t_node *from, t_node *to);
int					create_edge(t_lem	*lem);
void				del_edge(void *edge_addr, size_t size);
void				print_edges(t_list *elem);
void				all_edges_in_paths_connected(t_lem *lem);
void				copy_edge(t_lem *lem);
void				refresh_edges(t_lem *lem);

/*
** run ants
*/

void				count_steps(t_lem *lem, t_var *var);
void				run_ants(t_lem *lem);
void				print_nodes(t_lem *lem);

/*
** var structure
*/

void				free_var(t_var	**var);
void				free_vars(t_var **vars);
t_var				*new_var(int n_ways);
int					check_solutions(t_lem *lem);
void				choose_solution(t_lem *lem);
void				make_solution_from_first(t_lem *lem);
void				make_solutuins_from_second(t_lem *lem);

/*
** copy_paths
*/

void				copy_paths(t_lem *lem);

/*
** find_edge
*/

int					path_edges(t_edge *a, t_edge *b);
int					disjoint_edge(t_edge *a, t_edge *b);
int					in_way_edge(t_edge *a, t_edge *b);
int					start_edges(t_edge *a, t_edge *b);
t_edge				*find_edge(t_list **paths, t_edge *edge,
								int (*f)(t_edge*, t_edge*));

/*
** get_edge
*/

t_edge				*get_edge(t_node *from, t_node *to, t_lem *lem);

/*
** delete copies or disjoint edges
*/

void				change_path_dublicates(t_list *list);
void				delete_copy_nodes(t_lem *lem);
void				delete_dublicates(t_lem *lem);
void				delete_disjoint_edges(t_lem *lem);

/*
** debug
*/

t_edge				*find_edge_without_delete(t_lem *lem,
									t_node *from, t_node *to);
t_node				*find_node_without_delete(t_lem *lem, const char *name);

/*
** flags
*/

void				parse_flags_lemin(int ac, char **av, t_lem *lem);
void				execute_flags_after(t_lem *lem);
void				execute_flags_before(t_lem *lem);

/*
** reading from Bogdan
*/

typedef struct		s_rooms
{
	char			*room;
	int				x;
	int				y;
	int				cnt;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_cnct
{
	struct s_rooms	*from;
	struct s_rooms	*to;
	struct s_cnct	*next;
}					t_cnct;

typedef struct		s_read
{
	long			ant_cnt;
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
	char			*global_line;
}					t_read;

/*
** reading
*/
t_read				*init_read();
void				free_read(t_read *head);
t_rooms				*init_room();
void				free_rooms(t_rooms *head);
t_cnct				*init_cnct();
void				free_cnct(t_cnct *head);
int					gnl(t_read *reader);
int					check_after(char	*line, int i);
int					base_check_room(t_read *reader);
int					freed(char **line);
int					add_start_end(t_read *reader);
int					skip_it(t_read *reader, int flag);
int					read_name(t_read *reader, char **name, int num);
int					add_name(t_read *reader, char *tmp, t_cnct *link, int num);
int					add_link_list(t_read *reader, t_cnct *link);
int					read_link(t_read *reader);
int					links(t_read *reader);
int					read_room_content(t_read *reader, t_rooms *room);
int					check_room(t_read *reader, t_rooms *room);
int					add_room_help(t_read *reader, t_rooms *room, int flag);
int					add_room(t_read *reader, t_rooms *room, int flag);
int					read_room(t_read *reader, int flag);
int					rooms(t_read *reader);
int					first_line(t_read *reader);
int					reading(t_read *reader);
void				convert_structure(t_read *read, t_lem *lem);
int					in_neighbors(t_dynamicarr *arr_d, int len, t_node *target);

#endif

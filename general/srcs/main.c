/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrynn <sbrynn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 19:15:11 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/18 17:06:13 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int ac, char **av)
{
	t_lem	*lem;
	t_read	*reader;

	lem = error_f(NULL, 1);
	parse_flags_lemin(ac, av, lem);
	execute_flags_before(lem);
	if (!(reader = init_read()))
		error_f("reader malloc error", 0);
	if (reading(reader))
		error_f("reaging error", 0);
	convert_structure(reader, lem);
	solve(lem);
	write(1, reader->global_line, ft_strlen(reader->global_line));
	write(1, "\n", 1);
	run_ants(lem);
	execute_flags_after(lem);
	free_lem(lem);
	free_read(reader);
	exit(0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:09:14 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:09:18 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	init_filler(t_filler *f)
{
	ft_bzero(f, sizeof(t_filler));
	f->coord.x = -1;
	f->coord.y = -1;
	f->board = (t_grid *)ft_memalloc(sizeof(t_grid));
	f->piece = (t_grid *)ft_memalloc(sizeof(t_grid));
}

void	identify_bots(t_filler *f)
{
	char *line;

	line = NULL;
	get_next_line(0, &line);
	f->my_bot = ((line[10] == '1') ? 'O' : 'X');
	f->enemy_bot = ((f->my_bot == 'O') ? 'X' : 'O');
	ft_strdel(&line);
}

void	init_distance_board(t_filler *f)
{
	int i;

	i = 0;
	f->dist_board = (int **)ft_memalloc(sizeof(int *) * (f->board->rows + 1));
	while (i < f->board->rows)
	{
		f->dist_board[i] = (int *)ft_memalloc(sizeof(int)
							* f->board->columns + 1);
		i++;
	}
}

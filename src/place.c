/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:35:20 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:35:23 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	record_new_coordinates(t_filler *f, int x, int y, int dist)
{
	f->coord.x = x;
	f->coord.y = y;
	f->coord.dist = dist;
}

void	calculate_total_piece_distance(t_filler *f, int x, int y)
{
	int i;
	int j;
	int total_dist;

	i = 0;
	total_dist = 0;
	while (i < f->piece->rows)
	{
		j = 0;
		while (j < f->piece->columns)
		{
			total_dist += f->dist_board[y + i][x + j];
			j++;
		}
		i++;
	}
	if (f->coord.dist == -1 || total_dist < f->coord.dist)
		record_new_coordinates(f, x, y, total_dist);
}

void	attempt_to_place_a_piece(t_filler *f, int x, int y)
{
	int i;
	int j;
	int my_bot_cell;

	i = 0;
	my_bot_cell = 0;
	while (i < f->piece->rows)
	{
		j = 0;
		while (j < f->piece->columns)
		{
			if (f->piece->data[i][j] == '*')
			{
				if (f->board->data[y + i][x + j] == f->my_bot 
					|| f->board->data[y + i][x + j] == f->my_bot + 32)
					my_bot_cell++;
				else if (f->board->data[y + i][x + j] == f->enemy_bot
					|| f->board->data[y + i][x + j] == f->enemy_bot + 32)
					return ;
			}
			j++;
		}
		i++;
	}
	(my_bot_cell == 1) ? calculate_total_piece_distance(f, x, y) : 0;
}

void	place_a_piece(t_filler *f)
{
	int x;
	int y;

	y = 0;
	while (y < f->board->rows)
	{
		x = 0;
		while (x < f->board->columns)
		{
			if (f->piece->rows + y <= f->board->rows
				&& f->piece->columns + x <= f->board->columns)
			{
				attempt_to_place_a_piece(f, x, y);
			}
			x++;
		}
		y++;
	}
	ft_printf("%d %d\n", f->coord.y, f->coord.x);
}

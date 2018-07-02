/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manhattan_algo.c.                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:20:04 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:20:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int 	calculate_distance(int x, int y, t_filler *f)
{
	int dist;
	int min_dist;
	int enemy_x;
	int enemy_y;

	min_dist = -1;
	enemy_y = 0;
	while (enemy_y < f->board->rows)
	{
		enemy_x = 0;
		while (enemy_x < f->board->columns)
		{
			if (f->board->data[enemy_y][enemy_x] == f->enemy_bot ||
				f->board->data[enemy_y][enemy_x] == f->enemy_bot + 32)
			{
				dist = abs(x - enemy_x) + abs(y - enemy_y);
				(min_dist == -1 || dist < min_dist) ? min_dist = dist : 0;
			}
			enemy_x++;
		}
		enemy_y++;
	}
	return (min_dist);
}

void	form_manhattan_distance_board(t_filler *f)
{
	int x;
	int y;

	y = 0;
	while (y < f->board->rows)
	{
		x = 0;
		while (x < f->board->columns)
		{	
			f->dist_board[y][x] = calculate_distance(x, y, f);
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 06:06:11 by akorzhak          #+#    #+#             */
/*   Updated: 2018/06/25 06:31:46 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	handle_game_loop(t_filler *f)
{
	char *line;

	line = NULL;
	while (skip_the_line())
	{
		f->coord.dist = -1;
		fill_the_grid_data(f->board, BOARD_OFFSET);
		identify_grid_dimensions(f->piece);
		fill_the_grid_data(f->piece, PIECE_OFFSET);
		form_manhattan_distance_board(f);
		place_a_piece(f);
	}
}

int		main(void)
{
	t_filler	f;

	init_filler(&f);
	identify_bots(&f);
	identify_grid_dimensions(f.board);
	init_distance_board(&f);
	handle_game_loop(&f);
	free_memory(&f);
	return (0);
}

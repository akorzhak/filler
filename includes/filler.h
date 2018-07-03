/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 14:16:49 by akorzhak          #+#    #+#             */
/*   Updated: 2018/06/25 05:51:13 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libftprintf.h"
# include <fcntl.h>
# include <math.h>

# define BOARD_OFFSET 4
# define PIECE_OFFSET 0

typedef struct		s_grid
{
	int				rows;
	int				columns;
	char			**data;
}					t_grid;

typedef struct		s_coordinate
{
	int				x;
	int				y;
	int				dist;
}					t_coordinate;

typedef struct		s_filler
{
	char			my_bot;
	char			enemy_bot;
	t_grid			*piece;
	t_grid			*board;
	int				**dist_board;
	t_coordinate	coord;
}					t_filler;

void				init_filler(t_filler *f);
void				identify_bots(t_filler *f);
void				init_distance_board(t_filler *f);
int					skip_the_line(void);
void				identify_grid_dimensions(t_grid *grid);
void				fill_the_grid_data(t_grid *grid, int offset);
void				free_the_grid_data(t_grid *grid);
void				form_manhattan_distance_board(t_filler *f);
void				place_a_piece(t_filler *f);
void				free_memory(t_filler *f);

#endif

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
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

# define BOARD_OFFSET 4
# define PIECE_OFFSET 0
# define USAGE "USAGE: ./resources/filler_vm -f resources/maps/[map00/map01/\
				map02/map03] -p[1/2] ./[name].filler -p[2/1] ./resources/\
				players/[name].filler"
# define ERROR "Something went wrong"
# define FIRST_LINES "$$$ exec p"
# define MY_BOT_NAME "akorzhak.filler"

typedef struct		s_grid
{
	int				rows;
	int				columns;
	char			**data;
}					t_grid;

typedef struct		s_filler
{
	char			my_bot;
	char			enemy_bot;
	t_grid			piece;
	t_grid			board;
	int				**dist_board;
}					t_filler;

int					main(void);
void				display_error_message(char *message);
void				display_message(char *message);

#endif

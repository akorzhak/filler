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

void	skip_the_line(char **line)
{
	get_next_line(0, line);
	ft_strdel(line);
}

void	fill_the_grid_data(char **line, t_grid *grid, int offset)
{
	int i;

	i = 0;
	grid->data = (char **)malloc(sizeof(char *) * (grid->rows + 1));
	while (i < grid->rows)
	{
		get_next_line(0, line);
		grid->data[i] = ft_strdup(*(line + offset));
		ft_strdel(line);
		i++;
	}
	grid->data[i] = NULL; //next - <got (X)
}

void	handle_game_loop(char **line, t_filler *filler)
{
	skip_the_line(line);
	fill_the_grid_data(line, &filler->board, BOARD_OFFSET); //Next - Piece 3 6
	identify_grid_dimensions(line, &filler->piece);
	fill_the_grid_data(line, &filler->piece, PIECE_OFFSET); //maybe filler->&piece ???
	possible_move = get_possible_moves(line, filler);
	if (!possible_move)
	{
		exit(0);
	}
	make_a_move(possible_move);
}

int 	identify_grid_dimensions(char **line, t_grid *grid)
{
	grid = (t_grid *)malloc(sizeof(t_grid));
	while (!ft_isdigit(**line))
		(*line)++;
	grid->rows = ft_atoi(*line);
	while (ft_isdigit(**line))
		(*line)++;
	grid->columns = ft_atoi(*(line + 1));
	ft_strdel(line); //Plateau
}

void 	identify_bots(char **line, t_filler *filler)
{
	char *player_nb;

	*line = NULL;
	while (get_next_line(0, line) && line && !ft_strncmp(line, FIRST_LINES, 9))
	{
		if (line[10] == '1')
		{
			filler->my_bot = (ft_strstr(line, MY_BOT_NAME) ? O : X);
			filler->enemy_bot = ((filler->my_bot == O) ? X : O);
		}
		ft_strdel(line);
	}
}

void	init_filler(t_filler *filler)
{
	ft_bzero(filler, sizeof(t_filler));
}

int		main(int argc, char **argv)
{
	char		*line;
	t_filler	filler;
	
	init_filler(&filler);
	identify_bots(&line, &filler); //line at Plateau
	identify_grid_dimensions(&line, &filler->board);
	handle_game_loop(&line, &filler);
	return (0);
}

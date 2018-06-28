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

int		skip_the_line(char **line)
{
	if (get_next_line(0, line) <= 0)
		return (0);
	ft_strdel(line);
	return (1);
}

void	free_the_grid_data(t_grid *grid, int offset)
{
	if (grid->data && offset == PIECE_OFFSET)
	{
		ft_memdel((void **)&grid->data); //grid->data ???
	}
	if (!grid->data)
	{
		grid->data = (char **)ft_memalloc(sizeof(char *) * (grid->rows + 1));
	}
}

void	fill_the_grid_data(char **line, t_grid *grid, int offset)
{
	int i;

	i = 0;
	free_the_grid_data(grid, offset);
	while (i < grid->rows)
	{
		get_next_line(0, line);
		offset == PIECE_OFFSET ? grid->data[i] = ft_strdup(*line) : 0;
		offset == BOARD_OFFSET ? ft_strcpy(grid->data[i], *(line + offset)) : 0;
		ft_strdel(line);
		i++;
	}
	grid->data[i] = NULL; //next - <got (X)
}

void 	identify_grid_dimensions(char **line, t_grid *grid)
{
	grid = (t_grid *)ft_memalloc(sizeof(t_grid));
	while (!ft_isdigit(**line))
	{
		(*line)++;
	}
	grid->rows = ft_atoi(*line);
	while (ft_isdigit(**line))
	{
		(*line)++;
	}
	grid->columns = ft_atoi(*(line + 1));
	ft_strdel(line); //Plateau
}

void	init_distance_board(t_filler *filler)
{
	int x;
	int y;

	x = 0;
	y = 0;
	filler->dist_board = (int **)ft_memalloc(sizeof(int *)
							* (filler->board.rows + 1));
	while (y < filler->board->rows)
	{
		filler->dist_board[y] = (int *)ft_memalloc(sizeof(int) 
								* filler->board.columns + 1);
		y++;
	}
}

int 	calculate_distance(int x, int y, t_filler *filler)
{
	int dist;
	int min_dist;
	int enemy_x;
	int enemy_y;

	min_dist = 0;
	enemy_y = 0;
	while (enemy_y < filler->board.rows)
	{
		enemy_x = 0;
		while (enemy_x < filler->board.columns)
		{
			if (filler->board.data[enemy_y][enemy_x] == filler->enemy_bot)
			{
				dist = abs(x - enemy_x) + abs(y - enemy_y);
				(dist < min_dist) ? min_dist = dist : 0;
			}
			enemy_x++;
		}
		enemy_y++;
	}
	return (min_dist);
}

void	form_manhattan_distance_board(t_filler *filler)
{
	int x;
	int y;

	y = 0;
	while (y < filler->board.rows)
	{
		x = 0;
		while (x < filler->board.columns)
		{
			filler->dist_board[y][x] = calculate_distance(x, y, filler);
			x++;
		}
		y++;
	}
}

void	attempt_to_place_a_piece(t_filler *filler, int x, int y) //to_do
{

}

int 	place_a_piece(t_filler *filler)
{
	int X;
	int Y;
	int x;
	int y;

	y = 0;
	while (y < filler->board.rows)
	{
		x = 0;
		while (x < filler->board.columns)
		{
			if (filler->piece.rows + y <= filler->board.rows
				&& filler->piece.columns + x <= filler->board.columns)
			attempt_to_place_a_piece(filler, x, y);
			x++;
		}
		y++;
	}

	return (1);
}

void		handle_game_loop(char **line, t_filler *filler)
{
	while (skip_the_line(line))
	{
		fill_the_grid_data(line, &filler->board, BOARD_OFFSET); //Next - Piece 3 6
		identify_grid_dimensions(line, &filler->piece);
		fill_the_grid_data(line, &filler->piece, PIECE_OFFSET); //maybe filler->&piece ???
		form_manhattan_distance_board(filler);
		if (!place_a_piece(filler))
			break ;
	}	
	return (0);
}

void 	identify_bots(char **line, t_filler *filler)
{
	*line = NULL;
	while (get_next_line(0, line) && line && !ft_strncmp(*line, FIRST_LINES, 9))
	{
		if (*line[10] == '1')
		{
			filler->my_bot = (ft_strstr(*line, MY_BOT_NAME) ? 'O' : 'X');
			filler->enemy_bot = ((filler->my_bot == 'O') ? 'X' : 'O');
		}
		ft_strdel(line);
	}
}

void	init_filler(t_filler *filler)
{
	ft_bzero(filler, sizeof(t_filler));
}

int		main(void)
{
	char		*line;
	t_filler	filler;
	
	init_filler(&filler);
	identify_bots(&line, &filler); //line at Plateau
	identify_grid_dimensions(&line, &filler.board);
	init_distance_board(filler);
	handle_game_loop(&line, &filler);
	return (0);
}

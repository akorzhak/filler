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
#include <stdio.h>

int		skip_the_line(char **line)
{
	if (get_next_line(0, line) <= 0)
	{
		return (0);
	}
	if (*line)
		ft_strdel(line);
	return (1);
}

void	skip_two_lines(char **line)
{
	skip_the_line(line);
	skip_the_line(line);
}

void	free_the_grid_data(t_grid *grid)
{
	int i;

	i = 0;
	if (grid->data)
	{
		while (i < grid->columns)
		{
			if (grid->data[i])
				ft_strdel(&grid->data[i]);
			i++;
		}
		if (grid->data)
			ft_memdel((void **)&grid->data); //grid->data ???
	}
}

void	fill_the_grid_data(t_grid *grid, int offset)
{	
	int i;
	char *line;
	static char first_read = 1;
	// static int a = 0;
	// a++;
	// FILE * pfile;
	// pfile = fopen("temp.txt", "w+");

	// fprintf(pfile, "%d\n", first_read);
	// fprintf(pfile, "%d\n", offset);
	// fprintf(pfile, "%d\n", a);
	// 

	line = NULL;
//	FILE * pfile;
//	pfile = fopen("temp.txt", "w+");
	
	i = 0;
//	fprintf(pfile, "%d\n", grid->rows);
	if (offset == PIECE_OFFSET)
		free_the_grid_data(grid);
	if (offset == PIECE_OFFSET || first_read)
		grid->data = (char **)ft_memalloc(sizeof(char *) * (grid->rows + 1));
	if (offset == BOARD_OFFSET && !first_read)
	{
	//	skip_two_lines(&line);
		skip_the_line(&line);
	//	get_next_line(0, &line);
		
			
	//	exit(0);
	}
	
	
	
//	static int a = 0;
	while (i < grid->rows)
	{
	//	if (offset == PIECE_OFFSET)
	//		a++;
		get_next_line(0, &line);
		
		if (offset == PIECE_OFFSET || first_read)
		{
			grid->data[i] = ft_strdup(line + offset);
	
		//	 fprintf(pfile, "%s\n", line + offset);
		//		fprintf(pfile, "%s\n", grid->data[i]);
		}
		else
		 	ft_strcpy(grid->data[i], (line + offset));
		
		// if (offset == PIECE_OFFSET)
		// {
		// 	FILE * pfile;
		// 	pfile = fopen("temp.txt", "w+");
		// 	fprintf(pfile, "%s\n", line);
		// 	fprintf(pfile, "%s\n", grid->data[i]);
		// 	fprintf(pfile, "%s\n", grid->data[i + 1]);
		// 	fprintf(pfile, "%d\n", a);
		// 	fprintf(pfile, "%d\n", grid->rows);
		// 	fclose(pfile);
		// }
		if (line)
			ft_strdel(&line);
		i++;
	}
	first_read = 0;
}

void 	identify_grid_dimensions(t_grid *grid)
{
 	char *line;
 	char *str;
// 	FILE * pfile;
 	line = NULL;
// 	pfile = fopen("temp.txt", "w+");
	
	get_next_line(0, &line); //Plateau 15 17: //Piece 8 12:
//	fprintf(pfile, "%s\n", line);
	str = line;
	while (!ft_isdigit(*str))
	{
		str++;
	}
	grid->rows = ft_atoi(str);
	while (ft_isdigit(*str))
	{
		str++;
	}
	grid->columns = ft_atoi(str + 1);
	// fprintf(pfile, "rows: %d columns: %d\n", grid->rows, grid->columns);
	if (line)
		ft_strdel(&line);
	// fclose(pfile);
}

void	init_distance_board(t_filler *f)
{
	int i;

	i = 0;
	f->dist_board = (int **)ft_memalloc(sizeof(int *) * (f->board->rows + 1));
	while (i < f->board->rows)
	{
		f->dist_board[i] = (int*)ft_memalloc(sizeof(int) * f->board->columns + 1);
		i++;
	}
}

int 	calculate_distance(int x, int y, t_filler *f)
{
	int dist;
	int min_dist;
	int enemy_x;
	int enemy_y;
//	FILE * pfile;
//	pfile = fopen("temp.txt", "w+");

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
			//	fprintf(pfile, "%d\n", min_dist);
			}
			enemy_x++;
		}
		enemy_y++;
	}
//	fclose(pfile);	
	return (min_dist);
}

void	form_manhattan_distance_board(t_filler *f)
{

//	FILE * pfile;
//	pfile = fopen("temp.txt", "w+");
	int x;
	int y;

	y = 0;
	while (y < f->board->rows)
	{
		x = 0;
		while (x < f->board->columns)
		{	
			f->dist_board[y][x] = calculate_distance(x, y, f);
	//		fprintf(pfile, "%d\n", f->dist_board[y][x]);
			x++;
		}
		y++;
	}
//	 fclose(pfile);	
}

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
	// FILE * pfile;
	// pfile = fopen("temp.txt", "w+");

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
	// fprintf(pfile, "%d\n", x);
	// fprintf(pfile, "%d\n", y);
	// fprintf(pfile, "%d\n", f->coord.dist);
	// fprintf(pfile, "%d\n", f->coord.x);
	// fprintf(pfile, "%d\n", f->coord.y);
	// fclose(pfile);
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
		while (j < f->piece->columns && my_bot_cell <= 1)
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
	my_bot_cell ? calculate_total_piece_distance(f, x, y) : 0;
}

int 	place_a_piece(t_filler *f)
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
	
	if (f->coord.dist == -1)
	{
		ft_putstr("0 0\n");
		return (0);
	}
	else
	{
		// FILE * pfile;
		// char *line;
		// line = NULL;
		// pfile = fopen("temp.txt", "w+");
		// fprintf(pfile, "%d\n", x);
		// fprintf(pfile, "%d\n", y);
		// fprintf(pfile, "distance: %d\n", f->coord.dist);
		// fprintf(pfile, "X: %d\n", f->coord.x);
		// fprintf(pfile, "Y: %d\n", f->coord.y);	

		ft_printf("%d %d\n", f->coord.y, f->coord.x);

		// get_next_line(0, &line);
		// fprintf(pfile, "%s\n", line);
		// fclose(pfile);

	}
	return (1);
}

void		handle_game_loop(t_filler *f)
{
	char *line;
	// static int i = 0;
	// FILE * pfile;
	// pfile = fopen("temp.txt", "w+");
	

	line = NULL;
	while (skip_the_line(&line))
	{

		// i++;
		// fprintf(pfile, "%d\n", i);
		// fclose(pfile);
		f->coord.dist = -1;	
		fill_the_grid_data(f->board, BOARD_OFFSET);	
		identify_grid_dimensions(f->piece);
		fill_the_grid_data(f->piece, PIECE_OFFSET);
		// FILE * pfile;
		// char *line;
		// line = NULL;
		// pfile = fopen("temp.txt", "w+");
		// get_next_line(0, &line);
		// fprintf(pfile, "%s\n", line);
		// fclose(pfile);
		// exit(0);
		form_manhattan_distance_board(f);
		place_a_piece(f);
	}

}

void 	identify_bots(t_filler *f)
{
	char *line;
	line = NULL;
	get_next_line(0, &line);
	f->my_bot = ((line[10] == '1') ? 'O' : 'X');
	f->enemy_bot = ((f->my_bot == 'O') ? 'X' : 'O');
	ft_strdel(&line);
}

void	init_filler(t_filler *f)
{
	ft_bzero(f, sizeof(t_filler));
	f->coord.x = -1;
	f->coord.y = -1;
	f->coord.dist = -1;
	f->board = (t_grid *)ft_memalloc(sizeof(t_grid));
	f->piece = (t_grid *)ft_memalloc(sizeof(t_grid));
}

void	free_dist_board(t_filler *f)
{
	int i;

	i = 0;
	while (i < f->board->rows)
	{
		ft_memdel((void **)&f->dist_board[i]);
		i++;
	}
	ft_memdel((void **)f->dist_board); //&f->dist_board
}

void	free_memory(t_filler *f)
{
	free_dist_board(f);
//	free_the_grid_data(f->board);
	free_the_grid_data(f->piece);
//	ft_memdel((void **)f->board);
//	ft_memdel((void **)f->piece);
}

int		main(void)
{
	t_filler	f;
	init_filler(&f);
	identify_bots(&f); //line at Plateau
	identify_grid_dimensions(f.board); //Plateau is created and deleted	
	init_distance_board(&f);
	handle_game_loop(&f); //empty line
//	free_memory(&f);
	return (0);
}

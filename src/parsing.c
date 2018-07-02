/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void 	identify_grid_dimensions(t_grid *grid)
{
	char *line;
	char *str;
	line = NULL;
	
	get_next_line(0, &line);
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
	ft_strdel(&line);
}

void	fill_the_grid_data(t_grid *grid, int offset)
{	
	int i;
	char *line;
	static char first_read = 1;

	line = NULL;
	i = 0;
	if (offset == PIECE_OFFSET)
		free_the_grid_data(grid);
	if (offset == PIECE_OFFSET || first_read)
		grid->data = (char **)ft_memalloc(sizeof(char *) * (grid->rows + 1));
	if (offset == BOARD_OFFSET && !first_read)
		skip_the_line();
	while (i < grid->rows)
	{
		get_next_line(0, &line);
		
		if (offset == PIECE_OFFSET || first_read)
			grid->data[i] = ft_strdup(line + offset);
		else
		 	ft_strcpy(grid->data[i], (line + offset));
		ft_strdel(&line);
		i++;
	}
	first_read = 0;
}

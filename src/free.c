/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:14:31 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:14:34 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	free_the_grid_data(t_grid *grid)
{
	int i;

	i = 0;
	if (grid->data)
	{
		while (grid->data[i])
		{
			ft_strdel(&grid->data[i]);
			i++;
		}
		ft_memdel((void **)&grid->data);
	}
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
	ft_memdel((void **)f->dist_board);
}

void	free_memory(t_filler *f)
{
	free_dist_board(f);
	free_the_grid_data(f->board);
	free_the_grid_data(f->piece);
	ft_memdel((void **)&f->board);
	ft_memdel((void **)&f->piece);
}

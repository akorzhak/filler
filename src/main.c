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

int 	identify_board(char **line, t_filler *filler)
{
	while (get_next_line(0, line) && ft_strncmp(line, BOARD_DIMENSIONS_LINE))
		strdel(line);
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
		strdel(line);
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
	
	if (identify_board(&line, &filler) == 1)
		display_error_message(ERROR);
	return (0);
}

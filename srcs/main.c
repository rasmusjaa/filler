/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 16:05:02 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/22 18:09:24 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_filler	*init()
{
	t_filler *fil;

	if (!(fil = (t_filler *)malloc(sizeof(t_filler))))
		return (NULL);
	fil->grid = NULL;
	fil->width = 0;
	fil->height = 0;
	fil->piece_width = 0;
	fil->piece_height = 0;
	fil->piece_min_y = -1;
	fil->piece_max_y = -1;
	fil->piece_min_x = -1;
	fil->piece_max_x = -1;
	return (fil);
}

int			free_all(t_filler *fil)
{
	int		row;

	row = 0;
	while (row < fil->height)
	{
		free(fil->grid[row]);
		row++;
	}
	free(fil->grid);
	row = 0;
	while (row < fil->piece_height)
	{
		free(fil->piece[row]);
		row++;
	}
	free(fil->piece);
	free(fil->opp_y);
	free(fil->opp_x);
	free(fil);
	return (0);
}

int			game_loop(t_filler *fil)
{
	char	*line;
	int		game = 0;

	while (ft_get_next_line(0, &line) > 0 && game == 0)
	{
		if (ft_strncmp("$$$", line, 3) == 0)
		{
			if (read_player(fil, ft_atoi(&line[10])))
				return(1);
		}
		else if (ft_strncmp("Plateau", line, 7) == 0)
		{
			if (read_grid(fil, &line[8]))
				return(1);
			rate_grid(fil);
			ft_dprintf(2, "GRID\n");
			print_int_grid(fil->grid, fil->height, fil->width);
		}
		else if (ft_strncmp("Piece", line, 5) == 0)
		{
			if (read_piece(fil, &line[6]))
				return(1);
			ft_dprintf(2, "PIECE\n");
			print_int_grid(fil->piece, fil->piece_height, fil->piece_width);
			ft_dprintf(2, "min y%d x%d\n", fil->piece_min_y, fil->piece_min_x);
			ft_dprintf(2, "max y%d x%d\n", fil->piece_max_y, fil->piece_max_x);
			if (set_piece(fil) == 1)
				game = 1;
		}
		ft_strdel(&line);
	}
	return (0);
}

int			main(void)
{
	t_filler	*fil;
	int 		ret;

	ret = 0; //return value if needed
	if (!(fil = init()))
		return (1);
	if (game_loop(fil) == 1)
		return (1);
	free_all(fil);
	return (ret);
}

// testaa isommal bufferil
// karrtan ja piecen validointi jos muita merkkeja kun pisteet ja pelaajat
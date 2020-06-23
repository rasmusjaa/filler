/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 22:58:29 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/24 01:35:04 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	try_piece(t_filler *fil, int y, int x)
{
	int 	i;
	int 	j;
	int 	touching;
	int 	score;

	touching = 0;
	score = 0;
	i = 0;
	while (i < fil->piece_height)
	{
		j = 0;
		while (j < fil->piece_width)
		{
			if (fil->piece[i][j] == 1)
			{
				if ((y + i >= fil->height) || (x + j >= fil->width))
					return (-1);
				else if (fil->grid[y + i][x + j] == -2)
					return (-1);
				else if (fil->grid[y + i][x + j] == -1)
				{
					touching++;
					if (touching == 2)
						return (-1);
				}
				else
				{
					score += fil->grid[y + i][x + j];
				}
			}
			j++;
		}
		i++;
	}
	if (touching == 1)
		return (score);
	return (-1);
}

int		set_piece(t_filler *fil)
{
	int 	i;
	int 	j;
	int 	score;
	int scores;
	int lowest[3];

	i = 0;
	scores = 0;
	lowest[0] = 0;
	while (i - fil->piece_min_y < fil->height - fil->piece_max_y)
	{
		j = 0;
		while (j - fil->piece_min_x < fil->width - fil->piece_max_x)
		{
			score = try_piece(fil, i - fil->piece_min_y, j - fil->piece_min_x);
			if (score > 0)
			{
				scores++;
				if (score < lowest[0] || lowest[0] == 0)
				{
					lowest[0] = score;
					lowest[1] = i - fil->piece_min_y;
					lowest[2] = j - fil->piece_min_x;
				}
			}
			j++;
		}
		i++;
	}
//	ft_dprintf(2, "possible moves: %d\n", scores);
	if (lowest[0] > 0)
	{
//		ft_dprintf(2, "best place y %d, x %d, score %d\n", lowest[1], lowest[2], lowest[0]);
	//		while(1);
	//	sleep(1);
		ft_printf("%d %d\n", lowest[1], lowest[2]);
		return (0);
	}
	else
	{
//		ft_dprintf(2, "No possible move\n");
//		while (1);
		ft_printf("%d %d\n", 0, 0);
		return (0);
	}
}

int			fill_piece_row(t_filler *fil, int row, char *line)
{
	int 	column;

	column = 0;
	while (column < fil->piece_width)
	{
		if (line[column] == '*')
		{
			fil->piece[row][column] = 1;
			if (column < fil->piece_min_x || fil->piece_min_x == -1)
				fil->piece_min_x = column;
			if (column > fil->piece_max_x || fil->piece_max_x == -1)
				fil->piece_max_x = column;
			if (row < fil->piece_min_y || fil->piece_min_y == -1)
				fil->piece_min_y = row;
			if (row > fil->piece_max_y || fil->piece_max_y == -1)
				fil->piece_max_y = row;
		}
		column++;
	}
	return (0);
}

int			fill_piece(t_filler *fil)
{
	char	*line;
	int		row;

	row = 0;
	while (row < fil->piece_height && ft_get_next_line(0, &line) > 0)
	{
		fill_piece_row(fil, row, line);
		ft_strdel(&line);
		row++;
	}
	return (0);
}

int			read_piece(t_filler *fil, char *line)
{
	fil->piece_min_y = -1;
	fil->piece_max_y = -1;
	fil->piece_min_x = -1;
	fil->piece_max_x = -1;
	fil->piece_height = ft_atoi(line);
	while (line && *line != ' ')
		line++;
	line++;
	fil->piece_width = ft_atoi(line);
	if (fil->piece_width < 1 || fil->piece_height < 1)
		return (1);
	if (!(fil->piece = int_grid(fil->piece_width, fil->piece_height)))
		return (1);
	if (fill_piece(fil))
		return (1);
	return (0);
}

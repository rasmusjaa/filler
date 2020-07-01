/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 23:01:15 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/01 17:49:32 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			**int_grid(int width, int height)
{
	int **grid;
	int row;
	int i;

	if (!(grid = (int**)malloc(height * sizeof(int*))))
		return (NULL);
	row = 0;
	while (row < height)
	{
		if (!(grid[row] = (int*)malloc(width * sizeof(int))))
			return (NULL);
		i = 0;
		while (i < width)
		{
			(grid[row][i] = 0);
			i++;
		}
		row++;
	}
	return (grid);
}

void		print_int_grid(int **grid, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	ft_dprintf(2, "ARRAY height %d width %d\n", height, width);
	while (i < height)
	{
		j = 0;
		ft_dprintf(2, "%-3d [ ", i);
		while (j < width)
		{
			if (j == width - 1)
				ft_dprintf(2, "%d", grid[i][j]);
			else
				ft_dprintf(2, "%d, ", grid[i][j]);
			j++;
		}
		ft_dprintf(2, " ]\n");
		i++;
	}
}

int			read_player(t_filler *fil, int n)
{
	if (n != 1 && n != 2)
		return (1);
	fil->player = n == 1 ? 'O' : 'X';
	fil->opp = n == 1 ? 'X' : 'O';
	return (0);
}

void		check_lowest_score(t_filler *fil, int score, int i, int j)
{
	if (score < fil->lowest[0] || fil->lowest[0] == 0)
	{
		fil->lowest[0] = score;
		fil->lowest[1] = i - fil->piece_min_y;
		fil->lowest[2] = j - fil->piece_min_x;
	}
}

int			try_piece_on_spot(t_filler *fil, int y, int x)
{
	if ((y >= fil->height) || (x >= fil->width) || (fil->grid[y][x] == -2))
		return (-1);
	else if (fil->grid[y][x] == -1)
	{
		fil->touching++;
		if (fil->touching == 2)
			return (-1);
	}
	else
		fil->score += fil->grid[y][x];
	return (0);
}

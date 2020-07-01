/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 23:01:15 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/01 15:42:52 by rjaakonm         ###   ########.fr       */
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

void		print_info(t_filler *fil)
{
	ft_dprintf(2, "My score %d, opponent score %d\n",
		fil->my_score, fil->enemy_score);
}

int			read_player(t_filler *fil, int n)
{
	if (n != 1 && n != 2)
		return (1);
	fil->player = n == 1 ? 'O' : 'X';
	fil->opp = n == 1 ? 'X' : 'O';
	return (0);
}

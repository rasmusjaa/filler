/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 22:58:29 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/01 15:41:22 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			find_closest_opp(t_filler *fil, int y, int x)
{
	int i;
	int j;
	int d;
	int	closest;

	closest = 0;
	i = 0;
	while (i < fil->height)
	{
		j = 0;
		while (j < fil->width)
		{
			if (fil->grid[i][j] == -2)
			{
				d = i > y ? i - y : y - i;
				d += j > x ? j - x : x - j;
				if (d < closest || closest == 0)
					closest = d;
			}
			j++;
		}
		i++;
	}
	return (closest);
}

void		rate_grid(t_filler *fil)
{
	int	i;
	int	j;

	i = 0;
	fil->my_score = 0;
	fil->enemy_score = 4;
	while (i < fil->height)
	{
		j = 0;
		while (j < fil->width)
		{
			if (fil->grid[i][j] == 0)
				fil->grid[i][j] = find_closest_opp(fil, i, j);
			j++;
		}
		i++;
	}
}

int			fill_row(t_filler *fil, int row, char *line)
{
	int	column;

	column = 0;
	while (column < fil->width)
	{
		if (line[column] == fil->player || line[column] == fil->player + 32)
		{
			fil->grid[row][column] = -1;
		}
		else if (line[column] == fil->opp || line[column] == fil->opp + 32)
		{
			fil->grid[row][column] = -2;
		}
		else
			fil->grid[row][column] = 0;
		column++;
	}
	return (0);
}

int			fill_grid(t_filler *fil)
{
	char	*line;
	char	*temp;
	int		row;

	ft_get_next_line(0, &line);
	ft_strdel(&line);
	row = 0;
	while (row < fil->height && ft_get_next_line(0, &line) > 0)
	{
		temp = line;
		while ((*line >= '0' && *line <= '9') || *line == ' ')
			line++;
		fill_row(fil, row, line);
		ft_strdel(&temp);
		row++;
	}
	return (0);
}

int			read_grid(t_filler *fil, char *line)
{
	if (fil->grid == NULL)
	{
		fil->height = ft_atoi(line);
		while (line && *line != ' ')
			line++;
		line++;
		fil->width = ft_atoi(line);
		if (fil->width < 1 || fil->height < 1)
			return (1);
		if (!(fil->grid = int_grid(fil->width, fil->height)))
			return (1);
	}
	if (fill_grid(fil))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 22:58:29 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/22 18:40:44 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	find_closest_opp(t_filler *fil, int y, int x)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (y + i < fil->height || y - i >= 0)
	{
		if (fil->opp_y[y + i] < fil->height && fil->opp_y[y + i] == 1)
			break;
		if (fil->opp_y[y - i] >= 0 && fil->opp_y[y - i] == 1)
			break;
		i++;
	}
	while (x + j < fil->width || x - j >= 0)
	{
		if (fil->opp_x[x + j] < fil->width && fil->opp_x[x + j] == 1)
			break;
		if (fil->opp_x[x - j] >= 0 && fil->opp_x[x - j] == 1)
			break;
		j++;
	}
	return (i + j);
}

void		rate_grid(t_filler *fil)
{
	int 	i;
	int 	j;

	i = 0;
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
	int 	column;

	column = 0;

	while (column < fil->width)
	{
		if (line[column] == fil->player || line[column] == fil->player + 32)
			fil->grid[row][column] = -1;
		else if (line[column] == fil->opp || line[column] == fil->opp + 32)
		{
			fil->grid[row][column] = -2;
			fil->opp_x[column] = 1;
			fil->opp_y[row] = 1;
		}
		column++;
	}
	return (0);
}

void	init_opp_coord(t_filler *fil)
{
	int i;

	i = 0;
	while (i < fil->width)
	{
		fil->opp_x[i] = 0;
		i++;
	}
	i = 0;
	while (i < fil->height)
	{
		fil->opp_y[i] = 0;
		i++;
	}
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
		if (fill_row(fil, row, line))
			return (1);
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
		if (!(fil->opp_x = (int *)malloc(sizeof(int) * fil->width))
			|| !(fil->opp_y = (int *)malloc(sizeof(int) * fil->height)))
			return (1);
		init_opp_coord(fil);
	}
	if (fill_grid(fil))
		return (1);
	return (0);
}

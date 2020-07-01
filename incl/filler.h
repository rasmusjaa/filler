/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 16:07:52 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/01 17:49:22 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "ft_printf.h"
# include <stdlib.h>

typedef struct	s_filler
{
	char		player;
	char		opp;
	int			height;
	int			width;
	int			**grid;
	int			**piece;
	int			piece_width;
	int			piece_height;
	int			piece_min_y;
	int			piece_max_y;
	int			piece_min_x;
	int			piece_max_x;
	int			lowest[3];
	int			score;
	int			touching;
}				t_filler;

int				**int_grid(int width, int height);
void			print_int_grid(int **grid, int height, int width);
int				read_player(t_filler *fil, int n);
void			check_lowest_score(t_filler *fil, int score, int i, int j);
int				try_piece_on_spot(t_filler *fil, int y, int x);

void			rate_grid(t_filler *fil);
int				read_grid(t_filler *fil, char *line);

int				set_piece(t_filler *fil);
int				read_piece(t_filler *fil, char *line);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 16:07:52 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/01 17:14:29 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "ft_printf.h"
# include <stdlib.h>

typedef struct	s_filler
{
	char	player;
	char	opp;
	int height;
	int		width;
	int		**grid;
	int 	best_x;
	int		best_y;
	int		**piece;
	int pieces;
	int piece_width;
	int		piece_height;
	int		piece_min_y;
	int		piece_max_y;
	int		piece_min_x;
	int		piece_max_x;
	int		my_score;
	int		enemy_score;
} t_filler;

int		**int_grid(int width, int height);
void	print_int_grid(int **grid, int height, int width);
void	print_info(t_filler *fil);
int		read_player(t_filler *fil, int n);

void	rate_grid(t_filler *fil);
int		read_grid(t_filler *fil, char *line);

int		set_piece(t_filler *fil);
int		read_piece(t_filler *fil, char *line);

#endif

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2020/07/01 18:20:42 by rjaakonm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rjaakonm.filler

SRCS =	srcs/grid.c \
		srcs/main.c \
		srcs/piece.c \
		srcs/utilities.c \


FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

INCL = -I incl/ -I libft/libft/incl/ -I libft/printf/incl/

LIB = -L libft -lft

.PHONY: all clean fclean re run

all: $(NAME)

$(NAME): libftmake
	@gcc $(FLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME) -O2

libftmake:
	@make -C libft

clean:
#	@rm -f $(notdir $(OBJS))
#	@rm -f $(OBJS)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

run:
	gcc $(FLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME) -O2
	./filler_vm -p1 ./rjaakonm.filler -p2 ./players/grati.filler -v -f maps/map01

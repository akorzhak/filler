# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/13 18:35:56 by akorzhak          #+#    #+#              #
#    Updated: 2018/01/13 18:35:58 by akorzhak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = akorzhak.filler

C = gcc

CFLAG = -Wall -Wextra -Werror

INC = -I ./includes -I ./ft_printf/includes

PRINTFDIR = ft_printf/

PRINTF = $(PRINTFDIR)libftprintf.a

LIBS = -L ./ft_printf -lftprintf

SRCDIR = src

PLAYERSDIR = ./resources/players/

SRC = main.c init.c free.c parsing.c manhattan_algo.c place.c util.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean

%.o: $(SRCDIR)/%.c
	@$(C) $(CFLAG) -c $< $(INC)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(PRINTFDIR)
	@$(C) $(CFLAG) -o $(NAME) $(OBJ) $(LIBS)
	@cp $(NAME) $(PLAYERSDIR)
	@echo akorzhak.filler compilation is \done
clean:
	@make clean -C $(PRINTFDIR)
	@/bin/rm -f $(OBJ) *~
	@echo object files have been cleaned

fclean: clean
	@make fclean -C $(PRINTFDIR)
	@/bin/rm -f $(NAME)
	@echo akorzhak.filler has been removed

re: fclean all

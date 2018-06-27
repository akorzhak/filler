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

INC = -I ./includes -I ./libft -I /usr/local/include

LIBDIR = libft

LIBFT = $(LIBDIR)/libft.a

LIBMLX = $(MLXDIR)/libmlx.a

LIBS = -L ./libft -lft

SRCDIR = src

PLAYERSDIR = ./resources/players/

SRC = main.c init.c messages.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean

%.o: $(SRCDIR)/%.c
	@$(C) $(CFLAG) -c $< $(INC)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBDIR)
	@$(C) $(CFLAG) -o $(NAME) $(OBJ) $(LIBS)
	@cp $(NAME) $(PLAYERSDIR)
	@echo akorzhak.filler compilation is \done
clean:
	@make clean -C $(LIBDIR)
	@/bin/rm -f $(OBJ) *~
	@echo object files have been cleaned

fclean: clean
	@make fclean -C $(LIBDIR)
	@/bin/rm -f $(NAME)
	@echo akorzhak.filler has been removed

re: fclean all

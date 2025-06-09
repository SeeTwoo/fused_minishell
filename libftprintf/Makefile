# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/01 15:23:38 by gfontagn          #+#    #+#              #
#    Updated: 2024/12/01 15:28:23 by gfontagn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Werror -Wextra -I./include -I./libft
CC = cc $(FLAGS)

SRC := $(wildcard src/*.c)	
SRCB := $(wildcard srcbonus/*.c)	
OBJ := $(SRC:%.c=%.o)
OBJB := $(SRCB:%.c=%.o)

LIBFTDIR = libft
LIBFTNAME = libft.a
LIBFT = $(LIBFTDIR)/$(LIBFTNAME)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)

$(NAME): $(LIBFT) $(OBJ)	
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJ) 

bonus: $(LIBFT) .bonus

.bonus: $(OBJB)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJB)
	@touch .bonus

%.o: %.c 
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	rm -f $(OBJ) $(OBJB) .bonus
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus

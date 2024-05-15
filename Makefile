# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 15:11:53 by dabae             #+#    #+#              #
#    Updated: 2024/05/15 15:07:35 by dabae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
SRC = src/main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L./libft -lft -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	$(MAKE) clean -C ./libft
	@$(RM) -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C ./libft 
	@$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
CC = cc
NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
SRC = $(wildcard *.c)

BONUSSRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	   ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ = $(SRC:.c=.o)
BONUSOBJ = $(BONUSSRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	ar -rcs $@ $^

bonus: $(OBJ) $(BONUSOBJ)
	ar -rcs $(NAME) $^

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	rm -f $(OBJ) $(BONUSOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

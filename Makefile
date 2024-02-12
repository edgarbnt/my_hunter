##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Placeholder
##

SRC	=	src/my_strcat.c \
		src/my_putnbr_str.c \
		src/my_strlen.c \
		src/my_atoi.c \
		src/len_nbr.c \
		src/wtm.c \
		src/wtm02.c \
		src/wtm03.c \
		src/wtm04.c \
		src/wtm05.c \
		src/wtm06.c \
		src/my_strcmp.c


OBJ	=	$(SRC:.c=.o)

NAME	=	my_hunter

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) -lcsfml-graphics -lcsfml-system -lcsfml-window -lm -g


clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean $(NAME)

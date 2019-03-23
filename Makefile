CC		= 	gcc
CFLAGS	+= 	-Wall -Wextra -Werror -Wpedantic
CFLAGS 	+= 	-lm
CFLAGS	+= 	-I ./inc

NAME	=	interpretor

SRC		= 	src/main.c \
			src/ast.c \
			src/func-in.c \
			src/functions.c \
			src/interpreter.c \
			src/parser.c\
			src/parser_utils.c\
			src/repl.c \
			src/token.c \
			src/variables.c

OBJ		= 	$(SRC:.c=.o)

RM		= 	rm -f
LN		= 	ln -s

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: 	clean
	$(RM) $(NAME)

re:			fclean all

.PHONY	= 	all $(NAME) clean fclean re

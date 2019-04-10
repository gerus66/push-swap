NAME1 = checker
NAME2 = push_swap
SRC1 = $(filter-out $(NAME2).c generator.c, $(wildcard *.c))
OBJ1 = ${SRC1:.c=.o}
#HDR1 = $(NAME1).h
SRC2 = $(filter-out $(NAME1).c generator.c, $(wildcard *.c))
OBJ2 = ${SRC2:.c=.o}
HDR = swap.h
FLAGS = #-fsanitize=address #-Wextra -Wall -Werror
LIBDIR = libft
LIB = $(LIBDIR)/libft.a

all: lib $(NAME1) $(NAME2)

lib:
	make -C $(LIBDIR)

$(NAME1): $(OBJ1)
	gcc $(FLAGS) $(LIB) $(OBJ1) -o $(NAME1)

$(NAME2): $(OBJ2)
	gcc $(FLAGS) $(LIB) $(OBJ2) -o $(NAME2)

%.o: %.c $(HDR) $(LIB)
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ1) $(OBJ2)

fclean: clean
	rm -f $(NAME1) $(NAME2)

re: fclean all

NAME1 = checker
NAME2 = push_swap
SRC1 = $(filter-out $(NAME2).c generator.c, $(wildcard *.c))
OBJ1 = ${SRC1:.c=.o}
#HDR1 = $(NAME1).h
SRC2 = $(filter-out $(NAME1).c generator.c, $(wildcard *.c))
OBJ2 = ${SRC2:.c=.o}
HDR = swap.h
FLAGS = -Wextra -Wall -Werror #-fsanitize=address
LIBDIR = libft
LIB = $(LIBDIR)/libft.a
LIBH = $(LIBDIR)/includes

all: lib $(NAME1) $(NAME2)

lib:
	make -C $(LIBDIR)

$(NAME1): $(OBJ1)
	gcc $(FLAGS) -I $(LIBH) $(LIB) $(OBJ1) -o $(NAME1)

$(NAME2): $(OBJ2)
	gcc $(FLAGS) -I $(LIBH) $(LIB) $(OBJ2) -o $(NAME2)

%.o: %.c $(HDR) $(LIB)
	gcc $(FLAGS) -I $(LIBH) -c $< -o $@

clean:
	make clean -C $(LIBDIR)
	rm -f $(OBJ1) $(OBJ2)

fclean: clean
	make fclean -C $(LIBDIR)
	rm -f $(NAME1) $(NAME2)

re: fclean all

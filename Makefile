NAME1 = checker
SRC1 = $(wildcard $(NAME1)*.c)
OBJ1 = ${SRC1:.c=.o}
HDR1 = $(NAME1).h
FLAGS = -Wextra -Wall -Werror
LIBDIR = libft
LIB = $(LIBDIR)/libft.a

all: lib $(NAME1)

lib:
	make -C $(LIBDIR)

$(NAME1): $(OBJ1)
	gcc  $(LIB) $(OBJ1) -o $(NAME1)

%.o: %.c $(HDR1) $(LIB)
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ1)

fclean: clean
	rm -f $(NAME1)

re: fclean all

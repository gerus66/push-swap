NAME = libft.a
SRC = $(wildcard */*.c) $(wildcard *.c)
OBJ = ${SRC:.c=.o}
HDR = $(wildcard */*.h)
HDIR = includes
FLAGS = -Wextra -Wall -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o: %.c $(HDR)
	gcc $(FLAGS) -I $(HDIR) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

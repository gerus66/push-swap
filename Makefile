OS = $(shell uname)

NAME1 = checker
NAME2 = push_swap

S = ./srcs/
SRC1_NOGR = $(filter-out $S$(NAME2).c $Sgraphics.c $Sgraphics1.c, $(wildcard $S*.c))
OBJ1_NOGR = ${SRC1_NOGR:.c=.o}
SRC1 = $(filter-out $S$(NAME2).c, $(wildcard $S*.c))
OBJ1 = ${SRC1:.c=.o}
SRC2 = $(filter-out $S$(NAME1).c $Sgraphics.c $Sgraphics1.c, $(wildcard $S*.c))
OBJ2 = ${SRC2:.c=.o}
HDR = $Sswap.h

LIB = ./lib
INC = ./includes

LIBFT = $(LIB)/libft.a
ifeq ($(OS), Darwin)
	LIBMLX = $(LIB)/mlx_macos.a
	W_FLAGS = -Wall -Wextra -Werror
	MLX_FLAGS = -framework OpenGL -framework AppKit
	CFLAGS = -DMAC
else
	ifeq ($(OS), Linux)
		@echo "Linux version is under development"
		exit 2
	# TODO
	# #	LIBMLX = $(LIB)/mlx_linux.a
	# #	FLAGS = -lmlx -lXext -lX11
else
	@echo "Cant make it on your system, sorry.."
	exit 3
endif
endif

all: $(NAME2) $(OBJ1)
	gcc -I $(INC) $(LIBFT) $(LIBMLX) $(MLX_FLAGS) $(OBJ1) -o $(NAME1)

no-graph: CFLAGS += -DNO_GRAPH
no-graph: fclean $(NAME2) $(OBJ1_NOGR)
	gcc -I $(INC) $(LIBFT) $(OBJ1_NOGR) -o $(NAME1)

$(NAME2): $(OBJ2)
	gcc -I $(INC) $(LIBFT) $(OBJ2) -o $(NAME2)

%.o: %.c $(HDR)
	gcc -I $(INC) $(CFLAGS) $(W_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ1) $(OBJ2)

fclean: clean
	rm -f $(NAME1) $(NAME2)

re: fclean all

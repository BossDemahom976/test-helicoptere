CC = cc
NAME = cub3d
OBJ = obj
OBJ = $(SRC:.c=.o)
LFLAGS = -L./includes/minilibx-linux -lmlx -lXext -lX11 -lm -lz -Wall -Wextra -Werror
INCLUDES = includes/minilibx-linux/libmlx.a
SRC =	src/cub3d.c \
		src/cub3d_free.c \
		src/cub3d_pixel_put.c \
		src/cub3d_pixel_put2.c \
		src/cub3d_init.c \
		src/cub3d_player_move.c
MAKE = make

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) $(LFLAGS) $(OBJ) $(INCLUDES) -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean
		$(MAKE)

.PHONY: all clean fclean re
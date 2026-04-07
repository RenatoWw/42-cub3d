NAME = cub3D
CC = cc
# compilação
CFLAGS = -Wall -Werror -Wextra -I. -Iincludes/mlx -Iincludes/get_next_line -D BUFFER_SIZE=1000 -g
# linkagem
LFLAGS = -lmlx -lXext -lX11 -lm -Lincludes/libft/ -Lincludes/mlx -lft -lbsd
LIBFT = includes/libft/
LIBFT_A = includes/libft/libft.a
MLX = includes/mlx/
MLX_A = includes/mlx/libmlx.a

SRCS = main.c \
		draw_utils.c \
		key.c \
		init.c \
		map.c \
		mlx_utils.c \
		player.c \
		raycasting.c \
		raycasting_utils.c \
		parse/parse_color.c \
		parse/parse_map.c \
		parse/parse_texture.c \
		parse/parse_utils.c \
		parse/parse.c \
		parse/validate_map.c \
		parse/parse_player.c \
		includes/get_next_line/get_next_line.c \
		includes/get_next_line/get_next_line_utils.c

OBJ_DIR = objs/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

$(MLX_A):
	$(MAKE) -s -C $(MLX)

$(LIBFT_A):
	$(MAKE) -s -C $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

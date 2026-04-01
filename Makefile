NAME = cub3d
CC = cc
# compilação
CFLAGS = -Wall -Wextra -Iincludes/mlx -D BUFFER_SIZE=1000 -Ofast
# linkagem
LFLAGS = -lmlx -lXext -lX11 -lm -Lincludes/libft/ -Lincludes/mlx -lft -lbsd
LIBFT = includes/libft/
LIBFT_A = includes/libft/libft.a
MLX = includes/mlx/
MLX_A = includes/mlx/libmlx.a

SRCS = main.c \
		draw_utils.c

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
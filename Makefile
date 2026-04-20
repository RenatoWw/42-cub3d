NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Werror -Wextra -I. -Iincludes/mlx -Iincludes/get_next_line -D BUFFER_SIZE=1000 -g
LFLAGS      = -lmlx -lXext -lX11 -lm -Lincludes/libft/ -Lincludes/mlx -lft -lbsd

LIBFT       = includes/libft/
LIBFT_A     = $(LIBFT)libft.a
MLX         = includes/mlx/
MLX_A       = $(MLX)libmlx.a

SRCS_COMMON = draw_utils.c \
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
			  includes/get_next_line/get_next_line_utils.c \
			  render_lantern.c \
			  textures.c

SRC_MANDATORY = main.c
SRC_BONUS     = main_bonus.c

OBJ_DIR      = objs/
OBJS_COMMON  = $(addprefix $(OBJ_DIR), $(SRCS_COMMON:.c=.o))
OBJS_MAND    = $(addprefix $(OBJ_DIR), $(SRC_MANDATORY:.c=.o))
OBJS_BONUS   = $(addprefix $(OBJ_DIR), $(SRC_BONUS:.c=.o))

all: $(NAME)

bonus: .bonus_flag

.bonus_flag: $(OBJS_COMMON) $(OBJS_BONUS) $(LIBFT_A) $(MLX_A)
	@rm -f .mandatory_flag
	$(CC) $(CFLAGS) $(OBJS_COMMON) $(OBJS_BONUS) $(LFLAGS) -o $(NAME)
	@touch .bonus_flag

$(NAME): .mandatory_flag

.mandatory_flag: $(OBJS_COMMON) $(OBJS_MAND) $(LIBFT_A) $(MLX_A)
	@rm -f .bonus_flag
	$(CC) $(CFLAGS) $(OBJS_COMMON) $(OBJS_MAND) $(LFLAGS) -o $(NAME)
	@touch .mandatory_flag

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX_A):
	$(MAKE) -s -C $(MLX)

$(LIBFT_A):
	$(MAKE) -s -C $(LIBFT)

clean:
	$(MAKE) -C $(LIBFT) clean
	$(MAKE) -C $(MLX) clean
	rm -rf $(OBJ_DIR)
	rm -f .bonus_flag .mandatory_flag

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=includes/mlx.sup ./cub3D maps/map.cub

.PHONY: all clean fclean re bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

NAME = miniRT

SRCS = src/main.c src/window/window_management.c \
	   src/parse/validate_file.c src/parse/validate_objects.c src/parse/validate_params.c \
	   src/parse/validate_settings.c src/parse/validate_utils.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = lib/libft
LIBFT = $(LIBFT_PATH)/libft.a

MLX_PATH = lib/mlx
MLX = $(MLX_PATH)/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) -Imlx_linux -lXext -lX11 -lm -lz

$(LIBFT):
	make -C $(LIBFT_PATH)

$(MLX):
	make -C $(MLX_PATH)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	make -C $(MLX_PATH) clean
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	make -C $(MLX_PATH) clean
	rm -f $(MLX)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

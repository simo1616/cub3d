NAME = cub3d

LIBFT	= libft/libft.a
MLX_DIR = minilibx-linux
MLX		= $(MLX_DIR)/libmlx.a

# Debugger
DEBUGGER = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes --verbose --suppressions=$(PWD)/ignore_readline_leaks.supp --log-file=valgrind-out.txt

# Compilateur et flags +   -DDEBUG
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INC = -I ./libft/inc -I ./inc -I $(MLX_DIR)

# Couleurs pour la déco
GREEN   = \033[1;32m
CYAN    = \033[1;36m
RESET   = \033[0m

# Sources et objets
SRC_DIR = src/
PARSE_DIR = $(SRC_DIR)parse/

SRCS = $(SRC_DIR)main.c \
		$(SRC_DIR)close.c \
		$(SRC_DIR)start_mlx.c \
		$(SRC_DIR)coord.c \
		$(SRC_DIR)init_game.c \
		$(SRC_DIR)graphics.c \
		$(SRC_DIR)player.c \
		$(SRC_DIR)utils.c \
		$(SRC_DIR)text.c \
		$(SRC_DIR)key.c \
		$(SRC_DIR)raycast_dda.c \
		$(SRC_DIR)raycast_draw.c \
		$(SRC_DIR)raycast_render.c \
		$(PARSE_DIR)append_map.c \
		$(PARSE_DIR)check_map_help1.c \
		$(PARSE_DIR)check_map_help2.c \
		$(PARSE_DIR)check_map_help3.c \
		$(PARSE_DIR)check_valid_map.c \
		$(PARSE_DIR)error.c \
		$(PARSE_DIR)final_check.c \
		$(PARSE_DIR)free_1.c \
		$(PARSE_DIR)free_2.c \
		$(PARSE_DIR)init.c \
		$(PARSE_DIR)parse.c \
		$(PARSE_DIR)parse_color.c \
		$(PARSE_DIR)parse_helper1.c \
		$(PARSE_DIR)parse_helper2.c \
		$(PARSE_DIR)parse_text.c \
		$(PARSE_DIR)proc_color.c \
		$(PARSE_DIR)proc_text.c

OBJS = $(SRCS:.c=.o)

LDFLAGS = 	-Llibft -lft \
			-L$(MLX_DIR) -lmlx -lXext -lX11 \
			-lm
# Règles
all: header $(LIBFT) $(MLX) $(NAME)

# Affichage du header
header:
	@echo "$(GREEN)"
	@echo "    by         $(CYAN)@jdecarro $(GREEN)& $(CYAN)@mbendidi"
	@echo ""
	@echo "         ██████╗██╗   ██╗██████╗ ██████╗ ██████╗"
	@echo "        ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗"
	@echo "        ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║"
	@echo "        ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║"
	@echo "        ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝"
	@echo "         ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝"
	@echo "$(RESET)"

# Compilation de libft
$(LIBFT):
	@make -C libft

# Compilation de MinilibX
$(MLX):
	@make -C $(MLX_DIR)

# Compilation de cub3d
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(LDFLAGS)

# Compilation des .o
$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(PARSE_DIR)/%.o: $(PARSE_DIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@make -C libft clean
	@make -C $(MLX_DIR) clean
	rm -f $(OBJS)
	@echo "$(CYAN)Clean completed!$(RESET)"

fclean: clean
	@make -C libft fclean
	rm -f $(MLX_DIR)/libmlx.a $(MLX_DIR)/libmlx_Linux.a
	rm -f $(NAME)

re: fclean all

debug: all
	$(DEBUGGER) ./$(NAME)

.PHONY: all clean fclean re header


# Noms
NAME = cub3d
LIBFT = libft/libft.a
MLX   = minilibx-linux/libmlx.a

# Debugger
DEBUGGER = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes --verbose --suppressions=$(PWD)/ignore_readline_leaks.supp --log-file=valgrind-out.txt

# Compilateur et flags +   -DDEBUG
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INC = -I ./libft/inc -I ./inc -I ./minilibx-linux

# Couleurs pour la déco
GREEN   = \033[1;32m
CYAN    = \033[1;36m
RESET   = \033[0m

# Sources et objets
SRC_DIR = src/
PARSE_DIR = $(SRC_DIR)parse/

SRCS = $(SRC_DIR)main.c \
		$(SRC_DIR)key.c \
		$(SRC_DIR)close.c \
		$(SRC_DIR)start_mlx.c \
		$(SRC_DIR)coord.c \
		$(SRC_DIR)init_game.c \
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

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

OBJS = $(SRCS:.c=.o)

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
	@make -C minilibx-linux

# Compilation de cub3d
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(CFLAGS) -I ./libft/inc -I ./inc -L./libft -lft -L./minilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME)

# Compilation des .o
$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@make -C libft clean
	@make -C minilibx-linux clean
	rm -f $(OBJS)
	@echo "$(CYAN)Clean completed!$(RESET)"

fclean: clean
	@make -C libft fclean
	# Supprimer manuellement les fichiers générés par MinilibX
	rm -f minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a
	rm -f $(NAME)

re: fclean all

debug: all
	$(DEBUGGER) ./$(NAME)

.PHONY: all clean fclean re header

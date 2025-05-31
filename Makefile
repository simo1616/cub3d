# ************************************************************************** #
#                                VARIABLES                                   #
# ************************************************************************** #

NAME        := cub3d

LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

MLX_DIR     := minilibx-linux
MLX         := $(MLX_DIR)/libmlx.a

SRC_ROOT    := src/
CORE_DIR    := $(SRC_ROOT)core/
PLAYER_DIR  := $(SRC_ROOT)player/
RAY_DIR     := $(SRC_ROOT)raycast/
GFX_DIR     := $(SRC_ROOT)graphics/
UTIL_DIR    := $(SRC_ROOT)utils/
PARSE_DIR   := $(SRC_ROOT)parse/

# files *.c
VPATH       := $(CORE_DIR) $(PLAYER_DIR) $(RAY_DIR) \
               $(GFX_DIR)  $(UTIL_DIR)  $(PARSE_DIR)

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -g
INC         := -I ./$(LIBFT_DIR)/inc -I ./inc -I $(MLX_DIR)

LDFLAGS     := -L$(LIBFT_DIR) -lft \
               -L$(MLX_DIR)   -lmlx -lXext -lX11 -lm

# Debug + Valgrind (make debug)
DEBUGGER    := valgrind --leak-check=full --show-leak-kinds=all \
               --track-origins=yes --trace-children=yes --track-fds=yes \
               --log-file=valgrind-out.txt
CFLAGS_DEBUG:= -Wuninitialized -Wmaybe-uninitialized -pedantic \
               -fsanitize=address,undefined -fno-omit-frame-pointer

GREEN := \033[1;32m
CYAN  := \033[1;36m
RESET := \033[0m

SRCS := $(foreach dir,$(VPATH),$(wildcard $(dir)*.c))
OBJS := $(SRCS:.c=.o)

all: header $(LIBFT) $(MLX) $(NAME)

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

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: re
	$(DEBUGGER) ./$(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -f $(OBJS)
	@echo "$(CYAN)Clean completed!$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(MLX_DIR)/libmlx*.a
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug header

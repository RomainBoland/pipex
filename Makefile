NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes/ -I libft/includes/
MINECRAFT_GREEN = \033[38;5;70m
RESET = \033[0m
BOLD = \033[1m
LOADING_CHARS = ⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏

SRC = srcs/main.c srcs/error.c srcs/path.c

# Create objects directory path
OBJ_DIR = objects/
OBJ = $(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

LOGO = printf "\n\
$(MINECRAFT_GREEN)██████╗ ██╗██████╗ ███████╗██╗  ██╗$(RESET)\n\
$(MINECRAFT_GREEN)██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝$(RESET)\n\
$(MINECRAFT_GREEN)██████╔╝██║██████╔╝█████╗   ╚███╔╝ $(RESET)\n\
$(MINECRAFT_GREEN)██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ $(RESET)\n\
$(MINECRAFT_GREEN)██║     ██║██║     ███████╗██╔╝ ██╗$(RESET)\n\
$(MINECRAFT_GREEN)╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝$(RESET)\n"

all: logo $(OBJ_DIR) $(LIBFT) $(NAME)
	@printf "\r$(MINECRAFT_GREEN)$(BOLD)Compilation completed!$(RESET)\n"

logo:
	@$(LOGO)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@printf "\r$(MINECRAFT_GREEN)$(BOLD)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT)

$(OBJ_DIR)%.o: srcs/%.c includes/pipex.h
	@printf "\r$(MINECRAFT_GREEN)Compiling: $< $(RESET)                    "
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@printf "$(MINECRAFT_GREEN)Objects cleaned$(RESET)\n"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@printf "$(MINECRAFT_GREEN)Executable cleaned$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re logo
NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes/ -I libft/includes/
MINECRAFT_GREEN = \033[38;5;70m
RESET = \033[0m
BOLD = \033[1m

SRC = srcs/main.c srcs/error.c srcs/path.c srcs/exec.c

# Create objects directory path
OBJ_DIR = objects/
OBJ = $(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

# Count total files for progress bar
TOTAL_FILES := $(words $(SRC))
CURRENT_FILE = 0

# Progress bar function
define update_progress
    $(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
    $(eval PERCENTAGE=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
    @printf "\r$(MINECRAFT_GREEN)Progress: [%-50s] %3d%%$(RESET)" "$$(printf '#%.0s' $$(seq 1 $$(($(CURRENT_FILE) * 50 / $(TOTAL_FILES)))))" "$(PERCENTAGE)"
endef

LOGO = printf "\n\
$(MINECRAFT_GREEN)██████╗ ██╗██████╗ ███████╗██╗  ██╗$(RESET)\n\
$(MINECRAFT_GREEN)██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝$(RESET)\n\
$(MINECRAFT_GREEN)██████╔╝██║██████╔╝█████╗   ╚███╔╝ $(RESET)\n\
$(MINECRAFT_GREEN)██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ $(RESET)\n\
$(MINECRAFT_GREEN)██║     ██║██║     ███████╗██╔╝ ██╗$(RESET)\n\
$(MINECRAFT_GREEN)╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝$(RESET)\n"

all: logo $(OBJ_DIR) $(LIBFT) $(NAME)
	@printf "\n$(MINECRAFT_GREEN)$(BOLD)Compilation completed!$(RESET)\n"

logo:
	@$(LOGO)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@printf "$(MINECRAFT_GREEN)Building libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@printf "\n$(MINECRAFT_GREEN)$(BOLD)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT)

$(OBJ_DIR)%.o: srcs/%.c includes/pipex.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress)

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
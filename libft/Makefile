NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

SRC_LIBFT = src/libft/ft_atoi.c \
            src/libft/ft_split.c \
            src/libft/ft_bzero.c \
			src/libft/ft_calloc.c \
			src/libft/ft_isalnum.c \
			src/libft/ft_isalpha.c \
			src/libft/ft_isascii.c \
			src/libft/ft_isdigit.c \
			src/libft/ft_isprint.c \
			src/libft/ft_itoa.c \
			src/libft/ft_lstadd_back.c \
			src/libft/ft_lstadd_front.c \
			src/libft/ft_lstclear.c \
			src/libft/ft_lstdelone.c \
			src/libft/ft_lstiter.c \
			src/libft/ft_lstlast.c \
			src/libft/ft_lstmap.c \
			src/libft/ft_lstnew.c \
			src/libft/ft_lstsize.c \
			src/libft/ft_memchr.c \
			src/libft/ft_memcmp.c \
			src/libft/ft_memcpy.c \
			src/libft/ft_memmove.c \
			src/libft/ft_memset.c \
			src/libft/ft_putchar_fd.c \
			src/libft/ft_putendl_fd.c \
			src/libft/ft_putnbr_fd.c \
			src/libft/ft_putstr_fd.c \
			src/libft/ft_strchr.c \
			src/libft/ft_strdup.c \
			src/libft/ft_striteri.c \
			src/libft/ft_strjoin.c \
			src/libft/ft_strlcat.c \
			src/libft/ft_strlcpy.c \
			src/libft/ft_strlen.c \
			src/libft/ft_strmapi.c \
			src/libft/ft_strncmp.c \
			src/libft/ft_strnstr.c \
			src/libft/ft_strrchr.c \
			src/libft/ft_strtrim.c \
			src/libft/ft_substr.c \
			src/libft/ft_tolower.c \
			src/libft/ft_toupper.c

SRC_PRINTF = src/ft_printf/ft_printf.c \
             src/ft_printf/ft_put_str.c \
             src/ft_printf/ft_put_int.c \
			 src/ft_printf/ft_put_ptr.c \
			 src/ft_printf/ft_put_unsigned.c \
			 src/ft_printf/ft_put_hexa.c

SRC_GNL = src/get_next_line/get_next_line_bonus.c \
          src/get_next_line/get_next_line_utils_bonus.c

SRC = $(SRC_LIBFT) $(SRC_PRINTF) $(SRC_GNL)
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
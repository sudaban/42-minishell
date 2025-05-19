NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = \
	main.c \
	Signal/signal.c \

SRC += \
	Built-In/Exit/exit.c \
	Built-In/Pwd/pwd.c \
	Built-In/Echo/echo.c \
	Built-In/Cd/cd.c \
	Built-In/Env/env.c \
	Built-In/Export/export.c \
	Built-In/Export/export_utils.c \
	Built-In/Unset/unset.c \

SRC += \
	Lexer/lexer.c \
	Parser/parser.c \
	Utils/utils.c \

SRC += \
	Libft/ft_strlen.c \
	Libft/ft_split.c \
	Libft/ft_strchr.c \
	Libft/ft_free_double_ptr.c \
	Libft/ft_substr.c \
	Libft/ft_strlcpy.c \
	Libft/ft_strncmp.c \
	Libft/ft_strdup.c \
	Libft/ft_memcpy.c \
	Libft/ft_isspace.c \
	Libft/ft_isalnum.c


OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = \
	main.c \
	Signal/signal.c \
	Signal/sig_utils.c

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
	Lexer/lexer_split.c \
	Lexer/token_utils.c \
	Lexer/lexer_helper.c \
	Parser/parser.c \
	Parser/parser_helper.c \
	Utils/utils.c \
	Utils/helper.c \
	Utils/syntax.c \
	Utils/Memory/memory.c \
	Utils/Redirections/redirection.c \
	Utils/Redirections/red_utils.c \
	Utils/Redirections/utils2.c \
	Utils/Status/status.c \
	Executor/executor.c \
	Executor/pipe.c \
	Executor/pipe_utils.c

SRC += \
	Libft/ft_strlen.c \
	Libft/ft_split.c \
	Libft/ft_strchr.c \
	Libft/ft_substr.c \
	Libft/ft_strlcpy.c \
	Libft/ft_strncmp.c \
	Libft/ft_strdup.c \
	Libft/ft_memcpy.c \
	Libft/ft_isspace.c \
	Libft/ft_isalnum.c \
	Libft/ft_strtok.c \
	Libft/ft_itoa.c \
	Libft/ft_putstr_fd.c \
	Libft/ft_putendl_fd.c \
	Libft/ft_isdigit.c \
	Libft/ft_atol.c \
	Libft/ft_isalpha.c


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

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = \
	main.c \
	Signal/signal.c \
	Built-In/Exit/exit.c \
	Built-In/Pwd/pwd.c \
	Built-In/Echo/echo.c \
	Built-In/Cd/cd.c \
	Built-In/Env/env.c \
	Built-In/Export/export.c \
	Built-In/Export/export_utils.c \
	Built-In/Unset/unset.c

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

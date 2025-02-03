NAME = philo
CC = clang-19
CFLAGS = -Wall -Wextra -Werror -fsanitize=address,undefined,integer
SRC = philolo.c philolo_utils.c
OBJ = $(SRC:.c=.o)

%.o: %.c philolo.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

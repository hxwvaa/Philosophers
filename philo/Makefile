NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror 
# -pthread -fsanitize=thread -g
SRC = philolo.c philolo_utils.c philolo_inits.c
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

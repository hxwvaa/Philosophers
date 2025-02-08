NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRC = philo.c philo_destroy_free.c philo_eat_sleep_think.c philo_fork_utils.c philo_inits.c philo_monitor.c philo_routine.c philo_utils.c
OBJ = $(SRC:.c=.o)

%.o: %.c philo.h
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

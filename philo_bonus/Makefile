NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Werror -Wextra
TFLAG = -lpthread

SRC = philosophers_bonus.c argcontrol_bonus.c utils_bonus.c \
	routine_bonus.c gettime_bonus.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -I ./ $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(TFLAG) -o $(NAME)

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
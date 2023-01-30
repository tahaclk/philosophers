NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra
TFLAG = -lpthread

SRC = philosophers.c argcontrol.c utils.c \
	routine.c gettime.c

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
SRC = main.c

OBJS = $(SRC:.c=.o)

CC = gcc

Name = game

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $(SRC)

$(Name) : $(OBJS)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz  -o $(OBJS) 

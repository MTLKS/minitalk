SERVER = server
CLIENT = client

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SERVER_SRC = src/server.c
CLIENT_SRC = src/client.c

all: server client

bonus: all

server:		libft
			$(CC) $(CFLAGS) $(SERVER_SRC) -Llibft -lft -o $(SERVER)

client:		libft
			$(CC) $(CFLAGS) $(CLIENT_SRC) -Llibft -lft -o $(CLIENT)

libft:
			make -C libft

clean:
			make -C libft clean

fclean:
			make -C libft fclean
			rm -f server client

re:			fclean all

.PHONY:		all clean fclean re bonus libft
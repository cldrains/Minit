NAME = server client
NAME_bonus = server_bonus client_bonus
LIBFT = libft/libft.a
CC = cc

FLAGS = -Wall -Wextra


all: libft $(NAME)

bonus: libft $(NAME_bonus)

libft: $(LIBFT)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): server.c client.c
	$(CC) $(FLAGS) server.c ./libft/libft.a -o server
	$(CC) $(FLAGS) client.c ./libft/libft.a -o client

$(NAME_bonus): server_bonus.c client_bonus.c
	$(CC) $(FLAGS) server_bonus.c ./libft/libft.a -o server_bonus
	$(CC) $(FLAGS) client_bonus.c ./libft/libft.a -o client_bonus

clean:
	$(MAKE) clean -C ./libft/
	rm -f $(NAME) $(NAME_bonus)

fclean: clean
	$(MAKE) fclean -C ./libft/

re: fclean all
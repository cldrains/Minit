# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 04:10:54 by tevers            #+#    #+#              #
#    Updated: 2023/07/11 09:50:04 by tevers           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAGS := -Wall -Wextra -Werror
RM := /bin/rm -f
NAME_SERVER := server
NAME_CLIENT := client

NAME_SERVER_BONUS := server_bonus
NAME_CLIENT_BONUS := client_bonus

SRC_SERVER := server.c
SRC_CLIENT := client.c

SRC_SERVER_BONUS = server_bonus.c server_utils.c
SRC_CLIENT_BONUS := client_bonus.c client_gnl.c client_handler.c client_utils.c

INCLUDES := -I. -Ilibft

LIBFT := ./libft/libft.a
LIBFT_PATH := ./libft

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_SERVER) $(LIBFT) -o $(NAME_SERVER)

$(NAME_CLIENT): $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

# Make libft
$(LIBFT): $(shell make -C $(LIBFT_PATH) -q libft.a)
	make -C $(LIBFT_PATH)

# Clean object files (*.o) - not used on this project
clean:
	make clean -C $(LIBFT_PATH)
	
# Clean object files (*.o) and the binary file
fclean: clean
	make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

# Clean object files (*.o) and the binary file; 
# Then create the binary file again, and generate the library and index it
re: fclean all

# "To turn in bonuses to your project, you must include a rule bonus to your Makefile"
# "Makefile must not relink"

$(NAME_SERVER_BONUS): $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_SERVER_BONUS) $(LIBFT) -o $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_CLIENT_BONUS) $(LIBFT) -o $(NAME_CLIENT_BONUS)
	
bonus: $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)


rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus 
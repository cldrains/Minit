NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = 	ft_is.c ft_mem.c  ft_mem1.c  ft_num.c  ft_put.c \
        ft_split.c  ft_str.c  ft_str1.c  ft_str2.c  ft_to.c \
		ft_print_str.c ft_print_nbr.c ft_printf.c get_next_line.c

OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS) libft.h

clean:
	rm -rf $(OBJS)

fclean: clean
	@rm -f ./$(NAME) libft.a

re: fclean all

.PHONY: all clean fclean re
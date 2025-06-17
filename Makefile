NAME	= pipex
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -I./libft
SRC		= *.c
OBJ		= $(SRC:.c=.o)
DEPS	= libft/libft.a

all: $(DEPS) $(NAME)

libft/libft.a:
	@$(MAKE) --no-print-directory -C libft

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) --no-print-directory -C libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C libft fclean

re: fclean all

.PHONY: all clean fclean re
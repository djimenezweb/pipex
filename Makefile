NAME	= push_swap
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -I./libft -I./libstack
SRC		= push_swap.c push_swap_helpers.c algorithms/basic_sort.c algorithms/radix.c initialization/initialization.c initialization/validation.c moves/push.c moves/reverse_rotate.c moves/rotate.c moves/swap.c
OBJ		= $(SRC:.c=.o)
DEPS	= libft/libft.a libstack/libstack.a

all: $(DEPS) $(NAME)

libft/libft.a:
	@$(MAKE) --no-print-directory -C libft

libstack/libstack.a:
	@$(MAKE) --no-print-directory -C libstack

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) libft/libft.a libstack/libstack.a -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) --no-print-directory -C libft clean
	@$(MAKE) --no-print-directory -C libstack clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C libft fclean
	@$(MAKE) --no-print-directory -C libstack fclean

re: fclean all

.PHONY: all clean fclean re
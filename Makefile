NAME		= pipex
NAME_BONUS	= pipex_bonus
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I./libft
SRC			= pipex_errors.c pipex_fork_process.c pipex_helpers.c pipex_init_context.c pipex_run_child.c split_helpers.c
OBJ			= $(SRC:.c=.o)
DEPS		= libft/libft.a

all:	$(DEPS) $(NAME)
bonus:	$(DEPS) $(NAME_BONUS)

libft/libft.a:
	@$(MAKE) --no-print-directory -C libft

$(NAME): pipex.o $(OBJ)
	@$(CC) $(CFLAGS) pipex.o $(OBJ) libft/libft.a -o $(NAME)

$(NAME_BONUS): pipex_bonus.o $(OBJ)
	@$(CC) $(CFLAGS) pipex_bonus.o $(OBJ) libft/libft.a -o $(NAME_BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) --no-print-directory -C libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re
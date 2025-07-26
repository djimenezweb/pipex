NAME	= pipex
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -I./libft
SRC		= init_context.c paths.c pipex.c pipex_errors.c pipex_helpers.c run_child.c split_helpers.c
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

reset:
	@$(MAKE) --no-print-directory re
	@$(MAKE) --no-print-directory clean
	@rm -f *.txt
	@clear

.PHONY: all clean fclean re reset
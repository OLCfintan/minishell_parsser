NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
READLINE = -lreadline

FILES = $(shell find . -type f -name '*.c')

OBJ = $(FILES:.c=.o)

GREEN = \033[0;32m
ORANGE = \033[0;33m
RED = \033[0;31m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) $(READLINE)  -o $@
	@echo "$(GREEN)make is done :)"
	@echo "$(ORANGE)have fun ..."

$(OBJ): %.o: %.c
	@$(CC) $(CFLAGS) -c $< -g -o $@

clean:
	@rm -rf $(OBJ)
	@echo "$(RED)Cleaning objects..."

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)Cleaning $(NAME)..."

re: fclean all

.PHONY: all clean fclean re

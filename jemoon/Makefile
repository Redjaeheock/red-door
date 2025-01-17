NAME = minishell

SRC = main.c \
      exec_commads/exec_commads_liked_list.c \
      exec_commads/exec_commads_size.c \
      exec_commads/get_exec_commads.c \
      parsing/parse_utils.c \
      parsing/quote_parser.c \
      parsing/split_words.c \
      printf_utils/printf_utils.c \
      set_tpye/set_tpye.c \
	  validate_syntax/validate_bash_syntax.c \
      validate_syntax/validate_bash_syntax_utils.c \
	  liked_list/linked_list.c \
	  readline_utils/readline_utils.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

HEADER = minishell.h

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c $(HEADER)
	@cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
